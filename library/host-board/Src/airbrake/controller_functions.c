/*
 * controller_functions.c
 *
 *  Created on: 28 avr. 2019
 *      Author: Alexandre
 */

#include <stm32f4xx_hal.h>
#include <string.h>
#include "cmsis_os.h"
#include "led.h"


#define MAX_OPENING_DEG 66
#define MIN_OPENING_DEG 0
#define ANGLE_HELLOWORLD 1


UART_HandleTypeDef* airbrake_huart;
//extern volatile float32_t airbrakes_angle;


char command_string[10] = {0};

void ab_init(UART_HandleTypeDef *ab_huart) {
	airbrake_huart = ab_huart;
}

void transmit_command(char* command, int size)
{
  static char command_buffer[64];
  strcpy(command_buffer, command);
  HAL_UART_Transmit(airbrake_huart, (uint8_t*)command_buffer, size, 10);
  osDelay(30);
}


int deg2inc(float degrees_angle)
{
  //int inc = -(int) (degrees_angle * 75000 / 360); //3000 inc/evolution, 1:25reductor
	int inc = -(int) ((degrees_angle * 38280) / 360); //3000 inc/evolution, 1:12.76reductor
  return inc;
}

char* do_string_command (char first, char second, int number)
{
  sprintf(command_string, "%c%c%d\n", first, second, number);
  return command_string; //is it really needed ?
}

void motor_goto_position_inc (int position_inc)
{
  char command[15];
  transmit_command("EN\n", 3);
  do_string_command ('L', 'A', position_inc);
  sprintf(command, "%s%s", command_string, "M\n");
  transmit_command(command, strlen(command));
  // ADD DELAY HERE; THE PERIOD DEPENDS ON KALMAN FILTER FREQUENCY....
  return;
}

void controller_test (void)
{
  transmit_command("HO\r", 3);
  transmit_command("EN\r", 3);
  motor_goto_position_inc(10000);
  transmit_command("M\r", 2);
  return; // SMALL FUNCTION TO TEST IF THE TRANSMISSION IS WORKING... THE MOTOR SHOULD ROTATE
}

void aerobrakes_control_init (void)
{
	led_set_rgb(255,0,0);
  // TO CALL AT POWERING ON
  char command[40];
  do_string_command ('L', 'L', deg2inc (MAX_OPENING_DEG));
  sprintf(command, "%s%s%s%s", "HO\n", "LL1\n", command_string, "APL1\n");
  transmit_command(command, strlen(command));
  // controller properties
//  command = "SP10000\r";              MAXIMUM SPEED in inc/min
//  HAL_UART_Transmit_DMA(&huart1, command, 8);
  sprintf(command, "%s%s%s%s%s%s%s", "POR10\n", "I50\n", "PP30\n", "PD3\n",
      "LPC3000\n", "LCC3000\n", "EN\n");
  transmit_command(command, 37);
  return;
}

void full_open (void)
{
  int angle_open_inc = deg2inc (MAX_OPENING_DEG);
  motor_goto_position_inc (angle_open_inc);

  return;
}

void full_close (void)
{
  int angle_close_inc = deg2inc (MIN_OPENING_DEG);
  motor_goto_position_inc (angle_close_inc);
  return;
}

void aerobrake_helloworld (void)
{
	int i=0;
	for(i=0; i<5;i++)
	{
		transmit_command("EN\n", 3);
		led_set_rgb(0,0,255);
		int angle_helloworld_inc = deg2inc(ANGLE_HELLOWORLD);
		motor_goto_position_inc(angle_helloworld_inc);
		osDelay(500);
		full_close();
		led_set_rgb(0,255,0);
	}

  return;
}
