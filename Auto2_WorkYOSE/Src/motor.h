/*
 * motor.h
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#ifndef MOTOR_H_
#define MOTOR_H_


//#include "math.h"
#include "stm32f3xx_hal.h"
//#include "struct.h"



/*-----------------------------------------------
 * ���W��DC���[�^(r, theta, z)
-----------------------------------------------*/
void CoordinateSetDuty(float duty,int MD_ID);
void CoordinateEnable(void);
void CoordinateDisable(void);
void CoordinateSetDirection(float duty,int MD_ID);
void CoordinateSetPosPID(void);

//���W��DC���[�^�^�C�}�n���h��
#define MD_X_TIM_HANDLER		htim3
#define MD_Y_TIM_HANDLER		htim3

//PWM��ARR�l�iMAX�̒l�j
#define PWM_ARR 			1000.0f
//���[�^PWM�`�����l��
#define MD_X_PWM_TIM_CH				TIM_CHANNEL_4
#define MD_Y_PWM_TIM_CH				TIM_CHANNEL_2

//DC���[�^��]����GPIO
#define MD_X_1_PORT				GPIOA
#define MD_X_1_PIN				GPIO_PIN_6
#define MD_X_2_PORT				GPIOA
#define MD_X_2_PIN				GPIO_PIN_7

#define MD_Y_1_PORT				GPIOB
#define MD_Y_1_PIN				GPIO_PIN_0
#define MD_Y_2_PORT				GPIOB
#define MD_Y_2_PIN				GPIO_PIN_1

//���^�h����ID
#define MD_X_ID		3		//���[�N�񂹍��E�iX���j
#define MD_Y_ID		4		//���[�N�񂹉���O�iY���j

//���[�^�u���[�L
#define MOTOR_BRAKE					0.0f


#endif /* MOTOR_H_ */
