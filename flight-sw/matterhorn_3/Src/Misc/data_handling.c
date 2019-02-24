/*
 * data_handling.c
 *
 *  Created on: 19 Apr 2018
 *      Author: Cl�ment Nussbaumer
 */

#include "cmsis_os.h"
#include "fatfs.h"

#include <Misc/Common.h>
#include <Misc/data_handling.h>

#define MAX_FOLDER_NUMBER 1000

extern IMU_data IMU_buffer[];
extern BARO_data BARO_buffer[];

extern osMessageQId xBeeQueueHandle;

extern int startSimulation;
extern volatile float32_t high_range_pressure;

FIL sensorsFile, eventsFile;
const TCHAR sensor_file_header[] =
    "Seq num, timestamp, pressure, temperature, altitude, acc (mg) xyz, gyro(rps) xyz, mag(uT) xyz\r\n";
const TCHAR events_file_header[] = "timestamp, event_description\r\n";
char buffer[2048];
uint8_t file_closed = 0;

extern struct bno055_accel_float_t f_accel_xyz;
extern struct bno055_gyro_float_t f_gyro_xyz;
extern struct bno055_mag_float_t f_mag_xyz;

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
      SD_Error ();
      return osErrorResource;
    }

  /*##-2- Register the file system object to the FatFs module ##############*/
  if (f_mount (&SDFatFS, (TCHAR const*) SDPath, 0) != FR_OK)
    {
      /* FatFs Initialization Error */
      SD_Error ();
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
          SD_Error ();
          return osErrorResource;
        }
      sprintf (path, "%s" "/" "events.txt", dir);
      if (f_open (&eventsFile, path, FA_OPEN_APPEND | FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
        {
          /* 'STM32.TXT' file Open for write Error */
          SD_Error ();
          return osErrorResource;
        }

      return osOK;
    }
}

void SD_Error ()
{
  /*
   uint8_t repeat = 1;
   while (repeat--)
   {
   HAL_GPIO_WritePin (BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
   osDelay (75);
   HAL_GPIO_WritePin (BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
   osDelay (75);
   }
   */
}

void TK_data (void const * args)
{
  osDelay (200);

  if (initSdFile () != osOK)
    {
      HAL_GPIO_WritePin (BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
      osDelay (200);
      HAL_GPIO_WritePin (BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
      osDelay (200);
      HAL_GPIO_WritePin (BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
      osDelay (200);
      HAL_GPIO_WritePin (BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);

      for (;;)
        {
          osDelay (portMAX_DELAY);
        }
    }
  else
    {
      longBip ();
    }

  uint32_t lastImuSeqNumber = 0, lastBaroSeqNumber = 0, telemetrySeqNumber = 0;
  UINT bytes_written = 0;
  f_write (&sensorsFile, sensor_file_header, strlen (sensor_file_header), &bytes_written);
  f_write (&eventsFile, events_file_header, strlen (events_file_header), &bytes_written);

  uint32_t lastSync = HAL_GetTick ();

  f_sync (&sensorsFile);
  f_sync (&eventsFile);
  lastSync = HAL_GetTick ();

  osDelay (1500);

  for (;;)
    {

      /*TODO: Improvement: a task should be responsible for creating each line entry using the sprintf function.
       * It should then send these new lines to a queue. Another task (e.g. sd_task) then should emtpy the queue and sync the files.
       * This way you can have a constant sampling rate, which is not guaranteed here if the SD card is not fast enough.
       */

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
      uint32_t measurement_time = HAL_GetTick ();

      IMU_data* imu_data = &IMU_buffer[currentImuSeqNumber % CIRC_BUFFER_SIZE];
      BARO_data* baro_data = &BARO_buffer[currentBaroSeqNumber % CIRC_BUFFER_SIZE];

      lastImuSeqNumber = currentImuSeqNumber;
      lastBaroSeqNumber = currentBaroSeqNumber;

      sprintf (buffer, "%lu, %lu, "
               "%f, %f, %f, "
               "%f, %f, %f, "
               "%f, %f, %f, "
               "%f, %f, %f\r\n",
               telemetrySeqNumber++, measurement_time, baro_data->pressure, baro_data->temperature, baro_data->altitude,
               imu_data->acceleration.x, imu_data->acceleration.y, imu_data->acceleration.z, imu_data->gyro_rps.x,
               imu_data->gyro_rps.y, imu_data->gyro_rps.z, imu_data->mag_uT.x, imu_data->mag_uT.y, imu_data->mag_uT.z);

      f_write (&sensorsFile, buffer, strlen (buffer), &bytes_written);

      if (HAL_GetTick () - lastSync > 5000)
        {
          f_sync (&sensorsFile);
          //f_sync (&eventsFile);
          lastSync = HAL_GetTick ();
        }

      uint32_t elapsed = HAL_GetTick () - measurement_time;
      if (elapsed < 20)
        {
          osDelay (20 - elapsed);
        }
    }
}

