/*
 * controller.h
 *
 *  Created on: 2019/08/02
 *      Author: tomok
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "stm32f4xx_hal.h"
#include <stdlib.h>
#include "struct.h"
#include "main.h"
#include <math.h>


#define CONTROLLER_SPI_HANDLER	hspi3
#define CONTROLLER1_CS_PORT	GPIOD
#define CONTROLLER1_CS_PIN	GPIO_PIN_2

#define CONTROLLER2_CS_PORT	GPIOC
#define CONTROLLER2_CS_PIN	GPIO_PIN_8

//#define CONTROLLER_CS_PORT	GPIOA
//#define CONTROLLER_CS_PIN	GPIO_PIN_15

//アナログスティック不感帯
#define ANALOG_STICK_DEADZONE		0.4f

enum {
	CONTOROLLER_LEFT 	= 	0b1000000000000000,
	CONTOROLLER_DOWN 	= 	0b0100000000000000,
	CONTOROLLER_RIGHT 	= 	0b0010000000000000,
	CONTOROLLER_UP		= 	0b0001000000000000,
	CONTOROLLER_SQUARE	= 	0b0000000010000000,
	CONTOROLLER_CROSS 	= 	0b0000000001000000,
	CONTOROLLER_CIRCLE	= 	0b0000000000100000,
	CONTOROLLER_TRIANGLE=	0b0000000000010000,
	CONTOROLLER_L1		=	0b0000000000000100,
	CONTOROLLER_L2		=	0b0000000000000001,
	CONTOROLLER_R1		=	0b0000000000001000,
	CONTOROLLER_R2		=	0b0000000000000010
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



void PSControllerGetData(uint16_t*, analog_stick_norm*, analog_stick_norm*, analog_stick_polar*, analog_stick_polar*);
int filter(uint16_t button, analog_stick_norm left_norm, analog_stick_norm  right_norm, analog_stick_polar left_polar, analog_stick_polar right_polar);

#endif /* CONTROLLER_H_ */
