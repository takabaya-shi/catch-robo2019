/*
 * CAN_main.c
 *
 *  Created on: 2019/09/03
 *      Author: tomok
 */

#include "main.h"
#include <stdio.h>
CAN_FilterTypeDef  sFilterConfig;

int my_CAN_Init(CAN_HandleTypeDef *hcan){
	  sFilterConfig.FilterBank = 0;
	  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	  sFilterConfig.FilterIdHigh = 0x456<<5;
	  sFilterConfig.FilterIdLow = 0x0000;
	  sFilterConfig.FilterMaskIdHigh = 0x0000;//0xFFE0;
	  sFilterConfig.FilterMaskIdLow = 0x0000;
	  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	  sFilterConfig.FilterActivation = ENABLE;
	  sFilterConfig.SlaveStartFilterBank = 14;
	  if(HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK)
	  {
	    /* Filter configuration Error */
	    Error_Handler();
	  }
	  if (HAL_CAN_Start(hcan) != HAL_OK)
	  {
	      /* Start Error */
		  printf("Start Error\n");
	      Error_Handler();
	  }
}

