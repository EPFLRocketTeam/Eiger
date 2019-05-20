/*
 * data_handling.c
 *
 *  Created on: 19 Apr 2018
 *      Author: Cl�ment Nussbaumer
 */

#include <Misc/Common.h>
#include <Misc/sd_sync.h>

#include <string.h>
#include <cmsis_os.h>


extern osMessageQId sdLoggingQueueHandle;
char buffer[1024];

void TK_sd_data (void const * args)
{
  osDelay (5000);

  for(;;){
      osDelay(portMAX_DELAY); // we don't use the remaining part of this task. dirty temporary hack to disable everything.
  }

  int i = -14;
  float fl = -22.14;

  for (;;)
    {

      uint32_t measurement_time = HAL_GetTick ();

      sprintf (buffer, "%d\t\tTest print %d \t \t %f\tfree heap:\t%d\n", measurement_time,i , fl,  xPortGetFreeHeapSize());

      int message_length = strlen (buffer);
      if (message_length > 0)
        {
          void* message = pvPortMalloc (message_length + 1);
          if (message != NULL)
            {
              memcpy (message, buffer, message_length + 1); //include the trailing NULL char
              String_Message mess =
                { .ptr = message, .size = message_length };
              osStatus result = osMessagePut (sdLoggingQueueHandle, (uint32_t) &mess, 50);
              if (result != osOK) {
                  // The queue is probably full, we need to free the allocated message!
                  // # THIS IS REALLY IMPORTANT, but there is smth that prvetns it from being usable.
                  vPortFree(mess.ptr);
              } else {
                  i++;
                  fl += 0.00014;
              }
            }
        }

      uint32_t elapsed = HAL_GetTick () - measurement_time;
      /*
       if (elapsed < 10)
        {
          osDelay (20 - elapsed);
        }
      */
    }
}

