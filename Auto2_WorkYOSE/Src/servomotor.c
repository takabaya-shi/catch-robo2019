/*
 * servomotor.c
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#include "servomotor.h"

extern TIM_HandleTypeDef htim16;

//引数ｘで与えられた角度に相当するPWMの値を返す（MAXは10000）
long map(long x,long in_min,long in_max,long out_min,long out_max){
	return (x-in_min)*(out_max-out_min)/(in_max-in_min)+out_min;
}

//引数で与えられた角度にサーボを動かす
void ServoSetAngle(int angle,int servo_id){
	long PWM;

	if(servo_id == SERVO1_ID){
		//角度範囲を制限
		angle  = fmaxf(fminf(angle, SERVO1_MAX_ANGLE), SERVO1_MIN_ANGLE);
		//対応するPWMの値を取得
		PWM = map(angle,SERVO1_MIN_ANGLE,SERVO1_MAX_ANGLE,SERVO1_LOW,SERVO1_HIGH);
		__HAL_TIM_SET_COMPARE(&SERVO1_TIM_HANDLER,SERVO1_TIM_CH,PWM);
	}
}

/*
 * タイマENABLE
 * @param
 * @return
 */
void ServoEnable(void) {

	HAL_TIM_PWM_Start(&SERVO1_TIM_HANDLER, SERVO1_TIM_CH);

	ServoSetAngle(SERVO1_ZERO_ANGLE,SERVO1_ID);
}

/*
 * タイマDISABLE
 * @param
 * @return
 */
void ServoDisable(void) {
	HAL_TIM_PWM_Stop(&SERVO1_TIM_HANDLER, SERVO1_TIM_CH);
}

//指定されたスピードで段階的にサーボを出力する
void ServoGradAngle(int target_angle,int prev_angle,int speed,int delay,int servo_id){
	int tmp;
	int SERVO1_angle = SERVO1_ZERO_ANGLE;
	if((target_angle - prev_angle) > 0){
		tmp = (target_angle - prev_angle) % speed;
		if(servo_id == SERVO1_ID){
			for(int i=0;i<(target_angle - prev_angle)/speed;i++){
				SERVO1_angle = fminf(fmaxf(prev_angle + (i + 1) * speed + tmp, SERVO1_MIN_ANGLE),SERVO1_MAX_ANGLE);
				ServoSetAngle(SERVO1_angle,SERVO1_ID);
				HAL_Delay(delay);
			}
		}
	}else if((target_angle - prev_angle) < 0){
		tmp = (prev_angle - target_angle) % speed;
		if(servo_id == SERVO1_ID){
			for(int i=0;i<(prev_angle - target_angle)/speed;i++){
				SERVO1_angle = fminf(fmaxf(prev_angle - ((i + 1) * speed + tmp), SERVO1_MIN_ANGLE),SERVO1_MAX_ANGLE);
				ServoSetAngle(SERVO1_angle,SERVO1_ID);
				HAL_Delay(delay);
			}
		}
	}
}



