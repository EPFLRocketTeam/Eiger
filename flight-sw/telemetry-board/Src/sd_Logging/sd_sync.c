/*
 * sd_sync.c
 *
 *  Created on: 15 Nov 2018
 *      Author: Clément Nussbaumer
 */

#include "cmsis_os.h"
#include "fatfs.h"

#include <Misc/datastructs.h>
#include <Misc/Common.h>

#define MAX_FOLDER_NUMBER 1000

extern osMessageQId sdLoggingQueueHandle;

FIL sensorsFile, eventsFile;
const TCHAR sensor_file_header[] =
    "Header file, to be changer\r\n";
const TCHAR events_file_header[] = "timestamp, event_description\r\n";
char buffer[2048];
uint8_t file_closed = 0;

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
          sprintf (dir, "DATA%02d", i);
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
  osDelay (200);

  if (initSdFile () != osOK)
    {
//TODO: change led color perhaps?
      for (;;)
        {
          osDelay (portMAX_DELAY);
        }
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

  osDelay (1500);

  for (;;)
    {

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
        }*/

      osEvent event = osMessageGet (sdLoggingQueueHandle, 5);
      if (event.status != osEventMessage)
        {
          goto endOfLoop;
        }

      String_Message* m = event.value.p;
      f_write (&sensorsFile, m->ptr, m->size, &bytes_written);
      vPortFree (m->ptr);

      if ((HAL_GetTick () - lastSync) > 1000)
        {
          f_sync (&sensorsFile);
          //f_sync (&eventsFile);
          lastSync = HAL_GetTick ();
        }

      endOfLoop: elapsed = HAL_GetTick () - last_execution;
      if (elapsed < 5)
        {
          osDelay (5 - elapsed);
        }
      last_execution = HAL_GetTick ();
    }
}
