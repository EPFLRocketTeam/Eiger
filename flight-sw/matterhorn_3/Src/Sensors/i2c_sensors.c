/*
 * abs_p.c
 *
 *  Created on: 17 Apr 2018
 *      Author: Cl�ment Nussbaumer
 */

/*
 * Code based on this library: https://github.com/freetronics/BaroSensor/blob/master/BaroSensor.cpp
 */

#include <Sensors/BMP280/bmp280.h>
#include <Sensors/BNO055/bno055.h>
#include <Sensors/i2c_sensors.h>
#include <Misc/datastructs.h>
#include "stm32f4xx_hal.h"
#include "Misc/Common.h"

#if(SIMULATION == 1)
#include <Misc/SimData.h>
#endif
#include <Misc/rocket_constants.h>

extern I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef* hi2c;
extern osSemaphoreId i2cSensorsSemHandle;
extern BARO_data BARO_buffer[];

#define I2C_TIMEOUT 10 //ms

#define MAX_TEMPERATURE 85
#define MIN_TEMPERATURE -40

#define MAX_PRESSURE 1200
#define MIN_PRESSURE 100

struct bmp280_dev bmp;
uint8_t meas_dur;
char buf[200];

//# BNO055

struct bno055_accel_t accel_xyz;
struct bno055_mag_t mag_xyz;
struct bno055_gyro_t gyro_xyz;
struct bno055_accel_float_t f_accel_xyz;
struct bno055_gyro_float_t f_gyro_xyz;
struct bno055_mag_float_t f_mag_xyz;

struct bno055_t bno055;

int8_t stm32_i2c_read (uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  HAL_I2C_Mem_Read_DMA (hi2c, dev_id << 1, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len);
  return osSemaphoreWait (i2cSensorsSemHandle, I2C_TIMEOUT);
}

int8_t stm32_i2c_write (uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  HAL_I2C_Mem_Write (hi2c, dev_id << 1, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, I2C_TIMEOUT);
}

void stm32_delay_ms (uint32_t period)
{
  osDelay (period);
}

extern UART_HandleTypeDef huart2;

void initI2cDevices ()
{
  hi2c = &hi2c1;

  // ######## BMP280

  int8_t rslt = BMP280_OK;

  bmp.dev_id = BMP280_I2C_ADDR_PRIM;
  bmp.intf = BMP280_I2C_INTF;
  bmp.read = &stm32_i2c_read;
  bmp.write = &stm32_i2c_write;
  bmp.delay_ms = &stm32_delay_ms;

  rslt = bmp280_init (&bmp);

  struct bmp280_config conf;

  /* Always read the current settings before writing, especially when
   * all the configuration is not modified
   */
  rslt = bmp280_get_config (&conf, &bmp);
  /* Check if rslt == BMP280_OK, if not, then handle accordingly */

  /* Overwrite the desired settings */
  conf.filter = BMP280_FILTER_OFF;
  conf.os_pres = BMP280_OS_8X;
  conf.os_temp = BMP280_OS_1X;
  conf.odr = BMP280_ODR_0_5_MS;

  rslt = bmp280_set_config (&conf, &bmp);
  /* Check if rslt == BMP280_OK, if not, then handle accordingly */

  /* Always set the power mode after setting the configuration */
  rslt = bmp280_set_power_mode (BMP280_NORMAL_MODE, &bmp);
  /* Check if rslt == BMP280_OK, if not, then handle accordingly */

  meas_dur = bmp280_compute_meas_time (&bmp);

  // ######## BMNO055

  bno055.bus_write = &stm32_i2c_write;
  bno055.bus_read = &stm32_i2c_read;
  bno055.delay_msec = &stm32_delay_ms;
  bno055.dev_addr = BNO055_I2C_ADDR1;

  s32 comres = bno055_init (&bno055);

  uint8_t power_mode = BNO055_POWER_MODE_NORMAL;
  comres += bno055_set_power_mode (power_mode);

  comres += bno055_set_operation_mode (BNO055_OPERATION_MODE_AMG);
  bno055_set_accel_range (BNO055_ACCEL_RANGE_16G);
}

uint32_t failedReading = 0;

extern int startSimulation;

