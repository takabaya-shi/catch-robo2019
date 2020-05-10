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
 * マイクロスイッチ
 ----------------------------------------------*/
//マイクロスイッチの論理
#define MICROSW_POSITIVE_LOGIC
//#define MICROSW_NEGATIVE_LOGIC

//ON/OFF/長押し/短押し
enum {
	MICROSW_OFF = 0,
	MICROSW_ON
};

//マイクロスイッチの個数
#define NUM_OF_MICROSW			6

//マイクロスイッチ入力ピン
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

//マイクロスイッチ
enum {
	MICSW_R_MAX = 0,
	MICSW_R_MIN,
	MICSW_THETA_MAX,
	MICSW_THETA_MIN,
	MICSW_Z_MAX,
	MICSW_Z_MIN
};


//プロトタイプ宣言
uint8_t MicroSwitchIsOn(uint8_t);
void MicroSwitchWaitOff(uint8_t);


#ifdef __cplusplus
}
#endif


#endif /* MICROSWITCH_H_ */
