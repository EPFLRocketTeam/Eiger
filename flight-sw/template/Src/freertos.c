/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "led.h"
#include "Telemetry/xbee.h"
#include "Misc/Common.h"
#include "Misc/data_handling.h"
#include "airbrake/airbrake.h"
#include "Misc/sd_sync.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
int r=1000, g=0, b=0;
/* USER CODE BEGIN PD */


//#define AB_CONTROL
//#define SDCARD

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osThreadId sdWriteHandle;
osThreadId task_ABHandle;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId task_s1Handle;
osThreadId task_s2Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void TK_task_s1(void const * argument);
void TK_task_s2(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
#ifdef MAIN_BOARD
r=0, g=100, b=0;
#endif

#ifdef BLACK_BOX_BOARD
r=80, g=50, b=0;
#endif

#ifdef TELEMETRY_BOARD
r=0, g=0, b=100;
#endif

#ifdef AIRBRAKE_BOARD
r=100, g=0, b=100;
#endif

#ifdef DEBUG_BOARD
r=50, g=50, b=50;
#endif
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 256);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of task_s1 */
  osThreadDef(task_s1, TK_task_s1, osPriorityNormal, 0, 256);
  task_s1Handle = osThreadCreate(osThread(task_s1), NULL);

  /* definition and creation of task_s2 */
  osThreadDef(task_s2, TK_task_s2, osPriorityNormal, 0, 256);
  task_s2Handle = osThreadCreate(osThread(task_s2), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
#ifdef AB_CONTROL
  osThreadDef(task_AB, TK_ab_controller, osPriorityNormal, 0, 256);
  task_ABHandle = osThreadCreate(osThread(task_AB), NULL);
  ab_init(&huart1);
#endif

#ifdef SDCARD
  osThreadDef(sdWrite, TK_sd_sync, osPriorityBelowNormal, 0, 1024);
  sdWriteHandle = osThreadCreate(osThread(sdWrite), NULL);
#endif
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for FATFS */
  MX_FATFS_Init();

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	osDelay(100);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_TK_task_s1 */
/**
* @brief Function implementing the task_s1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TK_task_s1 */
void TK_task_s1(void const * argument)
{
  /* USER CODE BEGIN TK_task_s1 */
  led_set_rgb(r,g,b);
  osDelay(1000);

  /* Infinite loop */
  for(;;)
  {
	  led_set_rgb(r,g,b);
	  osDelay(100);
	  led_set_rgb(0,0,0);
	  osDelay(100);
  }
  /* USER CODE END TK_task_s1 */
}

/* USER CODE BEGIN Header_TK_task_s2 */
/**
* @brief Function implementing the task_s2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TK_task_s2 */
void TK_task_s2(void const * argument)
{
  /* USER CODE BEGIN TK_task_s2 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
  }
  /* USER CODE END TK_task_s2 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
