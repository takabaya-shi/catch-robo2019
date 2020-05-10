/*
 * robotstate.c
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#include "robotstate.h"
#include "microswitch.h"
#include "motor.h"
#include "encoder.h"

//����̒������W�n
struct_rec posrec;
struct_rec refrec;

void ResetYOSE(void){

	posrec.x = 0.0f;
	posrec.y = 0.0f;

	refrec.x = 0.0f;
	refrec.y = 0.0f;
}
