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


void TK_data (void const * args)
{
  uint32_t telemetrySeqNumber = 0;

  osDelay (800); //Wait for the first values to be written by the IMU and barometer.

  for (;;)
    {
      uint32_t measurement_time = HAL_GetTick ();

      IMU_data* imu_data = NULL;
      BARO_data* baro_data = NULL;
      float32_t pitot_press = 0;

      Telemetry_Message m = createTelemetryDatagram (imu_data, baro_data, pitot_press, measurement_time,
                                                     telemetrySeqNumber++);
      osMessagePut (xBeeQueueHandle, (uint32_t) &m, 50);

      osDelay (15 - (HAL_GetTick () - measurement_time));
    }
}

Telemetry_Message createTelemetryDatagram (IMU_data* imu_data, BARO_data* baro_data, float32_t pitot_press,
                                           uint32_t measurement_time, uint32_t telemetrySeqNumber)
{

  DatagramBuilder builder = DatagramBuilder (SENSOR_DATAGRAM_PAYLOAD_SIZE, TELEMETRY_ERT18, telemetrySeqNumber);

  // ## Beginning of datagram Payload ##
  // measurement time
  builder.write32<uint32_t> (measurement_time);

  builder.write32<float32_t> (10);
  builder.write32<float32_t> (20);
  builder.write32<float32_t> (30);

  builder.write32<float32_t> (1);
  builder.write32<float32_t> (2);
  builder.write32<float32_t> (3);

  builder.write32<float32_t> (4);
  builder.write32<float32_t> (5);

  builder.write32<float32_t> (6);

  return builder.finalizeDatagram ();
}
