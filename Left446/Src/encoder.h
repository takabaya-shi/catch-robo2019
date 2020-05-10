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

//右円筒のR軸の現在地を得るためのパラメータ
#define ENC_R_RESOLUTION		56
#define MOTOR_R_GEARHEAD		19
#define	R_PINION_DIAMETER		0.028f
#define M_PI 3.141592

//右円筒のθ軸の現在地を得るためのパラメータ
#define THITA_DEGREE			68		//エンコーダが一周するときにθ軸が回る角度
#define ENC_THITA_RESOLUTION	2400	//エンコーダの分解能600×4

//仕分けの現在地を得るためのパラメータ
#define ENC_SELECT_RESOLUTION	2400
#define PINION_DIAMETER			0.03f

//自動のPID制御のパラメータ
#define PID_P	0.5f
#define MD_DELTA_T 0.02

//プロトタイプ宣言
void EncGetData(int16_t *);
void EncEnable(void);
void EncDisable(void);
float GetPos(void);
void PIDOut(float current_pos,float target_pos);


#endif /* ENCODER_H_ */
