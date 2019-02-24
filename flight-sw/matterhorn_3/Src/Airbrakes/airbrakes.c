/*
 * airbrakes.c
 *
 *  Created on: 27 Apr 2018
 *      Author: ebrunner
 */

#include "stm32f4xx_hal.h"
#include "Misc/Common.h"
#include <cmsis_os.h>

#include "Airbrakes/controller_functions.h"
#include <Misc/rocket_constants.h>

extern volatile uint32_t flight_status;

osStatus motorDetected = osErrorOS;
uint8_t faulhaber_welcome[9];

void TK_ab_controller (void const * argument)
{
  airbrakes_angle = 0;
  flight_status = 0;
  uint32_t lastAirbrakesUpdate = 0;

#if (SIMULATION == 0)

  osDelay (2000);

  aerobrakes_control_init ();

  for (int i = 0; i < 5; ++i)
    {
      aerobrake_helloworld ();
      osDelay (500);
    }

  osDelay (1000);

  /*
   command_aerobrake_controller (1500.0, 100.0); // Should be full open
   command_aerobrake_controller (200.0, 100.0); // Should be full close
   command_aerobrake_controller (238.0, 131.0); // Should be somewhere in between
   command_aerobrake_controller (500.0, 80.0); // Should be full close
   */

#endif

  while (currentState < STATE_COAST)
    {
      osDelay (1);
    }

  for (;;)
    {

      /*if ((HAL_GetTick () - LIFTOFF_TIME) > 17000)
        {
          //full_close ();
          break;
        }*/

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

  for (;;)
    {
      osDelay (portMAX_DELAY);
    }
}
