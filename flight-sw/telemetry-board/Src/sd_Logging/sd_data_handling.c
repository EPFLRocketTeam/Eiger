/*
 * data_handling.c
 *
 *  Created on: 19 Apr 2018
 *      Author: Cl�ment Nussbaumer
 */

#include <Misc/Common.h>
#include <Misc/sd_sync.h>

#include <string.h>

extern osMessageQId sdLoggingQueueHandle;
char buffer[2048];

void TK_sd_data (void const * args)
{
  osDelay (5000);

  for (;;)
    {

      uint32_t measurement_time = HAL_GetTick ();

      int i = -14;
      float fl = -22.14;

      sprintf (buffer, "Test print %d \t %f\n", i++ , fl++);

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
          osDelay (100 - elapsed);
        }
    }
}

