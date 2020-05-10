/*
 * robotstate.c
 *
 *  Created on: 2019/09/07
 *      Author: tomok
 */

#include "robotstate.h"
#include "microswitch.h"
#include "motor.h"
#include "encoder.h"

//負論理はので注意！
//　== MICROSW_ON で実際はOFF
//　== MICROSW_OFF で実際はON
void ResetPush(float PUSH_MD3_DUTY) {
	//プッシャーの動作
	//float PUSH_MD3_DUTY = 0.5f;
	//右側のスイッチがONの時は、左のスイッチがONになるまで左に動かす
	//左側のスイッチがONの時は、右のスイッチがONになるまで右に動かす
	//正のDUTYが右向き
	if(MicroSwitchIsOn(MICSW_PUSH_MAX) == MICROSW_OFF){
		while(MicroSwitchIsOn(MICSW_PUSH_MIN) == MICROSW_ON){
			CoordinateSetDuty((-1.0f)*PUSH_MD3_DUTY, MD3_ID);
		}
	}else if(MicroSwitchIsOn(MICSW_PUSH_MIN) == MICROSW_OFF){
		while(MicroSwitchIsOn(MICSW_PUSH_MAX) == MICROSW_ON){
			CoordinateSetDuty(PUSH_MD3_DUTY, MD3_ID);
		}
	}
}
