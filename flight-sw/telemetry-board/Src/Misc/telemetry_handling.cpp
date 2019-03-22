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

#include "Telemetry/telemetry_protocol.h"
#include "Telemetry/simpleCRC.h"
#include "Telemetry/xbee.h"

extern "C" {
#include "CAN_communication.h"
}

#define TELE_TIMEOUT 50

Telemetry_Message createTelemetryDatagram (IMU_data* imu_data, BARO_data* baro_data,
                                           uint32_t measurement_time, uint32_t telemetrySeqNumber)
{

  DatagramBuilder builder = DatagramBuilder (SENSOR_DATAGRAM_PAYLOAD_SIZE, TELEMETRY_ERT18, telemetrySeqNumber);

  // ## Beginning of datagram Payload ##
  // measurement time
  builder.write32<uint32_t> (measurement_time);

  builder.write32<float32_t> (imu_data->acceleration.x);
  builder.write32<float32_t> (imu_data->acceleration.y);
  builder.write32<float32_t> (imu_data->acceleration.z);

  builder.write32<float32_t> (0.0);   // flight status
  builder.write32<float32_t> (0.0); // AB_angle
  builder.write32<float32_t> (0.0);     // pitot_press

  builder.write32<float32_t> (baro_data->temperature);
  builder.write32<float32_t> (baro_data->pressure);

  builder.write32<float32_t> (0);

  return builder.finalizeDatagram ();
}

void sendTelemetry(IMU_data *pimu_data, BARO_data *pbaro_data, uint32_t measurement_time) {
  static uint32_t telemetrySeqNumber = 0;

  Telemetry_Message m = createTelemetryDatagram (pimu_data, pbaro_data, measurement_time,
                                                       telemetrySeqNumber++);
  osMessagePut (xBeeQueueHandle, (uint32_t) &m, 50);
}

void sendSDcard(uint32_t id_can, uint32_t timestamp, uint8_t id, uint32_t data) {
  static uint32_t sdSeqNumber = 0;

  sdSeqNumber++;

}

void TK_telemetry_data (void const * args)
{
  // init
  IMU_data  imu  = {{0,0,0},{0,0,0}, 0};
  BARO_data baro = {0,0,0};
  uint32_t meas_time = HAL_GetTick();
  uint32_t tele_time = HAL_GetTick();

  bool new_baro = 0;
  bool new_imu = 0;

  osDelay (1000); // Wait for the other threads to be ready

  for (;;) // while 1
  {
      // read CAN frame
	  if (can_readFrame()) { // check if new data

		// add to SD card
	    sendSDcard(can_current_msg.id_CAN, can_current_msg.timestamp, can_current_msg.id, can_current_msg.data);

	    switch(can_current_msg.id) {
	    case DATA_ID_PRESSURE:
	    	baro.pressure = ((float32_t) ((int32_t) can_current_msg.data)) / 1000; // convert from cPa to hPa
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
	    	break;
	    }
	  }

	  // if both sensor data are new or timeout
	  if ((new_baro && new_imu) ||
	      ((new_baro || new_imu) && (tele_time - HAL_GetTick() > TELE_TIMEOUT))) {
		sendTelemetry(&imu, &baro, meas_time);
		tele_time = HAL_GetTick();
		new_baro = 0;
		new_imu  = 0;
	  }

      osDelay (10);
    }
}
