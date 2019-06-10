/*
 * CAN_communication.c
 *
 * If you read a frame and there is a message, the led blinks blue.
 * If you write a frame and it fails, the led blinks red.
 * If you write a frame and if does not fail, the led blinks green.
 *
 *  Created on: Feb 23, 2019
 *      Author: Tim Lebailly
 */
typedef float float32_t;

#include <stdbool.h>
#include "cmsis_os.h"

#include "CAN_communication.h"
#include "main.h"
#include "led.h"
#include "Telemetry/telemetry_handling.h"
#include "Misc/datastructs.h"
#include "sd_card.h"

#define BUFFER_SIZE 128

bool handleGPSData(GPS_data data) {
#ifdef XBEE
	return telemetry_handleGPSData(data);
#endif
	return false;
}

bool handleIMUData(IMU_data data) {
#ifdef XBEE
	return telemetry_handleIMUData(data);
#endif
	return false;
}

bool handleBaroData(BARO_data data) {
#ifdef XBEE
	return telemetry_handleBaroData(data);
#endif
	return false;
}


void sendSDcard(CAN_msg msg) {
   static char buffer[BUFFER_SIZE] = {0};
   static uint32_t sdSeqNumber = 0;
   sdSeqNumber++;

   uint32_t id_can = msg.id_CAN;
   uint32_t timestamp = msg.timestamp;
   uint8_t id = msg.id;
   uint32_t data = msg.data;

   sprintf((char*) buffer, "%lu\t%lu\t%d\t%ld\n",
		   sdSeqNumber, HAL_GetTick(), id, (int32_t) data);

   sd_write(buffer, strlen(buffer));
}

void TK_can_reader() {
// init
IMU_data  imu  = {{0,0,0},{0,0,0}, 0};
BARO_data baro = {0,0,0};
GPS_data gpsData = {0, 0, 0, 0, 0};
CAN_msg msg;

bool new_baro = 0;
bool new_imu = 0;
bool new_gps = 0;

osDelay (500); // Wait for the other threads to be ready

baro.temperature = 20;

for (;;)
{
  while (can_msgPending()) { // check if new data
	msg = can_readBuffer();
	// add to SD card
	#ifdef SDCARD
	sendSDcard(msg);
	#endif

	switch(msg.id) {
	case DATA_ID_PRESSURE:
	  baro.pressure = ((float32_t) ((int32_t) msg.data)) / 100; // convert from cPa to hPa
	  new_baro = true;
	  break;
	case DATA_ID_ACCELERATION_X:
	  imu.acceleration.x = ((float32_t) ((int32_t) msg.data)) / 1000; // convert from m-g to g
	  break;
	case DATA_ID_ACCELERATION_Y:
	  imu.acceleration.y = ((float32_t) ((int32_t) msg.data)) / 1000;
	  break;
	case DATA_ID_ACCELERATION_Z:
	  imu.acceleration.z = ((float32_t) ((int32_t) msg.data)) / 1000;
	  new_imu = true;  // only update when we get IMU from Z
	  break;
	case DATA_ID_GYRO_X:
	  imu.eulerAngles.x = ((float32_t) ((int32_t) msg.data)); // convert from mrps
	  break;
	case DATA_ID_GYRO_Y:
	  imu.eulerAngles.y = ((float32_t) ((int32_t) msg.data));
	  break;
	case DATA_ID_GYRO_Z:
	  imu.eulerAngles.z = ((float32_t) ((int32_t) msg.data));
	  break;
	case DATA_ID_GPS_HDOP:
	  gpsData.hdop = ((float32_t) ((int32_t) msg.data)) / 1e3; // from mm to m
	  break;
	case DATA_ID_GPS_LAT:
	  gpsData.lat = ((float32_t) ((int32_t) msg.data))  / 1e6; // from udeg to deg
	  break;
	case DATA_ID_GPS_LONG:
	  gpsData.lon = ((float32_t) ((int32_t) msg.data))  / 1e6; // from udeg to deg
	  break;
	case DATA_ID_GPS_ALTITUDE:
	  gpsData.altitude = ((int32_t) msg.data) / 100; // from cm to m
	  break;
	case DATA_ID_GPS_SATS:
	  gpsData.sats = ((uint8_t) ((int32_t) msg.data));
	  new_gps = true;
	  break;
	}
  }

  if (new_gps) {
	  if (handleGPSData(gpsData)) { // handle packet
		  // reset all the data
		  gpsData.hdop     = 0xffffffff;
		  gpsData.lat      = 0xffffffff;
		  gpsData.lon      = 0xffffffff;
		  gpsData.altitude = 0;
		  gpsData.sats     = 0;
		  new_gps = false;
	  }
  }

  if (new_baro) {
	  new_baro = !handleBaroData(baro);
  }

  if (new_imu) {
	  new_imu = !handleIMUData(imu);
  }

  osDelay (10);
  }
}
