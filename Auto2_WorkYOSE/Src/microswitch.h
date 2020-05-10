/*
 * microswitch.h
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#ifndef MICROSWITCH_H_
#define MICROSWITCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f3xx_hal.h"
//#include "struct.h"
//#include "xprintf.h"

/*-----------------------------------------------
 * �}�C�N���X�C�b�`
 ----------------------------------------------*/
//�}�C�N���X�C�b�`�̘_��
//#define MICROSW_POSITIVE_LOGIC
#define MICROSW_NEGATIVE_LOGIC

//ON/OFF/������/�Z����
enum {
	MICROSW_OFF = 0,
	MICROSW_ON
};

//�}�C�N���X�C�b�`�̌�
#define NUM_OF_MICROSW			2

//�}�C�N���X�C�b�`���̓s��
//�v�b�V���[��MAX���E��
#define MICSW_X_MAX_PORT		GPIOA		//1
#define MICSW_X_MAX_PIN 		GPIO_PIN_3

#define MICSW_Y_MAX_PORT		GPIOA		//2
#define MICSW_Y_MAX_PIN		GPIO_PIN_4

//�}�C�N���X�C�b�`
enum {
	MICSW_X_MAX = 0,
	MICSW_Y_MAX
};


//�v���g�^�C�v�錾
uint8_t MicroSwitchIsOn(uint8_t);
void MicroSwitchWaitOff(uint8_t);


#ifdef __cplusplus
}
#endif


#endif /* MICROSWITCH_H_ */
