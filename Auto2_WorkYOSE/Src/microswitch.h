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
 * マイクロスイッチ
 ----------------------------------------------*/
//マイクロスイッチの論理
//#define MICROSW_POSITIVE_LOGIC
#define MICROSW_NEGATIVE_LOGIC

//ON/OFF/長押し/短押し
enum {
	MICROSW_OFF = 0,
	MICROSW_ON
};

//マイクロスイッチの個数
#define NUM_OF_MICROSW			2

//マイクロスイッチ入力ピン
//プッシャーはMAXが右側
#define MICSW_X_MAX_PORT		GPIOA		//1
#define MICSW_X_MAX_PIN 		GPIO_PIN_3

#define MICSW_Y_MAX_PORT		GPIOA		//2
#define MICSW_Y_MAX_PIN		GPIO_PIN_4

//マイクロスイッチ
enum {
	MICSW_X_MAX = 0,
	MICSW_Y_MAX
};


//プロトタイプ宣言
uint8_t MicroSwitchIsOn(uint8_t);
void MicroSwitchWaitOff(uint8_t);


#ifdef __cplusplus
}
#endif


#endif /* MICROSWITCH_H_ */
