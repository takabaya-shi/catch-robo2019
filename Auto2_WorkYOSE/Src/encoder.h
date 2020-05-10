/*
 * encoder.h
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "stm32f3xx_hal.h"
#include "robotstate.h"

#define ENC_X_TIM_HANDLER	htim1
#define ENC_X_TIM	TIM1
#define ENC_Y_TIM_HANDLER	htim2
#define ENC_Y_TIM	TIM2

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

//BOX���̌��ݒn�𓾂邽�߂̃p�����[�^
#define ENC_BOX_RESOLUTION		56
#define MOTOR_R_GEARHEAD		19
#define	R_PINION_DIAMETER		0.028f
#define M_PI 3.141592

//�����X���̌��ݒn�𓾂邽�߂̃p�����[�^
#define THITA_DEGREE			68		//�G���R�[�_���������Ƃ��ɃƎ������p�x
#define ENC_X_RESOLUTION	2400	//�G���R�[�_�̕���\600�~4

//����Y���̌��ݒn�𓾂邽�߂̃p�����[�^
#define ENC_Y_RESOLUTION	2400
#define PINION_DIAMETER			0.03f

//������PID����̃p�����[�^
#define PID_P	0.5f
#define MD_DELTA_T 0.02

//�v���g�^�C�v�錾
void EncGetData(int16_t *,int16_t *);
void EncEnable(void);
void EncDisable(void);
float GetPos(void);
void PIDOut(float current_pos,float target_pos);


#endif /* ENCODER_H_ */
