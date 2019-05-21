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

#define MAX_FOLDER_NUMBER 1000
volatile bool new_sd_data_ready = 0;

FIL sensorsFile, eventsFile;
const TCHAR sensor_file_header[] = "CANSeq\tTimestamp[ms]\tID\tData\r\n";
const TCHAR events_file_header[] = "NOT USED timestamp, event_description\r\n";

volatile char sd_buffer[2048];

int led_sdcard_id;

osStatus initSdFile ()
{
  MX_FATFS_Init ();
  led_sdcard_id = led_register_TK();

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
  osDelay (200);

  if (initSdFile () != osOK)
    {
	  while (1) {
		  led_set_TK_rgb(led_sdcard_id, 50, 0, 0);
		  osDelay (1000);
	  }
    }

  UINT bytes_written = 0;
  f_write (&sensorsFile, sensor_file_header, strlen (sensor_file_header), &bytes_written);
  f_write (&eventsFile, events_file_header, strlen (events_file_header), &bytes_written);

  uint32_t lastSync = HAL_GetTick ();

  f_sync (&sensorsFile);
  f_sync (&eventsFile);
  lastSync = HAL_GetTick ();

  osDelay (500);
  FRESULT result = 0;

  for (;;)
    {
      if (new_sd_data_ready) {
    	  int line_size = strlen (sd_buffer);
    	  result |= f_write (&sensorsFile, sd_buffer, line_size, &bytes_written);
    	  new_sd_data_ready = 0;

    	  if ((HAL_GetTick () - lastSync) > 1000) // synchronization every second with the SD card.
    	  {
    		  result |= f_sync (&sensorsFile);
    		  lastSync = HAL_GetTick ();
    	  }
      }

      if (result == FR_OK) {
    	  led_set_TK_rgb(led_sdcard_id, 0, 50, 0);
      } else {
    	  led_set_TK_rgb(led_sdcard_id, 255, 0 ,0);
      }
      osDelay(1);
    }
}
