/*
 * airbrake.h
 *
 *  Created on: 28 avr. 2019
 *      Author: Alexandre
 */

#ifndef AIRBRAKE_H_
#define AIRBRAKE_H_

#include "usart.h"

void TK_ab_controller (void const * argument);

void ab_init(UART_HandleTypeDef *ab_huart);

void controller_test(void);

void aerobrakes_control_init(void);

void full_close(void);
void full_open(void);

void aerobrake_helloworld(void);
void motor_goto_position_inc(int position_inc);

#endif /* AIRBRAKE_H_ */
