/*
 * data_handling.c
 *
 *  Created on: 19 Apr 2018
 *      Author: Cl�ment Nussbaumer
 */

#include <Misc/Common.h>
#include <Misc/sd_sync.h>


extern osMessageQId sdLoggingQueueHandle;
char buffer[2048];

void TK_sd_data (void const * args)
{
  osDelay (5000);

  uint32_t lastImuSeqNumber = 0, lastBaroSeqNumber = 0, telemetrySeqNumber = 0;

  for (;;)
    {

      uint32_t measurement_time = HAL_GetTick ();

      // IMU_data* imu_data = &IMU_buffer[currentImuSeqNumber % CIRC_BUFFER_SIZE];
      // BARO_data* baro_data = &BARO_buffer[currentBaroSeqNumber % CIRC_BUFFER_SIZE];

      lastImuSeqNumber = currentImuSeqNumber;
      lastBaroSeqNumber = currentBaroSeqNumber;

      int i = -14;
      float fl = -22.14;

      sprintf (buffer, "Test print %d \t %f", i++ , fl++);

      int message_length = strlen (buffer);
      if (message_length > 0)
        {
          void* message = pvPortMalloc (message_length + 1);
          if (message != NULL)
            {
              memcpy (message, buffer, message_length + 1); //include the trailing NULL char
              String_Message mess =
                { .ptr = message, .size = message_length };
              osMessagePut (sdLoggingQueueHandle, (uint32_t) &mess, 50);
            }
        }

      uint32_t elapsed = HAL_GetTick () - measurement_time;
      if (elapsed < 10)
        {
          osDelay (10 - elapsed);
        }
    }
}

