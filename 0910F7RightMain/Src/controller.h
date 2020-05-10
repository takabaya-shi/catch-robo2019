/*
 * controller.h
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "stm32f7xx_hal.h"
//#include "struct.h"
//#include "xprintf.h"
#include <stdlib.h>
#include <math.h>

//SPI通信ハンドラ
#define CONTROLLER_SPI_HANDLER		hspi3

//CSポート、ピン
#define CONTROLLER_CS_PORT			GPIOD
#define CONTROLLER_CS_PIN			GPIO_PIN_7

//アナログスティック不感帯
#define ANALOG_STICK_DEADZONE		0.4f

//ボタンマスク用
enum {
	CONTROLLER_LEFT     = 0b1000000000000000,
	CONTROLLER_DOWN     = 0b0100000000000000,
	CONTROLLER_RIGHT    = 0b0010000000000000,
	CONTROLLER_UP       = 0b0001000000000000,
	CONTROLLER_SQUARE   = 0b0000000010000000,
	CONTROLLER_CROSS    = 0b0000000001000000,
	CONTROLLER_CIRCLE   = 0b0000000000100000,
	CONTROLLER_TRIANGLE = 0b0000000000010000,
	CONTROLLER_L1       = 0b0000000000000100,
	CONTROLLER_L2       = 0b0000000000000001,
	CONTROLLER_R1       = 0b0000000000001000,
	CONTROLLER_R2       = 0b0000000000000010,
	CONTROLLER_L3		= 0b0000001000000000,
	CONTROLLER_R3		= 0b0000010000000000,
	CONTROLLER_SELECT	= 0b0000000100000000,
	CONTROLLER_START	= 0b0000100000000000
};

//アナログスティック
typedef struct {
	int16_t x;
	int16_t y;
} analog_stick;

typedef struct {
	float x;
	float y;
} analog_stick_norm;

typedef struct {
	float r;
	float theta;
} analog_stick_polar;

//プロトタイプ宣言
void PSControllerGetData(uint16_t*, analog_stick_norm*, analog_stick_norm*, analog_stick_polar*, analog_stick_polar*);
int filter(uint16_t button, analog_stick_norm left_norm, analog_stick_norm  right_norm, analog_stick_polar left_polar, analog_stick_polar right_polar);



#endif /* CONTROLLER_H_ */
