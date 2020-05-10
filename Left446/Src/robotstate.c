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

//���_���͂̂Œ��ӁI
//�@== MICROSW_ON �Ŏ��ۂ�OFF
//�@== MICROSW_OFF �Ŏ��ۂ�ON
void ResetPush(float PUSH_MD3_DUTY) {
	//�v�b�V���[�̓���
	//float PUSH_MD3_DUTY = 0.5f;
	//�E���̃X�C�b�`��ON�̎��́A���̃X�C�b�`��ON�ɂȂ�܂ō��ɓ�����
	//�����̃X�C�b�`��ON�̎��́A�E�̃X�C�b�`��ON�ɂȂ�܂ŉE�ɓ�����
	//����DUTY���E����
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
