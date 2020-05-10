/*
 * motor.c
 *
 *  Created on: 2019/08/17
 *      Author: tomok
 */



#include "motor.h"

/*
static void CoordinateSetDirection(float,float,float);

void CoordinateSetPosXYZ(){
	struct_cyl cyl;
	struct_rec rec;
	rec = refrec;
	Rec2Cyl(&rec,&cyl);
	refcyl = cyl;

	CoordinateSetPosRTZ();
}

void CoordinateSetPosRTZ(){
	float duty_r,duty_theta,duty_z;
	static float prev_z = 0;

	duty_r	=(poscyl.r	-refcyl.r)	*(-17.5f);
	duty_theta = (poscyl.theta - refcyl.theta)*(-7.5f);
	duty_z = (poscyl.z - refcyl.z)*(-90.0f);

	prev_z = poscyl.z;

	CoordinateSetDuty(duty_r,duty_theta,duty_z);
}


void CoordinateSetDuty(float duty_r,float duty_theta,float duty_z){
	uint16_t pwm_r = 0, pwm_theta = 0,pwm_z = 0;

	if(duty_r  !=MOTOR_BRAKE){
		duty_r = fmax(fminf(duty_r,1),-1);
	}
	if(duty_theta  !=MOTOR_BRAKE){
			duty_theta = fmax(fminf(duty_theta,1),-1);
	}
	if(duty_z  !=MOTOR_BRAKE){
			duty_z = fmax(fminf(duty_z,1),-1);
	}

	CoordinateSetDirection(duty_r,duty_theta,duty_z);

	if(duty_r != MOTOR_BRAKE){
		duty_r = fabsf(duty_r)*COORDINATE_DUTY_LIMIT;
		pwm_r = duty_r * (float)(COORDINATE_TIM_FREQ / COORDINATE_PWM_FREQ);
	}
	if(duty_theta != MOTOR_BRAKE){
			duty_theta = fabsf(duty_theta)*COORDINATE_DUTY_LIMIT;
			pwm_theta = duty_theta * (float)(COORDINATE_TIM_FREQ / COORDINATE_PWM_FREQ);
	}
	if(duty_z != MOTOR_BRAKE){
			duty_z = fabsf(duty_z)*COORDINATE_DUTY_LIMIT;
			pwm_z = duty_z * (float)(COORDINATE_TIM_FREQ / COORDINATE_PWM_FREQ);
	}
	__HAL_TIM_SetCompare(&COORDINATE_TIM_HANDLER, PWM_R_TIM_CH, 	pwm_r);
	__HAL_TIM_SetCompare(&COORDINATE_TIM_HANDLER, PWM_THETA_TIM_CH, pwm_theta);
	__HAL_TIM_SetCompare(&COORDINATE_TIM_HANDLER, PWM_Z_TIM_CH, 	pwm_z);
}

static void CoordinateSetDirection(float duty_r, float duty_theta, float duty_z) {
	if (duty_r >= 0) {
		HAL_GPIO_WritePin(MOTOR_R_1_PORT, MOTOR_R_1_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_R_2_PORT, MOTOR_R_2_PIN, GPIO_PIN_SET);
	} else if (duty_r < 0){
		HAL_GPIO_WritePin(MOTOR_R_1_PORT, MOTOR_R_1_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_R_2_PORT, MOTOR_R_2_PIN, GPIO_PIN_RESET);
	} else if (duty_r == MOTOR_BRAKE) {
		HAL_GPIO_WritePin(MOTOR_R_1_PORT, MOTOR_R_1_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_R_2_PORT, MOTOR_R_2_PIN, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(MOTOR_R_1_PORT, MOTOR_R_1_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_R_2_PORT, MOTOR_R_2_PIN, GPIO_PIN_RESET);
	}

	if (duty_theta >= 0) {
		HAL_GPIO_WritePin(MOTOR_THETA_1_PORT, MOTOR_THETA_1_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_THETA_2_PORT, MOTOR_THETA_2_PIN, GPIO_PIN_RESET);
	} else if (duty_theta < 0){
		HAL_GPIO_WritePin(MOTOR_THETA_1_PORT, MOTOR_THETA_1_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_THETA_2_PORT, MOTOR_THETA_2_PIN, GPIO_PIN_SET);
	} else if (duty_theta == MOTOR_BRAKE) {
		HAL_GPIO_WritePin(MOTOR_THETA_1_PORT, MOTOR_THETA_1_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_THETA_2_PORT, MOTOR_THETA_2_PIN, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(MOTOR_THETA_1_PORT, MOTOR_THETA_1_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_THETA_2_PORT, MOTOR_THETA_2_PIN, GPIO_PIN_RESET);
	}

	if (duty_z >= 0) {
		HAL_GPIO_WritePin(MOTOR_Z_1_PORT, MOTOR_Z_1_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_Z_2_PORT, MOTOR_Z_2_PIN, GPIO_PIN_SET);
	} else if (duty_z < 0){
		HAL_GPIO_WritePin(MOTOR_Z_1_PORT, MOTOR_Z_1_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_Z_2_PORT, MOTOR_Z_2_PIN, GPIO_PIN_RESET);
	} else if (duty_z == MOTOR_BRAKE) {
		HAL_GPIO_WritePin(MOTOR_Z_1_PORT, MOTOR_Z_1_PIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MOTOR_Z_2_PORT, MOTOR_Z_2_PIN, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(MOTOR_Z_1_PORT, MOTOR_Z_1_PIN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MOTOR_Z_2_PORT, MOTOR_Z_2_PIN, GPIO_PIN_RESET);
	}
}

void CoordinateEnable(void) {
	CoordinateSetDuty(0, 0, 0);
	HAL_TIM_PWM_Start(&COORDINATE_TIM_HANDLER, PWM_R_TIM_CH);
	HAL_TIM_PWM_Start(&COORDINATE_TIM_HANDLER, PWM_THETA_TIM_CH);
	HAL_TIM_PWM_Start(&COORDINATE_TIM_HANDLER, PWM_Z_TIM_CH);
}

void CoordinateDisable(void) {
	CoordinateSetDuty(0, 0, 0);
	HAL_TIM_PWM_Stop(&COORDINATE_TIM_HANDLER, PWM_R_TIM_CH);
	HAL_TIM_PWM_Stop(&COORDINATE_TIM_HANDLER, PWM_THETA_TIM_CH);
	HAL_TIM_PWM_Stop(&COORDINATE_TIM_HANDLER, PWM_Z_TIM_CH);
}

*/
