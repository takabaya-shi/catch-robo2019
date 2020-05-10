/*
 * servomotor.h
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include "stm32f3xx_hal.h"
#include "math.h"

long map(long x,long in_min,long in_max,long out_min,long out_max);
void ServoSetAngle(int angle,int servo_id);
void ServoDisable(void);
void ServoEnable(void);
void ServoGradAngle(int target_angle,int prev_angle,int speed,int delay,int servo_id);
//サーボの可動範囲(0.5ms ~ 2.0ms)

//BOX取りの一番右
#define SERVO1_LOW		600
#define SERVO1_HIGH		1200
#define SERVO1_MAX_ANGLE	90
#define SERVO1_MIN_ANGLE	-90

#define SERVO1_ID 10		//BOX取りの一番右

//サーボのタイマーハンドラ
#define SERVO1_TIM_HANDLER	htim16
//サーボのチャンネル
#define SERVO1_TIM_CH	TIM_CHANNEL_1


//サーボの初期位置
#define SERVO1_ZERO_ANGLE 	-90


#endif /* SERVOMOTOR_H_ */
