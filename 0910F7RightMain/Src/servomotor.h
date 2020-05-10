/*
 * servomotor.h
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include "stm32f7xx_hal.h"
#include "math.h"

long map(long x,long in_min,long in_max,long out_min,long out_max);
void ServoSetAngle(float angle,int servo_id);
void ServoDisable(void);
void ServoEnable(void);
void ServoGradAngle(int target_angle,int prev_angle,int speed,int delay,int servo_id);
//サーボの可動範囲(0.5ms ~ 2.0ms)

//BOX取りの一番右
#define SERVO1_LOW		200
#define SERVO1_HIGH		1400
#define SERVO1_MAX_ANGLE	90
#define SERVO1_MIN_ANGLE	-90

//BOX取りの真ん中
#define SERVO2_LOW		330
#define SERVO2_HIGH		1600
#define SERVO2_MAX_ANGLE	90
#define SERVO2_MIN_ANGLE	-90

//BOX取りの一番左
#define SERVO3_LOW		200
#define SERVO3_HIGH		1400

#define SERVO3_MAX_ANGLE	90
#define SERVO3_MIN_ANGLE	-90

//一個取り
#define SERVO4_LOW		200
#define SERVO4_HIGH		1400
#define SERVO4_MAX_ANGLE	90
#define SERVO4_MIN_ANGLE	-90



#define SERVO1_ID 10		//BOX取りの一番右
#define SERVO2_ID 11		//BOX取りの真ん中
#define SERVO3_ID 12		//BOX取りの一番左
#define SERVO4_ID 13		//一個取り

//サーボのタイマーハンドラ
#define SERVO1_TIM_HANDLER	htim10
#define SERVO2_TIM_HANDLER	htim9
#define SERVO3_TIM_HANDLER	htim11

//サーボのチャンネル
#define SERVO1_TIM_CH	TIM_CHANNEL_1
#define SERVO2_TIM_CH	TIM_CHANNEL_1
#define SERVO3_TIM_CH	TIM_CHANNEL_1
#define SERVO4_TIM_CH	TIM_CHANNEL_1


//サーボの初期位置
#define SERVO1_ZERO_ANGLE   -90
#define SERVO2_ZERO_ANGLE 	-90
#define SERVO3_ZERO_ANGLE 	-90
#define SERVO4_ZERO_ANGLE 	-90

#define SERVO1_BOX_ANGLE   90
#define SERVO2_BOX_ANGLE 	80
#define SERVO3_BOX_ANGLE 	80
#define SERVO4_BOX_ANGLE 	80

#endif /* SERVOMOTOR_H_ */
