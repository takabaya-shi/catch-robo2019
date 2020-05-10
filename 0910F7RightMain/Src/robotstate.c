/*
 * robotstate.c
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#include "robotstate.h"
#include "microswitch.h"
#include "motor.h"
#include "encoder.h"

//�~�����W�n
struct_cyl poscyl;
struct_cyl refcyl;

//�������W�n
struct_rec posrec;
struct_rec refrec;

float BOX_posrec;
float BOX_refrec;

void ResetBOX(void){


	BOX_posrec = 0.0f;
	BOX_refrec = 0.0f;
}


void ResetPos(void) {
	//���_���A
	while(MicroSwitchIsOn(MICSW_Z_MAX) == MICROSW_ON){
		CoordinateSetDuty(0.1f, MD_Z_ID);
		//����DUTY�ŏ�Ɉړ�
	}
	CoordinateSetDuty(0.0f, MD_Z_ID);


	while(MicroSwitchIsOn(MICSW_R_MAX) == MICROSW_ON){
		CoordinateSetDuty(-0.1f, MD_R_ID);
		//����DUTY��R���̕����i���j
	}

	ENC_R_TIMx->CNT     = 1;

	CoordinateSetDuty(MOTOR_BRAKE,MD_R_ID);
	CoordinateSetDuty(MOTOR_BRAKE,MD_THITA_ID);
	CoordinateSetDuty(MOTOR_BRAKE,MD_Z_ID);

	//���݉~�����W
	poscyl.r     = 0.0f;
	poscyl.theta = M_PI;//(float)(-10.0f * M_PI) / 180.0f;
	poscyl.z     = 0;

	//�ڕW�~�����W
	refcyl.r     = 0.0f;
	refcyl.theta = M_PI;;
	refcyl.z     = 0;

	//���ݒ������W
	posrec.x = 0.0f;
	posrec.y = 0.0f;
	posrec.z = 0;

	//�ڕW�������W
	refrec.x = 0.0f;
	refrec.y = 0.0f;
	refrec.z = 0;
}

