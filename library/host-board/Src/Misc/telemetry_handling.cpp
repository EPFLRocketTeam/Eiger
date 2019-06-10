/*
 * data_handling.c
 *
 *  Created on: 19 Apr 2018
 *      Author: Cl�ment Nussbaumer
 */

#include "cmsis_os.h"

#include "Misc/Common.h"

#include "Misc/data_handling.h"
#include "Misc/datagram_builder.h"
#include "Misc/sd_sync.h"

#include "Telemetry/telemetry_protocol.h"
#include "Telemetry/simpleCRC.h"

#include <stdbool.h>

extern "C" {
#include "CAN_communication.h"
}

#define TELE_TIMEMIN 100
#define BUFFER_SIZE 128

extern osMessageQId xBeeQueueHandle;
char buffer[BUFFER_SIZE] = {0};




Telemetry_Message createTelemetryDatagram (IMU_data* imu_data, BARO_data* baro_data, uint32_t measurement_time, uint32_t telemetrySeqNumber)
{

  DatagramBuilder builder = DatagramBuilder (SENSOR_DATAGRAM_PAYLOAD_SIZE, TELEMETRY_ERT18, telemetrySeqNumber);

  // ## Beginning of datagram Payload ##
  // measurement time
  builder.write32<uint32_t> (measurement_time);

  builder.write32<float32_t> (imu_data->acceleration.x);
  builder.write32<float32_t> (imu_data->acceleration.y);
  builder.write32<float32_t> (imu_data->acceleration.z);

  builder.write32<float32_t> (imu_data->eulerAngles.x); // flight status
  builder.write32<float32_t> (imu_data->eulerAngles.y); // AB_angle
  builder.write32<float32_t> (imu_data->eulerAngles.z); // pitot_press

  builder.write32<float32_t> (baro_data->temperature);
  builder.write32<float32_t> (baro_data->pressure);

  builder.write32<float32_t> (0);

  return builder.finalizeDatagram ();
}


Telemetry_Message createGPSDatagram (uint32_t seqNumber, GPS_data gpsData)
{
  DatagramBuilder builder = DatagramBuilder (GPS_DATAGRAM_PAYLOAD_SIZE, GPS, seqNumber++);

  builder.write32<uint32_t> (HAL_GetTick ());
  builder.write8 (gpsData.sats);
  builder.write32<float32_t> (gpsData.hdop);
  builder.write32<float32_t> (gpsData.lat);
  builder.write32<float32_t> (gpsData.lon);
  builder.write32<int32_t> (gpsData.altitude);

  return builder.finalizeDatagram ();
}


void sendSDcard(uint32_t id_can, uint32_t timestamp, uint8_t id, uint32_t data) {
   static uint32_t sdSeqNumber = 0;
   sdSeqNumber++;
   sprintf((char*) buffer, "%lu\t%lu\t%d\t%ld\n", sdSeqNumber, HAL_GetTick(), id, (int32_t) data);

   sd_write(buffer, strlen(buffer));
}

void TK_telemetry_data (void const * args)
{
  // init
  IMU_data  imu  = {{0,0,0},{0,0,0}, 0};
  BARO_data baro = {0,0,0};
  GPS_data gpsData = {0};
  uint32_t meas_time = HAL_GetTick();
  uint32_t tele_time = HAL_GetTick();

  bool new_baro = 0;
  bool new_imu = 0;
  bool new_gps = 0;

  osDelay (1000); // Wait for the other threads to be ready
  uint32_t telemetrySeqNumber = 0;

  baro.temperature = 20;

  for (;;)
    {
	  while (can_readFrame()) { // check if new data

	    // add to SD card
	    sendSDcard(can_current_msg.id_CAN, can_current_msg.timestamp, can_current_msg.id, can_current_msg.data);

	    switch(can_current_msg.id) {
	    case DATA_ID_PRESSURE:
	   	  baro.pressure = ((float32_t) ((int32_t) can_current_msg.data)) / 100; // convert from cPa to hPa
		  new_baro = 1;
		  break;
		case DATA_ID_ACCELERATION_X:
		  imu.acceleration.x = ((float32_t) ((int32_t) can_current_msg.data)) / 1000; // convert from m-g to g
		  break;
  	    case DATA_ID_ACCELERATION_Y:
		  imu.acceleration.y = ((float32_t) ((int32_t) can_current_msg.data)) / 1000;
		  break;
        case DATA_ID_ACCELERATION_Z:
		  imu.acceleration.z = ((float32_t) ((int32_t) can_current_msg.data)) / 1000;
		  new_imu = 1;  // only update when we get IMU from Z
		  meas_time = HAL_GetTick();
		  break;
        case DATA_ID_GYRO_X:
          imu.eulerAngles.x = ((float32_t) ((int32_t) can_current_msg.data)); // convert from mrps
          break;
        case DATA_ID_GYRO_Y:
          imu.eulerAngles.y = ((float32_t) ((int32_t) can_current_msg.data));
          break;
        case DATA_ID_GYRO_Z:
          imu.eulerAngles.z = ((float32_t) ((int32_t) can_current_msg.data));
          break;
        case DATA_ID_GPS_HDOP:
		  gpsData.hdop = ((float32_t) ((int32_t) can_current_msg.data)) / 1e3;
		  break;
        case DATA_ID_GPS_LAT:
		  gpsData.lat = ((float32_t) ((int32_t) can_current_msg.data))  / 1e6;
		  break;
        case DATA_ID_GPS_LONG:
		  gpsData.lon = ((float32_t) ((int32_t) can_current_msg.data))  / 1e6;
		  break;
        case DATA_ID_GPS_ALTITUDE:
		  gpsData.altitude = ((int32_t) can_current_msg.data);
		  break;
        case DATA_ID_GPS_SATS:
		  gpsData.sats = ((uint8_t) ((int32_t) can_current_msg.data));
		  new_gps = 1;
		  break;
	    }

	    // if both sensor data are new or timeout
	    if ((new_baro || new_imu) && (HAL_GetTick() - tele_time > TELE_TIMEMIN)) {
	    	Telemetry_Message m = createTelemetryDatagram (&imu, &baro, meas_time, telemetrySeqNumber++);
	    	osMessagePut (xBeeQueueHandle, (uint32_t) &m, 50);
	    	tele_time = HAL_GetTick();
	    	new_baro = 0;
	    	new_imu  = 0;
	    }

	    if (new_gps) {
	    	Telemetry_Message m = createGPSDatagram (telemetrySeqNumber++, gpsData);
	    	osMessagePut (xBeeQueueHandle, (uint32_t) &m, 50);
	    	// reset all the data
	    	gpsData.hdop     = 0xffffffff;
	    	gpsData.lat      = 0xffffffff;
	    	gpsData.lon      = 0xffffffff;
	    	gpsData.altitude = 0;
	    	gpsData.sats     = 0;
	    	new_gps = 0;
	    }
	  }

      osDelay (1);
    }
}
