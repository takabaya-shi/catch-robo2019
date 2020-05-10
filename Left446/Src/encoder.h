/*
 * encoder.h
 *
 *  Created on: 2019/09/07
 *      Author: tomok
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "stm32f4xx_hal.h"

#define ENC_1_TIM_HANDLER	htim2
#define ENC_1_TIM	TIM2

extern TIM_HandleTypeDef htim2;

//�E�~����R���̌��ݒn�𓾂邽�߂̃p�����[�^
#define ENC_R_RESOLUTION		56
#define MOTOR_R_GEARHEAD		19
#define	R_PINION_DIAMETER		0.028f
#define M_PI 3.141592

//�E�~���̃Ǝ��̌��ݒn�𓾂邽�߂̃p�����[�^
#define THITA_DEGREE			68		//�G���R�[�_���������Ƃ��ɃƎ������p�x
#define ENC_THITA_RESOLUTION	2400	//�G���R�[�_�̕���\600�~4

//�d�����̌��ݒn�𓾂邽�߂̃p�����[�^
#define ENC_SELECT_RESOLUTION	2400
#define PINION_DIAMETER			0.03f

//������PID����̃p�����[�^
#define PID_P	0.5f
#define MD_DELTA_T 0.02

//�v���g�^�C�v�錾
void EncGetData(int16_t *);
void EncEnable(void);
void EncDisable(void);
float GetPos(void);
void PIDOut(float current_pos,float target_pos);


#endif /* ENCODER_H_ */
