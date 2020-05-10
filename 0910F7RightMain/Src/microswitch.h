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

#include "stm32f7xx_hal.h"
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
#define NUM_OF_MICROSW			9

//�}�C�N���X�C�b�`���̓s��
//�~��
#define MICSW_R_MAX_PORT		GPIOA		//1
#define MICSW_R_MAX_PIN 		GPIO_PIN_4

#define MICSW_THETA_MAX_PORT		GPIOC		//2
#define MICSW_THETA_MAX_PIN		GPIO_PIN_3

#define MICSW_Z_MAX_PORT	GPIOC		//3
#define MICSW_Z_MAX_PIN	GPIO_PIN_2

//BOX���
#define MICSW_BOX_MAX_PORT	GPIOC		//4
#define MICSW_BOX_MAX_PIN	GPIO_PIN_0

#define MICSW_BOX_MIN_PORT	GPIOD		//5
#define MICSW_BOX_MIN_PIN	GPIO_PIN_3

//Z���̒ǉ�
#define MICSW_Z_MIN_PORT	GPIOG		//6
#define MICSW_Z_MIN_PIN		GPIO_PIN_2

//����
#define MICSW_ONE_X_MIN_PORT	GPIOG		//7
#define MICSW_ONE_X_MIN_PIN	GPIO_PIN_3

#define MICSW_ONE_Y_MAX_PORT	GPIOE		//8
#define MICSW_ONE_Y_MAX_PIN	GPIO_PIN_2

#define MICSW_ONE_Y_MIN_PORT	GPIOE		//9
#define MICSW_ONE_Y_MIN_PIN	GPIO_PIN_4
//�}�C�N���X�C�b�`
enum {
	MICSW_R_MAX = 0,
	MICSW_THETA_MAX,
	MICSW_Z_MAX,
	MICSW_BOX_MAX,
	MICSW_BOX_MIN,
	MICSW_Z_MIN,
	MICSW_ONE_X_MIN,
	MICSW_ONE_Y_MAX,
	MICSW_ONE_Y_MIN
};


//�v���g�^�C�v�錾
uint8_t MicroSwitchIsOn(uint8_t);
void MicroSwitchWaitOff(uint8_t);


#ifdef __cplusplus
}
#endif


#endif /* MICROSWITCH_H_ */
