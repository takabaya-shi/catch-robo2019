/*
 * motor.h
 *
 *  Created on: 2019/08/17
 *      Author: tomok
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "math.h"
#include "stm32f4xx_hal.h"
#include "struct.h"
#include "autoctrl.h"


/*-----------------------------------------------
 * ���W��DC���[�^(r, theta, z)
-----------------------------------------------*/
void CoordinateSetPosXYZ(void);
void CoordinateSetPosRTZ(void);
void CoordinateSetDuty(float duty_r, float duty_theta, float duty_z);
void CoordinateEnable(void);
void CoordinateDisable(void);

//���W��DC���[�^�^�C�}�n���h��
#define COORDINATE_TIM_HANDLER		htim1

//PWM���g��
#define COORDINATE_PWM_FREQ			10000

//�^�C�}���g��
#define COORDINATE_TIM_FREQ			84000000

//Duty��̃��~�b�g
#define COORDINATE_DUTY_LIMIT		0.55f

//���[�^PWM�`�����l��
#define PWM_R_TIM_CH				TIM_CHANNEL_3
#define PWM_THETA_TIM_CH			TIM_CHANNEL_1
#define PWM_Z_TIM_CH				TIM_CHANNEL_2

//DC���[�^��]����GPIO
//R��
#define MOTOR_R_1_PORT				GPIOC
#define MOTOR_R_1_PIN				GPIO_PIN_5
#define MOTOR_R_2_PORT				GPIOB
#define MOTOR_R_2_PIN				GPIO_PIN_0

//Theta��
#define MOTOR_THETA_1_PORT			GPIOB
#define MOTOR_THETA_1_PIN			GPIO_PIN_10
#define MOTOR_THETA_2_PORT			GPIOB
#define MOTOR_THETA_2_PIN			GPIO_PIN_12

//Z��
#define MOTOR_Z_1_PORT				GPIOB
#define MOTOR_Z_1_PIN				GPIO_PIN_1
#define MOTOR_Z_2_PORT				GPIOB
#define MOTOR_Z_2_PIN				GPIO_PIN_2

//���[�^�u���[�L
#define MOTOR_BRAKE					1000000

//1��̊��荞�݂Ői�ދ����im�j
#define MOTOR_speed 0.0005f


#endif /* MOTOR_H_ */
