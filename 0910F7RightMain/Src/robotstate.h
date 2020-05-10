/*
 * robotstate.h
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#ifndef ROBOTSTATE_H_
#define ROBOTSTATE_H_


#include <math.h>
#include "stm32f7xx_hal.h"
//#include "struct.h"

//制御周期
#define CTRL_CYCLE		0.005f

//円筒座標系
typedef struct {
	float r;
	float theta;
	float z;
} struct_cyl;
extern struct_cyl poscyl;
extern struct_cyl refcyl;
extern float BOX_posrec;
extern float BOX_refrec;
//直行座標系
typedef struct {
	float x;
	float y;
	float z;
} struct_rec;
extern struct_rec posrec;
extern struct_rec refrec;

//プロトタイプ宣言
void ResetPos(void);


#endif /* ROBOTSTATE_H_ */
