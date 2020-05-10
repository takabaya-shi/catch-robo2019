/*
 * robotstate.h
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#ifndef ROBOTSTATE_H_
#define ROBOTSTATE_H_

#include <math.h>
#include "stm32f3xx_hal.h"
//#include "struct.h"

//�������
#define CTRL_CYCLE		0.005f


//���s���W�n
typedef struct {
	float x;
	float y;
} struct_rec;
extern struct_rec posrec;
extern struct_rec refrec;

//�v���g�^�C�v�錾
void ResetYOSE(void);


#endif /* ROBOTSTATE_H_ */
