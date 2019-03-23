/*
 * sd_sync.c
 *
 *  Created on: 15 Nov 2018
 *      Author: Clément Nussbaumer
 */

#include <stdbool.h>
#include "cmsis_os.h"
#include "fatfs.h"
#include "led.h"

#include <Misc/datastructs.h>
#include <Misc/Common.h>

#include <string.h>

extern SD_HandleTypeDef hsd;

#define MAX_FOLDER_NUMBER 1000

extern osMessageQId sdLoggingQueueHandle;

volatile bool new_sd_data_ready = 0;

FIL sensorsFile, eventsFile;
const TCHAR sensor_file_header[] = "CANSeq\tTimestamp[ms]\tID\tData\r\n";
const TCHAR events_file_header[] = "NOT USED timestamp, event_description\r\n";
volatile char sd_buffer[2048];
uint8_t file_closed = 0;
int sdErrorCounter = 0;

osStatus initSdFile ()
{
  MX_FATFS_Init ();

  FRESULT res; /* FatFs function common result code */
  uint32_t byteswritten, bytesread; /* File write/read counts */

  //osDelay(portMAX_DELAY);

  for (int i = 3; i >= 0; i--)
    {
      if (disk_initialize (0) == 0)
        {
          break; //Initialization is valid
        }
      else
        {
          osDelay (300);
        }
    }

  if (disk_initialize (0) != 0)
    {
      //The disk is not initialized correctly.
      return osErrorResource;
    }

  /*##-2- Register the file system object to the FatFs module ##############*/
  if (f_mount (&SDFatFS, (TCHAR const*) SDPath, 0) != FR_OK)
    {
      /* FatFs Initialization Error */
      return osErrorResource;
    }
  else
    {
      TCHAR dir[20];
      for (int i = 0; i < MAX_FOLDER_NUMBER; i++)
        {
          sprintf (dir, "DATA%04d", i);
          FILINFO info;
          if (f_stat (dir, &info) != FR_OK)
            {
              f_mkdir (dir);
              break;
            }
        }
      TCHAR path[100];

      sprintf (path, "%s" "/" "sensors.txt", dir);
      if (f_open (&sensorsFile, path, FA_OPEN_APPEND | FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
        {
          /* 'STM32.TXT' file Open for write Error */
          return osErrorResource;
        }
      sprintf (path, "%s" "/" "events.txt", dir);
      if (f_open (&eventsFile, path, FA_OPEN_APPEND | FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
        {
          /* 'STM32.TXT' file Open for write Error */
          return osErrorResource;
        }

      return osOK;
    }
}

void TK_sd_sync (void const* pvArgs)
{
  init: osDelay (200);

  if (initSdFile () != osOK)
    {
	  led_set_rgb(255,0,50);
      osDelay (10 * 1000);
      goto init;
    }

  UINT bytes_written = 0;
  f_write (&sensorsFile, sensor_file_header, strlen (sensor_file_header), &bytes_written);
  f_write (&eventsFile, events_file_header, strlen (events_file_header), &bytes_written);

  uint32_t lastSync = HAL_GetTick ();
  uint32_t last_execution = 0;
  uint32_t elapsed;

  f_sync (&sensorsFile);
  f_sync (&eventsFile);
  lastSync = HAL_GetTick ();

  osDelay (500);
  FRESULT result = 0;

  int i = -14;

  for (;;)
    {
      result = 0;
      /*
       if (currentState == STATE_TOUCHDOWN && !file_closed)
       {
       f_close (&sensorsFile);
       f_close (&eventsFile);
       file_closed = 1;
       for (;;)
       {
       osDelay (portMAX_DELAY);
       }
       }

       osEvent event = osMessageGet (sdLoggingQueueHandle, 5);
       if (event.status != osEventMessage)
       {
       goto endOfLoop;
       }

       String_Message* m = event.value.p;
       vPortFree (m->ptr);
       */

      // ###############
      // Here you need to fetch the data and to print it.
      uint32_t measurement_time = HAL_GetTick ();
      if (new_sd_data_ready) {
      //sprintf (buffer, "%d\t\tTest print %d\t free heap:\t%d\n", measurement_time, i++, xPortGetFreeHeapSize ());

      // ###############

      int line_size = strlen (sd_buffer);
      if (line_size > 768 || line_size < 0)
        {
          goto endOfLoop;
        }
      result |= f_write (&sensorsFile, sd_buffer, line_size, &bytes_written);
      new_sd_data_ready = 0;
      if ((HAL_GetTick () - lastSync) > 1000) // synchronization every second with the SD card.
        {
          result |= f_sync (&sensorsFile);
          //result |= f_sync (&eventsFile);
          lastSync = HAL_GetTick ();
        }
      }

      endOfLoop: elapsed = HAL_GetTick () - last_execution;
      uint32_t delay = 20; // Delay of 50ms
      if (elapsed < delay)
        {
          osDelay (delay - elapsed);
        }
      last_execution = HAL_GetTick ();

      /*
       if (result != FR_OK)
       { // create a new file in case of problem.  ## does not work correctly yet
       f_close (&sensorsFile);
       f_close (&eventsFile);

       HAL_SD_DeInit (&hsd);

       osDelay (100);

       HAL_StatusTypeDef sd_state = HAL_SD_Init (&hsd);
       if (sd_state == MSD_OK)
       {
       if (HAL_SD_ConfigWideBusOperation (&hsd, SDIO_BUS_WIDE_4B) != HAL_OK)
       {
       sd_state = MSD_ERROR;
       }
       }

       break;
       }
       */

    }

  //we need to get outside the for loop to correctly deinitialize scope-local data.
  sdErrorCounter++;
  goto init;

}
