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
//�T�[�{�̉��͈�(0.5ms ~ 2.0ms)

//�����̐�̃T�[�{

#define SERVO1_LOW		600
#define SERVO1_HIGH		1200
#define SERVO1_MAX_ANGLE	90
#define SERVO1_MIN_ANGLE	-90

//�����̍��{�̃T�[�{
#define SERVO2_LOW		700
#define SERVO2_HIGH		1200
#define SERVO2_MAX_ANGLE	90
#define SERVO2_MIN_ANGLE	-90

//
#define SERVO3_LOW		600
#define SERVO3_HIGH		1200
#define SERVO3_MAX_ANGLE	90
#define SERVO3_MIN_ANGLE	-90


#define SERVO1_ID 10		//���[�N�𑗂�o���T�[�{
#define SERVO2_ID 11		//�{�b�N�X�͂߂̃T�[�{
#define SERVO3_ID 12		//�\��(�p�~���ꂽ�T�[�{)


//�T�[�{�̃^�C�}�[�n���h��
#define SERVO2_TIM_HANDLER	htim14		//1
#define SERVO1_TIM_HANDLER	htim13		//2
#define SERVO3_TIM_HANDLER	htim11		//3
//�T�[�{�̃`�����l��
#define SERVO2_TIM_CH	TIM_CHANNEL_1	//1
#define SERVO1_TIM_CH	TIM_CHANNEL_1	//2
#define SERVO3_TIM_CH	TIM_CHANNEL_1	//3


//�T�[�{�̏����ʒu
#define SERVO1_ZERO_ANGLE 	-90
#define SERVO2_ZERO_ANGLE 	-90
#define SERVO3_ZERO_ANGLE 	0

#endif /* SERVOMOTOR_H_ */
