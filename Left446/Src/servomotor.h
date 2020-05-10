/*
 * servomotor.h
 *
 *  Created on: 2019/09/07
 *      Author: tomok
 */

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include "stm32f4xx_hal.h"
#include "math.h"

long map(long x,long in_min,long in_max,long out_min,long out_max);
void ServoSetAngle(int angle,int servo_id);
void ServoDisable(void);
void ServoEnable(void);
void ServoGradAngle(int target_angle,int prev_angle,int speed,int delay,int servo_id);
//サーボの可動範囲(0.5ms ~ 2.0ms)

//自動の先のサーボ

#define SERVO1_LOW		600
#define SERVO1_HIGH		1200
#define SERVO1_MAX_ANGLE	90
#define SERVO1_MIN_ANGLE	-90

//自動の根本のサーボ
#define SERVO2_LOW		700
#define SERVO2_HIGH		1200
#define SERVO2_MAX_ANGLE	90
#define SERVO2_MIN_ANGLE	-90

//
#define SERVO3_LOW		600
#define SERVO3_HIGH		1200
#define SERVO3_MAX_ANGLE	90
#define SERVO3_MIN_ANGLE	-90


#define SERVO1_ID 10		//ワークを送り出すサーボ
#define SERVO2_ID 11		//ボックスはめのサーボ
#define SERVO3_ID 12		//予備(廃止されたサーボ)


//サーボのタイマーハンドラ
#define SERVO2_TIM_HANDLER	htim14		//1
#define SERVO1_TIM_HANDLER	htim13		//2
#define SERVO3_TIM_HANDLER	htim11		//3
//サーボのチャンネル
#define SERVO2_TIM_CH	TIM_CHANNEL_1	//1
#define SERVO1_TIM_CH	TIM_CHANNEL_1	//2
#define SERVO3_TIM_CH	TIM_CHANNEL_1	//3


//サーボの初期位置
#define SERVO1_ZERO_ANGLE 	-90
#define SERVO2_ZERO_ANGLE 	-90
#define SERVO3_ZERO_ANGLE 	0

#endif /* SERVOMOTOR_H_ */
