/*
 * microswitch.h
 *
 *  Created on: 2019/09/07
 *      Author: tomok
 */

#ifndef MICROSWITCH_H_
#define MICROSWITCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"
//#include "struct.h"
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
#define NUM_OF_MICROSW			4

//�}�C�N���X�C�b�`���̓s��
//�v�b�V���[��MAX���E��
#define MICSW_PUSH_MAX_PORT		GPIOC		//1
#define MICSW_PUSH_MAX_PIN 		GPIO_PIN_5

#define MICSW_PUSH_MIN_PORT		GPIOB		//2
#define MICSW_PUSH_MIN_PIN		GPIO_PIN_0

//�d������MAX����O��
#define MICSW_SELECT_MAX_PORT	GPIOB		//3
#define MICSW_SELECT_MAX_PIN	GPIO_PIN_1

#define MICSW_SELECT_MIN_PORT	GPIOB		//4
#define MICSW_SELECT_MIN_PIN	GPIO_PIN_2

//�}�C�N���X�C�b�`
enum {
	MICSW_PUSH_MAX = 0,
	MICSW_PUSH_MIN,
	MICSW_SELECT_MAX,
	MICSW_SELECT_MIN
};


//�v���g�^�C�v�錾
uint8_t MicroSwitchIsOn(uint8_t);
void MicroSwitchWaitOff(uint8_t);


#ifdef __cplusplus
}
#endif


#endif /* MICROSWITCH_H_ */
