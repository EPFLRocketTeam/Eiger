/*
 * CAN_communication.h
 *
 *  Created on: Feb 23, 2019
 *      Author: Tim Lebailly
 */

#ifndef CAN_COMMUNICATION_H_
#define CAN_COMMUNICATION_H_

#include "stm32f4xx_hal.h"
#include <string.h>

typedef struct
{
  uint32_t data;
  uint8_t id;
  uint32_t timestamp;
} CAN_msg;

// Define all the data ID's
#define DATA_ID_ALTITUDE 0
#define DATA_ID_ACCELERATION_X 1
#define DATA_ID_ACCELERATION_Y 2
#define DATA_ID_ACCELERATION_Z 3
#define DATA_ID_GYRO_X 4
#define DATA_ID_GYRO_Y 5
#define DATA_ID_GYRO_Z 6

// Define all the board ID's (lower means higher priority for CAN protocol)
#define ID_MASTER 0
#define ID_GPS_SENSOR 3
#define ID_TELEMETRY_SD 2


void CAN_Config(uint32_t);
void setFrame(uint32_t, uint8_t, uint32_t);
uint32_t readFrame(void);

#endif /* CAN_COMMUNICATION_H_ */
