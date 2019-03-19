/*
 * Common.h
 *
 *  Created on: 4 Apr 2018
 *      Author: Cl�ment Nussbaumer
 */

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "datastructs.h"
#include <stm32f4xx_hal.h>

#define CIRC_BUFFER_SIZE 8
#define CCMRAM __attribute__((section(".ccmram")))

#define SIMULATION 0 // 0 production mode, 1 simulation mode
#define NOSECONE

//#define FLAPPYFLAPPY
#define SHURIKEN

#if defined(FLAPPYFLAPPY) && defined(SHURIKEN)
#error SHURIKEN and FLAPPYFLAPPY cannot be both defined
#endif

#if defined(NOSECONE) && defined(CENTRALBODY)
#error CENTRALBODY and NOSECONE cannot be both defined
#endif

extern TIM_HandleTypeDef htim7;

/*
 * States decleration
 */

enum states
{
  STATE_CALIBRATION, STATE_IDLE, STATE_LIFTOFF, STATE_COAST, STATE_PRIMARY, STATE_SECONDARY, STATE_TOUCHDOWN
};

volatile uint32_t flight_status;
volatile float32_t airbrakes_angle;
extern volatile float32_t air_speed_state_estimate, altitude_estimate;

volatile uint8_t currentState;
volatile uint32_t LIFTOFF_TIME;

volatile uint32_t currentImuSeqNumber;
volatile uint32_t currentBaroSeqNumber;
volatile uint32_t currentBaroTimestamp;
volatile uint32_t currentPitotSeqNumber;


extern IMU_data IMU_buffer[];
extern BARO_data BARO_buffer[];

static inline IMU_data* getCurrentIMU_data ()
{
  return &IMU_buffer[currentImuSeqNumber % CIRC_BUFFER_SIZE];
}

static inline BARO_data* getCurrentBARO_data ()
{
  return &BARO_buffer[currentBaroSeqNumber % CIRC_BUFFER_SIZE];
}

static inline void uint8ToFloat (uint8_t* uint8Ptr, float* floatPtr)
{
  uint8_t* floatAsUintPtr = (uint8_t*) floatPtr;
  floatAsUintPtr[0] = uint8Ptr[3];
  floatAsUintPtr[1] = uint8Ptr[2];
  floatAsUintPtr[2] = uint8Ptr[1];
  floatAsUintPtr[3] = uint8Ptr[0];
}

static inline int32_t mod (int32_t x, int32_t n)
{
  int32_t r = x % n;
  return r < 0 ? r + n : r;
}

//TODO: use a timer with a bigger period
static inline void delayUs (uint32_t delay)
{
  uint32_t start = __HAL_TIM_GET_COUNTER(&htim7);
  int32_t elapsed;

  while ((elapsed = mod (((int32_t) __HAL_TIM_GET_COUNTER(&htim7) - start), htim7.Init.Period) < delay))
    ;
}

static inline void floatToUint8 (uint8_t* uint8Ptr, float* floatPtr)
{
  uint8_t* floatAsUintPtr = (uint8_t*) floatPtr;
  uint8Ptr[0] = floatAsUintPtr[3];
  uint8Ptr[1] = floatAsUintPtr[2];
  uint8Ptr[2] = floatAsUintPtr[1];
  uint8Ptr[3] = floatAsUintPtr[0];
}

static inline float32_t abs_fl32 (float32_t v)
{
  return (v >= 0) ? v : -v;
}

static inline float32_t array_mean(float32_t* array, uint8_t arraySize)
{
  uint8_t i;
  float32_t sum = 0.0;

  for(i = 0 ; i < arraySize ; i++)
    {
      sum += array[i];
    }

  return sum/arraySize;
}

#ifdef __cplusplus
 }
#endif

#endif /* INCLUDE_COMMON_H_ */
