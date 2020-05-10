/*
 * servomotor.h
 *
 *  Created on: 2019/08/29
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

//サーボの可動範囲(0.5ms ~ 2.0ms)
//ボックス取りのサーボ３個
#define SERVO_LOW 			340
#define SERVO_HIGH 			1200
#define SERVO1_MIN_ANGLE 	-90
#define SERVO1_MAX_ANGLE 	90

//自動の先のサーボ
#define AUTO_SERVO1_LOW		450
#define AUTO_SERVO1_HIGH		1250
#define AUTO_SERVO1_MAX_ANGLE	180
#define AUTO_SERVO1_MIN_ANGLE	-90

//自動の根本のサーボ
#define AUTO_SERVO2_LOW		250
#define AUTO_SERVO2_HIGH		870
#define AUTO_SERVO2_MAX_ANGLE	180
#define AUTO_SERVO2_MIN_ANGLE	-90


#define SERVO1_ID 1
#define SERVO2_ID 2
#define SERVO3_ID 3
#define SERVO4_ID 4
#define SERVO5_ID 5
#define SERVO6_ID 6
#define SERVO7_ID 7
#define SERVO8_ID 8
#define SERVO9_ID 9
#define SERVO10_ID 10
#define SERVO11_ID 11
#define SERVO12_ID 12

#define AUTO_SERVO1_ID 13
#define AUTO_SERVO2_ID 14




//サーボのタイマーハンドラ
/*
#define SERVO1_TIM_HANDLER	htim2
#define SERVO2_TIM_HANDLER	htim13
#define SERVO3_TIM_HANDLER	htim14
#define SERVO4_TIM_HANDLER	htim4
#define SERVO5_TIM_HANDLER	htim8
#define SERVO6_TIM_HANDLER	htim1
#define SERVO7_TIM_HANDLER	htim1
#define SERVO8_TIM_HANDLER	htim2
*/
#define SERVO9_TIM_HANDLER	htim3

/*#define SERVO10_TIM_HANDLER	htim3
#define SERVO11_TIM_HANDLER	htim1
#define SERVO12_TIM_HANDLER	htim9
*/

#define AUTO_SERVO1_TIM_HANDLER	htim2
#define AUTO_SERVO2_TIM_HANDLER	htim3
//サーボのチャンネル
/*
#define SERVO1_TIM_CH		TIM_CHANNEL_1
#define SERVO2_TIM_CH		TIM_CHANNEL_1
#define SERVO3_TIM_CH		TIM_CHANNEL_1
#define SERVO4_TIM_CH		TIM_CHANNEL_1
#define SERVO5_TIM_CH		TIM_CHANNEL_2
#define SERVO6_TIM_CH		TIM_CHANNEL_2
#define SERVO7_TIM_CH		TIM_CHANNEL_1
#define SERVO8_TIM_CH		TIM_CHANNEL_3
*/
#define SERVO9_TIM_CH		TIM_CHANNEL_1
/*
#define SERVO10_TIM_CH		TIM_CHANNEL_2
#define SERVO11_TIM_CH		TIM_CHANNEL_3
#define SERVO12_TIM_CH		TIM_CHANNEL_2
*/
#define AUTO_SERVO1_TIM_CH	TIM_CHANNEL_1
#define AUTO_SERVO2_TIM_CH	TIM_CHANNEL_1


//サーボの初期位置
#define SERVO1_ZERO_ANGLE 	0
#define AUTO_SERVO1_ZERO_ANGLE 	170
#define AUTO_SERVO2_ZERO_ANGLE 	165

#endif /* SERVOMOTOR_H_ */
