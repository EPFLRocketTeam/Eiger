/*
 * airbrakes.c
 *
 *  Created on: 28 Apr 2019
 *      Author: Alexandre
 */

#include "stm32f4xx_hal.h"
#include "Misc/Common.h"
#include <cmsis_os.h>
#include "airbrake/airbrake.h"

#include "CAN_communication.h"
#include "led.h"


//#include "Airbrakes/controller_functions.h"
//#include <Misc/rocket_constants.h>

//extern volatile uint32_t flight_status;
int led_AB_id;



void TK_ab_controller (void const * argument)
{
  osDelay (2000);
  static float altitude = 0, speed = 0;
  currentState = STATE_CALIBRATION;

  led_AB_id = led_register_TK();

  // Finite State Machine -------------------------
  for (;;)
    {

	  switch(currentState){

	  	  case STATE_CALIBRATION:
	  		  led_set_TK_rgb(led_AB_id, 200, 0, 80);


	  		  // Wait for AB motor powered ON
	  		  if(!aerobrakes_control_init())
	  		  {
	  			  osDelay(100);
	  			  break;
	  		  }
	  		  else
	  		  {

	  			  aerobrake_helloworld();
				  can_setFrame(STATE_IDLE, CAN_ID_STATE, HAL_GetTick());

				  currentState = STATE_IDLE;
				  break;
	  		  }

		  case STATE_IDLE:
			  led_set_TK_rgb(led_AB_id, 50, 0, 80);
			  // wait for LIFTOFF message
			  if( !(can_current_msg.id == CAN_ID_STATE && can_current_msg.data == STATE_LIFTOFF) )
			  {
				  can_readFrame();
				  osDelay(100);
				  break;
			  }
			  else
			  {
				  currentState = STATE_LIFTOFF;
				  break;
			  }

		  case STATE_LIFTOFF:
			  led_set_TK_rgb(led_AB_id, 50, 100, 200);
			  // wait for burn-out message
			  if( !(can_current_msg.id == CAN_ID_STATE && can_current_msg.data == STATE_COAST) )
			  {
				  can_readFrame();
				  if(can_current_msg.id == DATA_ID_KALMAN_VZ)
				  {
					  speed = can_current_msg.data;
				  }
				  else if(can_current_msg.id == DATA_ID_KALMAN_Z)
				  {
					  altitude = can_current_msg.data;
				  }
				  osDelay(10);
				  break;
			  }
			  else
			  {
				  currentState = STATE_COAST;
				  break;
			  }

		  case STATE_COAST:
			  led_set_TK_rgb(led_AB_id, 0, 200, 50);
			  // wait for apogee
			  if( !(can_current_msg.id == CAN_ID_STATE && can_current_msg.data == STATE_PRIMARY) )
			  {
				  can_readFrame();
				  if(can_current_msg.id == DATA_ID_KALMAN_VZ)
				  {
					  speed = can_current_msg.data;
				  }
				  else if(can_current_msg.id == DATA_ID_KALMAN_Z)
				  {
					  altitude = can_current_msg.data;
				  }

				  command_aerobrake_controller (altitude, speed); // TO UPDATE WITH THE REAL VARIABLE !!

				  osDelay(1);
				  break;
			  }
			  else
			  {
				  currentState = STATE_PRIMARY;
				  break;
			  }

		  case STATE_PRIMARY:
			  led_set_TK_rgb(led_AB_id, 100, 100, 60);
			  if( !(can_current_msg.id == CAN_ID_STATE && can_current_msg.data == STATE_SECONDARY) )
			  {
				  can_readFrame();

				  full_close();

				  osDelay(100);
				  break;
			  }
			  else
			  {
				  currentState = STATE_SECONDARY;
				  break;
			  }

		  case STATE_SECONDARY:
			  led_set_TK_rgb(led_AB_id, 200, 0, 100);
			  if( !(can_current_msg.id == CAN_ID_STATE && can_current_msg.data == STATE_TOUCHDOWN) )
			  {
				  can_readFrame();

				  full_close();

				  osDelay(100);
				  break;
			  }
			  else
			  {
				  currentState = STATE_TOUCHDOWN;
				  break;
			  }

		  case STATE_TOUCHDOWN:
			  led_set_TK_rgb(led_AB_id, 10, 10, 2);

			  full_close();
			  osDelay(1000);

			  break;


	  }
      osDelay (1);
    }

  osDelay (1000);

  /*
   command_aerobrake_controller (1500.0, 100.0); // Should be full open
   command_aerobrake_controller (200.0, 100.0); // Should be full close
   command_aerobrake_controller (238.0, 131.0); // Should be somewhere in between
   command_aerobrake_controller (500.0, 80.0); // Should be full close
   */

  /*
  while (currentState < STATE_COAST)
    {
      osDelay (1);
    }

  for (;;)
    {

      if ((HAL_GetTick () - LIFTOFF_TIME) > 17000)
        {
          //full_close ();
          break;
        }

      if (currentState == STATE_COAST)
        {
          //command_aerobrake_controller (altitude_estimate, air_speed_state_estimate); // Should be full close

          uint32_t elapsed_time = HAL_GetTick () - LIFTOFF_TIME;

          if (elapsed_time > AB_T1_DEPLOYMENT)
            {
              if (elapsed_time < AB_T2_CLOSE)
                {
                  full_open ();
                  shortBip();
                }
              else
                {
                  shortBip();
//                  full_close ();
                  break;
                }
            }

        }
      else if (currentState > STATE_PRIMARY)
        {
//          full_close ();
          break;
        }

      int elapsed = HAL_GetTick () - lastAirbrakesUpdate;
      if (elapsed < 100)
        {
          osDelay (100 - elapsed);
        }
      lastAirbrakesUpdate = HAL_GetTick ();
    }
*/

  for (;;)
    {
      osDelay (portMAX_DELAY);
    }
}
