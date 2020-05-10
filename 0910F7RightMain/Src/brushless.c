/*
 * brushless.c
 *
 *  Created on: 2019/09/12
 *      Author: tomok
 */

#include "brushless.h"
#include "stm32f7xx_hal.h"

extern TIM_HandleTypeDef htim13;

float BRUSHLESS_PWM = 500.0f;

//�u���V���X���L�����u���[�V��������֐�
void BrushLessEnable(void){
	  HAL_TIM_PWM_Start(&BRUSHLESS_PWM_TIM,BRUSHLESS_PWM_TIM_CNANNEL);
	  __HAL_TIM_SET_COMPARE(&BRUSHLESS_PWM_TIM, BRUSHLESS_PWM_TIM_CNANNEL, 	1000);
	  HAL_Delay(3000);

	  __HAL_TIM_SET_COMPARE(&BRUSHLESS_PWM_TIM, BRUSHLESS_PWM_TIM_CNANNEL, 	500);
	    HAL_Delay(3000);
}

void BrushLessDisable(void){
	  __HAL_TIM_SET_COMPARE(&BRUSHLESS_PWM_TIM, BRUSHLESS_PWM_TIM_CNANNEL, 	500);
	  HAL_TIM_PWM_Stop(&BRUSHLESS_PWM_TIM,BRUSHLESS_PWM_TIM_CNANNEL);
}

//�O���[�o���ϐ��̒l�ɉ����ďo�͂���
void BrushLessSet(void){
	  //int PWM;
	  //int SPEED = 625;
	  //PWM = fmaxf(fminf(SPEED,625),500);
	  __HAL_TIM_SET_COMPARE(&BRUSHLESS_PWM_TIM, BRUSHLESS_PWM_TIM_CNANNEL, 	BRUSHLESS_PWM);
}

void BrushLessStop(void){
	  int PWM;
	  int SPEED = 500;
	  PWM = fmaxf(fminf(SPEED,625),500);
	  __HAL_TIM_SET_COMPARE(&BRUSHLESS_PWM_TIM, BRUSHLESS_PWM_TIM_CNANNEL, 	PWM);
}
