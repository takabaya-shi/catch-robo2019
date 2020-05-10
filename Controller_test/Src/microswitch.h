/*
 * microswitch.h
 *
 *  Created on: 2019/09/02
 *      Author: tomok
 */

#ifndef MICROSWITCH_H_
#define MICROSWITCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "struct.h"
//#include "xprintf.h"

/*-----------------------------------------------
 * �}�C�N���X�C�b�`
 ----------------------------------------------*/
//�}�C�N���X�C�b�`�̘_��
#define MICROSW_POSITIVE_LOGIC
//#define MICROSW_NEGATIVE_LOGIC

//ON/OFF/������/�Z����
enum {
	MICROSW_OFF = 0,
	MICROSW_ON
};

//�}�C�N���X�C�b�`�̌�
#define NUM_OF_MICROSW			6

//�}�C�N���X�C�b�`���̓s��
#define MICSW_R_MAX_PORT		GPIOA
#define MICSW_R_MAX_PIN 		GPIO_PIN_8

#define MICSW_R_MIN_PORT		GPIOC
#define MICSW_R_MIN_PIN			GPIO_PIN_9

#define MICSW_THETA_MAX_PORT	GPIOC
#define MICSW_THETA_MAX_PIN		GPIO_PIN_8

#define MICSW_THETA_MIN_PORT	GPIOC
#define MICSW_THETA_MIN_PIN		GPIO_PIN_7

#define MICSW_Z_MAX_PORT		GPIOC
#define MICSW_Z_MAX_PIN			GPIO_PIN_6

#define MICSW_Z_MIN_PORT		GPIOB
#define MICSW_Z_MIN_PIN			GPIO_PIN_15

//�}�C�N���X�C�b�`
enum {
	MICSW_R_MAX = 0,
	MICSW_R_MIN,
	MICSW_THETA_MAX,
	MICSW_THETA_MIN,
	MICSW_Z_MAX,
	MICSW_Z_MIN
};


//�v���g�^�C�v�錾
uint8_t MicroSwitchIsOn(uint8_t);
void MicroSwitchWaitOff(uint8_t);


#ifdef __cplusplus
}
#endif


#endif /* MICROSWITCH_H_ */
