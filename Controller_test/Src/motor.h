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
 * 座標軸DCモータ(r, theta, z)
-----------------------------------------------*/
void CoordinateSetPosXYZ(void);
void CoordinateSetPosRTZ(void);
void CoordinateSetDuty(float duty_r, float duty_theta, float duty_z);
void CoordinateEnable(void);
void CoordinateDisable(void);

//座標軸DCモータタイマハンドラ
#define COORDINATE_TIM_HANDLER		htim1

//PWM周波数
#define COORDINATE_PWM_FREQ			10000

//タイマ周波数
#define COORDINATE_TIM_FREQ			84000000

//Duty比のリミット
#define COORDINATE_DUTY_LIMIT		0.55f

//モータPWMチャンネル
#define PWM_R_TIM_CH				TIM_CHANNEL_3
#define PWM_THETA_TIM_CH			TIM_CHANNEL_1
#define PWM_Z_TIM_CH				TIM_CHANNEL_2

//DCモータ回転方向GPIO
//R軸
#define MOTOR_R_1_PORT				GPIOC
#define MOTOR_R_1_PIN				GPIO_PIN_5
#define MOTOR_R_2_PORT				GPIOB
#define MOTOR_R_2_PIN				GPIO_PIN_0

//Theta軸
#define MOTOR_THETA_1_PORT			GPIOB
#define MOTOR_THETA_1_PIN			GPIO_PIN_10
#define MOTOR_THETA_2_PORT			GPIOB
#define MOTOR_THETA_2_PIN			GPIO_PIN_12

//Z軸
#define MOTOR_Z_1_PORT				GPIOB
#define MOTOR_Z_1_PIN				GPIO_PIN_1
#define MOTOR_Z_2_PORT				GPIOB
#define MOTOR_Z_2_PIN				GPIO_PIN_2

//モータブレーキ
#define MOTOR_BRAKE					1000000

//1回の割り込みで進む距離（m）
#define MOTOR_speed 0.0005f


#endif /* MOTOR_H_ */
