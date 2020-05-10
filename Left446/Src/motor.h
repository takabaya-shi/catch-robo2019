/*
 * motor.h
 *
 *  Created on: 2019/09/07
 *      Author: tomok
 */

#ifndef MOTOR_H_
#define MOTOR_H_

//#include "math.h"
#include "stm32f4xx_hal.h"
//#include "struct.h"



/*-----------------------------------------------
 * ���W��DC���[�^(r, theta, z)
-----------------------------------------------*/
void CoordinateSetDuty(float duty,int MD_ID);
void CoordinateEnable(void);
void CoordinateDisable(void);
void CoordinateSetDirection(float duty,int MD_ID);


//���W��DC���[�^�^�C�}�n���h��
#define MD1_TIM_HANDLER		htim1
#define MD2_TIM_HANDLER		htim1
#define MD3_TIM_HANDLER		htim8
#define MD4_TIM_HANDLER		htim8

//PWM��ARR�l�iMAX�̒l�j
#define PWM_ARR 			1000.0f
//���[�^PWM�`�����l��
#define MD1_PWM_TIM_CH				TIM_CHANNEL_2
#define MD2_PWM_TIM_CH				TIM_CHANNEL_1
#define MD3_PWM_TIM_CH				TIM_CHANNEL_4
#define MD4_PWM_TIM_CH				TIM_CHANNEL_3

//DC���[�^��]����GPIO
#define MD1_1_PORT				GPIOA
#define MD1_1_PIN				GPIO_PIN_12
#define MD1_2_PORT				GPIOA
#define MD1_2_PIN				GPIO_PIN_11

#define MD2_1_PORT				GPIOC
#define MD2_1_PIN				GPIO_PIN_7
#define MD2_2_PORT				GPIOC
#define MD2_2_PIN				GPIO_PIN_6

#define MD3_1_PORT				GPIOB
#define MD3_1_PIN				GPIO_PIN_15
#define MD3_2_PORT				GPIOB
#define MD3_2_PIN				GPIO_PIN_14

#define MD4_1_PORT				GPIOB
#define MD4_1_PIN				GPIO_PIN_13
#define MD4_2_PORT				GPIOB
#define MD4_2_PIN				GPIO_PIN_12

//���^�h����ID
#define MD1_ID		1		//�����̃R���x�A
#define MD2_ID		2		//��O���̃R���x�A
#define MD3_ID		3		//�v�b�V���[
#define MD4_ID		4		//�d����

//���[�^�u���[�L
#define MOTOR_BRAKE					0.0f


#endif /* MOTOR_H_ */
