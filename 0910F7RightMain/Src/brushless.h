/*
 * brushless.h
 *
 *  Created on: 2019/09/12
 *      Author: tomok
 */

#ifndef BRUSHLESS_H_
#define BRUSHLESS_H_

#define BRUSHLESS_PWM_TIM 	htim13
#define BRUSHLESS_PWM_TIM_CNANNEL 	TIM_CHANNEL_1

#define BRUSHLESS_MAX	650.0f
#define BRUSHLESS_MIN	500.0f

extern float BRUSHLESS_PWM;

void BrushLessEnable(void);

#endif /* BRUSHLESS_H_ */