void TK_fetch_i2c ()
{
#if(SIMULATION == 1)

  while (!startSimulation)
    {
      osDelay (10);
    }

  // Save initialization time to synchronize program clock with data
  float32_t initial_sim_time = SimData[0][SIM_TIMESTAMP] - HAL_GetTick ();
  uint32_t sensorCounter = 0;

  // Populate first sensor structure
  BARO_data* newBaroData = &BARO_buffer[(currentBaroSeqNumber + 1) % CIRC_BUFFER_SIZE];
  newBaroData->temperature = 0;
  newBaroData->pressure = 0;
  newBaroData->altitude = SimData[sensorCounter][SIM_ALTITUDE];

  PITOT_buffer[(currentPitotSeqNumber + 1) % CIRC_BUFFER_SIZE] = 0.0f;
  currentBaroSeqNumber++;
  sensorCounter++;
  currentPitotSeqNumber++;

  for (;;)
    {
      if ((sensorCounter < SIM_TAB_HEIGHT - 1)
          && ((HAL_GetTick () - (SimData[sensorCounter][SIM_TIMESTAMP] - initial_sim_time)) > 0))
        {
          // change sensor data
          // create artificial sensor structure
          BARO_data* newBaroData = &BARO_buffer[(currentBaroSeqNumber + 1) % CIRC_BUFFER_SIZE];
          //populate data
          newBaroData->temperature = 0;
          newBaroData->pressure = SimData[sensorCounter][SIM_PRESSURE];
          newBaroData->altitude = SimData[sensorCounter][SIM_ALTITUDE];

          PITOT_buffer[(currentPitotSeqNumber++) % CIRC_BUFFER_SIZE] = SimData[sensorCounter][SIM_VELOCITYX];
          //increment counters
          currentBaroSeqNumber++;
          currentBaroTimestamp = HAL_GetTick();

          sensorCounter++;
        }
      osDelay (SimData[sensorCounter][SIM_TIMESTAMP] - SimData[sensorCounter - 1][SIM_TIMESTAMP] - 1);
    }

# else
  osSemaphoreWait (i2cSensorsSemHandle, 1); // make sure the semaphore is taken at the start of the loop

  osDelay (500);

  initI2cDevices ();

  uint32_t samplingStart, elapsed;
  struct bmp280_uncomp_data ucomp_data;
  int8_t rslt = BMP280_OK;
  s32 comres;

  for (;;)
    {

      samplingStart = HAL_GetTick ();

      rslt = bmp280_get_uncomp_data (&ucomp_data, &bmp);
      if (rslt != BMP280_OK)
        {
          goto IMU;
        }

      int32_t temp32 = bmp280_comp_temp_32bit (ucomp_data.uncomp_temp, &bmp);
      uint32_t pres32 = bmp280_comp_pres_32bit (ucomp_data.uncomp_press, &bmp);
      uint32_t pres64 = bmp280_comp_pres_64bit (ucomp_data.uncomp_press, &bmp);
      float temp = (float) bmp280_comp_temp_double (ucomp_data.uncomp_temp, &bmp);
      double pres = bmp280_comp_pres_double (ucomp_data.uncomp_press, &bmp);

      //float temp = (float) bmp280_comp_temp_double (ucomp_data.uncomp_temp, &bmp);
      //float press = (float) bmp280_comp_pres_double (ucomp_data.uncomp_press, &bmp) / 100.0;
      /*
       int written = sprintf (buf, "UT: %d, UP: %d, T32: %d, P32: %d, P64: %d, P64N: %d, T: %f, P: %f\r\n",
       ucomp_data.uncomp_temp, ucomp_data.uncomp_press, temp32, pres32, pres64, pres64 / 256,
       temp, pres);
       if (written > 180)
       {
       HAL_UART_Transmit_DMA (&huart2, buf, strlen (buf));
       }
       */

      BARO_data* new_data = &BARO_buffer[(currentBaroSeqNumber + 1) % CIRC_BUFFER_SIZE];
      new_data->pressure = pres/100.0;
      new_data->temperature = temp;
      new_data->altitude = altitudeFromPressure (pres/100.0);

#if DEBUG
      sprintf (buf, "T: %f, P: %f\r\n", temp, press);
      HAL_UART_Transmit_DMA (&huart2, buf, strlen (buf));
#endif

      IMU: comres = 0;
      comres += bno055_convert_float_accel_xyz_mg (&f_accel_xyz);
      comres += bno055_convert_float_mag_xyz_uT (&f_mag_xyz);
      comres += bno055_convert_float_gyro_xyz_rps (&f_gyro_xyz);

      IMU_data* new_imu_data = &IMU_buffer[(currentImuSeqNumber + 1) % CIRC_BUFFER_SIZE];
      new_imu_data->acceleration.x = f_accel_xyz.x / 1000.0;
      new_imu_data->acceleration.y = f_accel_xyz.y / 1000.0;
      new_imu_data->acceleration.z = f_accel_xyz.z / 1000.0;

      new_imu_data->gyro_rps.x = f_gyro_xyz.x;
      new_imu_data->gyro_rps.y = f_gyro_xyz.y;
      new_imu_data->gyro_rps.z = f_gyro_xyz.z;

      new_imu_data->mag_uT.x = f_mag_xyz.x;
      new_imu_data->mag_uT.y = f_mag_xyz.y;
      new_imu_data->mag_uT.z = f_mag_xyz.z;

      currentBaroSeqNumber++;
      currentImuSeqNumber++;

      osDelay(10);
    }

#endif
}

inline float altitudeFromPressure (float pressure_hPa)
{
  float altitude = 44330 * (1.0 - pow (pressure_hPa / ADJUSTED_SEA_LEVEL_PRESSURE, 0.1903));
  return altitude;
}

/*
 void HAL_I2C_MasterTxCpltCallback (I2C_HandleTypeDef *hi2c)
 {
 osSemaphoreRelease (pressureSensorI2cSemHandle);
 }
 */

/*void HAL_I2C_MasterRxCpltCallback (I2C_HandleTypeDef *hi2c)
 {
 osSemaphoreRelease (i2cSensorsSemHandle);
 }
 */

void HAL_I2C_MemTxCpltCallback (I2C_HandleTypeDef *hi2c)
{
  osSemaphoreRelease (i2cSensorsSemHandle);
}

void HAL_I2C_MemRxCpltCallback (I2C_HandleTypeDef *hi2c)
{
  osSemaphoreRelease (i2cSensorsSemHandle);
}

/*
 void HAL_I2C_ErrorCallback (I2C_HandleTypeDef *hi2c)
 {
 osSemaphoreRelease (i2cSensorsSemHandle);
 }

 void HAL_I2C_AbortCpltCallback (I2C_HandleTypeDef *hi2c)
 {
 //osSemaphoreRelease (i2cSensorsSemHandle);
 }
 */
