/*
 * encoder.c
 *
 *  Created on: 2019/08/05
 *      Author: tomok
 */

#include "encoder.h"

void EncEnable(void){
	HAL_TIM_Encoder_Start(&ENC_1_TIM_HANDLER,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&ENC_2_TIM_HANDLER,TIM_CHANNEL_ALL);

	ENC_1_TIM -> CNT	= 32768;
	ENC_2_TIM -> CNT	= 32768;

//	ENC_1_TIM -> CNT	= 0;
//	ENC_2_TIM -> CNT	= 0;
}

void EncDisable(void){
	HAL_TIM_Encoder_Stop(&ENC_1_TIM_HANDLER,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Stop(&ENC_2_TIM_HANDLER,TIM_CHANNEL_ALL);

//	ENC_1_TIM -> CNT	= 32768;
//	ENC_2_TIM -> CNT	= 32768;

	ENC_1_TIM -> CNT	= 0;
	ENC_2_TIM -> CNT	= 0;
}

void EncGetData(int16_t *enc_1_buf,int16_t *enc_2_buf){
	*enc_1_buf = ENC_1_TIM->CNT -32768;
	*enc_2_buf = ENC_2_TIM->CNT -32768;
//	*enc_1_buf = ENC_1_TIM->CNT;
//	*enc_2_buf = ENC_2_TIM->CNT;

	ENC_1_TIM -> CNT	= 32768;
	ENC_2_TIM -> CNT	= 32768;

//	ENC_1_TIM -> CNT	= 0;
//	ENC_2_TIM -> CNT	= 0;
}
