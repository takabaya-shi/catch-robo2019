/*
 * autoctrl.h
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#ifndef AUTOCTRL_H_
#define AUTOCTRL_H_

#include <math.h>
#include "robotstate.h"
#include "stm32f7xx_hal.h"

void Cyl2Rec(struct_cyl *, struct_rec *);
void Rec2Cyl(struct_rec *, struct_cyl *);


#endif /* AUTOCTRL_H_ */
