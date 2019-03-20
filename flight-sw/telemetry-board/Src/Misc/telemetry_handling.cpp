/*
 * data_handling.c
 *
 *  Created on: 19 Apr 2018
 *      Author: Cl�ment Nussbaumer
 */

#include "cmsis_os.h"

#include "Misc/Common.h"

#include "Misc/data_handling.h"
#include "Misc/datagram_builder.h"

#include "Telemetry/telemetry_protocol.h"
#include "Telemetry/simpleCRC.h"

extern osMessageQId xBeeQueueHandle;


void TK_telemetry_data (void const * args)
{
  uint32_t telemetrySeqNumber = 0;

  osDelay (800); //Wait for the first values to be written by the IMU and barometer.
  IMU_data imu_data = {{0.0,0.0,0.0},{0.0,0.0,0.0},0.0};
  BARO_data baro_data = {1000, 1000, 1000};

  for (;;)
    {
      uint32_t measurement_time = HAL_GetTick ();

      imu_data.acceleration.x +=0.1;
      if (imu_data.acceleration.x > 5) {
    	  imu_data.acceleration.x = -5;
      }

      baro_data.pressure -= 1;
      if (baro_data.pressure < 900) {
    	  baro_data.pressure = 1000;
      }
      baro_data.temperature = 20;

      float32_t pitot_press = 0;

      Telemetry_Message m = createTelemetryDatagram (&imu_data, &baro_data, pitot_press, measurement_time,
                                                     telemetrySeqNumber++);
      osMessagePut (xBeeQueueHandle, (uint32_t) &m, 50);

      osDelay (100 - (HAL_GetTick () - measurement_time));
    }
}

Telemetry_Message createTelemetryDatagram (IMU_data* imu_data, BARO_data* baro_data, float32_t pitot_press,
                                           uint32_t measurement_time, uint32_t telemetrySeqNumber)
{

  DatagramBuilder builder = DatagramBuilder (SENSOR_DATAGRAM_PAYLOAD_SIZE, TELEMETRY_ERT18, telemetrySeqNumber);

  // ## Beginning of datagram Payload ##
  // measurement time
  builder.write32<uint32_t> (measurement_time);

  builder.write32<float32_t> (imu_data->acceleration.x);
  builder.write32<float32_t> (imu_data->acceleration.y);
  builder.write32<float32_t> (imu_data->acceleration.z);

  builder.write32<float32_t> (1.0);
  builder.write32<float32_t> (0);
  builder.write32<float32_t> (0);

  builder.write32<float32_t> (baro_data->temperature);
  builder.write32<float32_t> (baro_data->pressure);

  builder.write32<float32_t> (0);

  return builder.finalizeDatagram ();
}
