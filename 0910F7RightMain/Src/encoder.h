/*
 * encoder.h
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <math.h>
#include "stm32f7xx_hal.h"
//#include "struct.h"
#include "robotstate.h"
#include "autoctrl.h"



//R��
#define ENC_R_TIM_HANDLER		htim2	//1
#define ENC_R_TIMx				TIM2
#define ENC_R_RESOLUTION		56
#define MOTOR_R_GEARHEAD		19
#define	R_PINION_DIAMETER		0.028f

//�Ǝ�
#define ENC_THETA_TIM_HANDLER	htim3	//2
#define ENC_THETA_TIMx			TIM3
#define ENC_THETA_RESOLUTION	56
#define MOTOR_THETA_GEARHEAD	19
#define THETA_GEARRATIO			(float)(85 / 28)

//�E�~���̃Ǝ��̌��ݒn�𓾂邽�߂̃p�����[�^
#define THITA_DEGREE			68.0f		//�G���R�[�_���������Ƃ��ɃƎ������p�x
#define ENC_THITA_RESOLUTION	1024.0f	//�G���R�[�_�̕���\600�~4

//Z��
#define ENC_Z_TIM_HANDLER		htim4	//3
#define ENC_Z_TIMx				TIM4
#define ENC_Z_RESOLUTION		400
#define MOTOR_Z_GEARHEAD		14
#define	Z_PINION_DIAMETER		0.030f

//�v���g�^�C�v�錾
void GetPosCyl(void);
void EncGetCountDiff(int16_t *, int16_t *, int16_t *);
void EncEnable(void);
void EncDisable(void);


#endif /* ENCODER_H_ */
