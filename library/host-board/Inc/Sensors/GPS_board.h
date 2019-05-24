/*
 * GPS_board.h
 *
 *  Created on: 12 Apr 2019
 *      Author: linky
 */

#ifndef GPS_BOARD_H_
#define GPS_BOARD_H_

#include "main.h"

void gps_init(UART_HandleTypeDef *gpsHuart);
void TK_GPS_board(void const * argument);

#endif /* SENSORS_GPS_BOARD_H_ */
