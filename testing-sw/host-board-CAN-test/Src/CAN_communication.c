/*
 * CAN_communication.c
 *
 *  Created on: Feb 23, 2019
 *      Author: Tim Lebailly
 */

#include "CAN_communication.h"

extern CAN_HandleTypeDef hcan1;
CAN_TxHeaderTypeDef   TxHeader;
CAN_RxHeaderTypeDef   RxHeader;
uint8_t               TxData[8];
uint8_t               RxData[8];
uint32_t              TxMailbox;
CAN_msg				  current_msg;

/*
 * Configures CAN protocol for 250kbit/s without interrupt for reading (only polling).
 */
void CAN_Config(uint32_t id)
{
  CAN_FilterTypeDef  sFilterConfig;

  /*##-1- Configure the CAN peripheral #######################################*/
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 9;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = ENABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
	_Error_Handler(__FILE__, __LINE__);
  }

  /*##-2- Configure the CAN Filter ###########################################*/
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
  sFilterConfig.SlaveStartFilterBank = 14;

  if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
	  _Error_Handler(__FILE__, __LINE__);
  }

  /*##-3- Start the CAN peripheral ###########################################*/
  if (HAL_CAN_Start(&hcan1) != HAL_OK)
  {
    /* Start Error */
	  _Error_Handler(__FILE__, __LINE__);
  }

  /*##-4- Activate CAN RX notification #######################################*/
//  if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
//  {
//    /* Notification Error */
//	  _Error_Handler(__FILE__, __LINE__);
//  }

  /*##-5- Configure Transmission process #####################################*/
  TxHeader.StdId = id;
  TxHeader.ExtId = id; // not needed
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = 8;
  TxHeader.TransmitGlobalTime = DISABLE;
}

/*
 * Sends a frame of 8 bytes (payload) on the CAN bus using our predefined protocol.
 * byte 0..3 --> some uint32_t
 * byte 4    --> data_id, see CAN_communication.h
 * byte 5..7 --> timestamp
 */
void setFrame(uint32_t data, uint8_t data_id, uint32_t timestamp) {
	TxData[0] = (uint8_t) (data >> 24);
	TxData[1] = (uint8_t) (data >> 16);
	TxData[2] = (uint8_t) (data >> 8);
	TxData[3] = (uint8_t) (data >> 0);
	TxData[4] = data_id;
	TxData[5] = (uint8_t) (timestamp >> 16);
	TxData[6] = (uint8_t) (timestamp >> 8);
	TxData[7] = (uint8_t) (timestamp >> 0);

	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK) {
		// deal with it (never fails)
	}
}

/*
 * Reads the CAN bus and sets global CAN_msg current_msg struct (see CAN_communication.h)
 * Returns the fill level when the function was called
 * This way, the caller knows if the variable current_msg was updated by the funciton call or not.
 *
 * byte 0..3 --> some uint32_t
 * byte 4    --> data_id, see CAN_communication.h
 * byte 5..7 --> timestamp
 */
uint32_t readFrame(void) {
	uint32_t fill_level = HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0);
	if (fill_level > 0) {
		HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, RxData);
		memcpy(&current_msg.data, RxData, 4);
		current_msg.id = RxData[4];
		//----------------------------------------------------------------------check if works
		uint8_t* ptr = (uint8_t*) &current_msg.timestamp;
		*ptr = 0;
		memcpy(&ptr[1], &RxData[5], 3);
		//----------------------------------------------------------------------check if works
	}
	return fill_level;
}
