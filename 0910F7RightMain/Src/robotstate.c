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

//円筒座標系
struct_cyl poscyl;
struct_cyl refcyl;

//直交座標系
struct_rec posrec;
struct_rec refrec;

float BOX_posrec;
float BOX_refrec;

void ResetBOX(void){


	BOX_posrec = 0.0f;
	BOX_refrec = 0.0f;
}


void ResetPos(void) {
	//原点復帰
	while(MicroSwitchIsOn(MICSW_Z_MAX) == MICROSW_ON){
		CoordinateSetDuty(0.1f, MD_Z_ID);
		//正のDUTYで上に移動
	}
	CoordinateSetDuty(0.0f, MD_Z_ID);


	while(MicroSwitchIsOn(MICSW_R_MAX) == MICROSW_ON){
		CoordinateSetDuty(-0.1f, MD_R_ID);
		//正のDUTYでR正の方向（奥）
	}

	ENC_R_TIMx->CNT     = 1;

	CoordinateSetDuty(MOTOR_BRAKE,MD_R_ID);
	CoordinateSetDuty(MOTOR_BRAKE,MD_THITA_ID);
	CoordinateSetDuty(MOTOR_BRAKE,MD_Z_ID);

	//現在円筒座標
	poscyl.r     = 0.0f;
	poscyl.theta = M_PI;//(float)(-10.0f * M_PI) / 180.0f;
	poscyl.z     = 0;

	//目標円筒座標
	refcyl.r     = 0.0f;
	refcyl.theta = M_PI;;
	refcyl.z     = 0;

	//現在直交座標
	posrec.x = 0.0f;
	posrec.y = 0.0f;
	posrec.z = 0;

	//目標直交座標
	refrec.x = 0.0f;
	refrec.y = 0.0f;
	refrec.z = 0;
}

