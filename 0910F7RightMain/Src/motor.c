/*
 * motor.c
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#include "math.h"
#include "motor.h"
#include "stm32f7xx_hal.h"
#include "robotstate.h"
#include "autoctrl.h"
#include "microswitch.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;

float vero = 0.0f;
float current_diff_z = 0.0f;
float prev_diff_z = 0.0f;
float integral_z = 0.0f;

float current_diff_r = 0.0f;
float prev_diff_r = 0.0f;
float integral_r = 0.0f;

float current_diff_theta = 0.0f;
float prev_diff_theta = 0.0f;
float integral_theta = 0.0f;

/*
 * 指定された直行座標位置に動かす
 * @param
 * @return
 */
void CoordinateSetPosXYZ(uint16_t auto_flag) {
	//座標変換
	struct_cyl cyl;
	struct_rec rec;
	rec = refrec;
		Rec2Cyl(&rec, &cyl);
		refcyl = cyl;

		//θが暴れるのを防ぐ
		/*
		if(refcyl.theta >= 0 && refcyl.theta <= 100 && poscyl.theta == M_PI){
			refcyl.theta = poscyl.theta - 0.0175;
		}else */if(refcyl.theta >= 0 && refcyl.theta <= 100 && poscyl.theta < M_PI - 0.015f && poscyl.theta > M_PI + 0.015f){
			refcyl.theta = poscyl.theta;
		}

		//自動と手動でPゲインが明らかに違うので関数を変えている
		//auto_flag = 0　で手動
		if(auto_flag == 0){
			//出力
			CoordinateSetPosRTZ();
		}else{
			CoordinateSetPosPID();
		}
}

/*
 * 自動で目標座標位置に動かす
 * @param
 * @return
 */
void CoordinateSetPosPID(void) {
	float duty_r, duty_theta, duty_z;

	//各モータのDuty比を決定
	//θはDUTY負で右向き
	duty_r     = (poscyl.r     - refcyl.r)     * (-10.5f);
	duty_theta = (poscyl.theta - refcyl.theta) * (-2.5f) * poscyl.r;
	duty_z	   = (refcyl.z - poscyl.z) * -35.5f + (float)(0.5f * (current_diff_z - prev_diff_z)/0.04f);


	/*
	integral_z = fmaxf(fminf(integral_z + (current_diff_z + prev_diff_z) /2.0f * 0.04f, 200.0f),-200.0f);
	current_diff_z = refcyl.z - poscyl.z;
	duty_z	   = current_diff_z * -20.5f + (float)(0.5f * (current_diff_z - prev_diff_z)/0.04f) + integral_z * 0.0001f;
	prev_diff_z = current_diff_z;

	current_diff_r = poscyl.r     - refcyl.r;
	integral_r = fmaxf(fminf(integral_r + (current_diff_r + prev_diff_r) /2.0f * 0.04f, 0.2f),-0.2f);
	duty_r	   = current_diff_r * -30.5f  + integral_r * 0.6f;
	prev_diff_r = current_diff_r;

	integral_theta = fmaxf(fminf(integral_theta + (current_diff_theta + prev_diff_theta) /2.0f * 0.04f, 200.0f),-200.0f);
	current_diff_theta = poscyl.theta     - refcyl.theta;
	duty_theta	   = current_diff_theta * (-1.6f) * poscyl.r +  integral_theta * 0.00005f;
	prev_diff_theta = current_diff_theta;
	*/


	//低すぎるDUTYならストップ
	if(duty_r > -0.09f && duty_r < 0.09f){
		duty_r = 0.0f;
	}
	if(duty_theta > -0.09f && duty_theta < 0.09f){
		duty_theta = 0.0f;
	}
	if(duty_z > -0.09f && duty_z < 0.09f){
		duty_z = 0.0f;
	}

	duty_theta     = fmaxf(fminf(duty_theta,     0.4f), -0.4f);

	//モータに出力
	//θの行きすぎ防止
	if(duty_theta > 0){
		if(MicroSwitchIsOn(MICSW_THETA_MAX) == MICROSW_OFF){
			CoordinateSetDuty(MOTOR_BRAKE,MD_THITA_ID);
		}else{
			CoordinateSetDuty(duty_theta,MD_THITA_ID);
		}
	}else{
		CoordinateSetDuty(duty_theta,MD_THITA_ID);
		CoordinateSetDuty(duty_r,MD_R_ID);
		CoordinateSetDuty(duty_z,MD_Z_ID);
	}
}


/*
 * 手動で目標円筒座標位置に動かす
 * @param
 * @return
 */
void CoordinateSetPosRTZ(void) {
	float duty_r, duty_theta, duty_z;
	//static float prev_z = 0;

	//各モータのDuty比を決定
	duty_r     = (poscyl.r     - refcyl.r)     * (-90.5f);
	duty_theta = (poscyl.theta - refcyl.theta) * (-60.5f) * poscyl.r;
	duty_z	   = (refcyl.z - poscyl.z) * 65.0f;

	duty_theta     = fmaxf(fminf(duty_theta,     0.6f), -0.6f);

	if(duty_r > -0.09f && duty_r < 0.09f){
		duty_r = 0.0f;
	}
	if(duty_theta > -0.09f && duty_theta < 0.09f){
		duty_theta = 0.0f;
	}
	if(duty_z > -0.09f && duty_z < 0.09f){
		duty_z = 0.0f;
	}

	//θの行きすぎ防止
	if(duty_theta > 0){
		if(MicroSwitchIsOn(MICSW_THETA_MAX) == MICROSW_OFF){
			CoordinateSetDuty(MOTOR_BRAKE,MD_THITA_ID);
		}else{
			CoordinateSetDuty(duty_theta,MD_THITA_ID);
		}
	}else{

		CoordinateSetDuty(duty_theta,MD_THITA_ID);
		CoordinateSetDuty(duty_r,MD_R_ID);
		CoordinateSetDuty(duty_z,MD_Z_ID);
	}


}

/*
 * BOX座標位置に動かす
 * @param
 * @return
 */
void CoordinateSetPosBOX(void) {
	float duty;

	//各モータのDuty比を決定
	duty = (BOX_posrec - BOX_refrec) * (-30.0f);

	if(duty > -0.09f && duty < 0.09f){
		duty = 0.0f;
	}
	//モータに出力
	CoordinateSetDuty(duty,MD_BOX1_ID);
	CoordinateSetDuty(duty,MD_BOX2_ID);
}



/*-----------------------------------------------
 * 座標軸モータ
-----------------------------------------------*/
//static void CoordinateSetDirection(float duty,int MD_ID);
void CoordinateSetDirection(float duty,int MD_ID) {
	if(MD_ID == MD_R_ID){
		if (duty < 0) {
			HAL_GPIO_WritePin(MD_R_1_PORT, MD_R_1_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MD_R_2_PORT, MD_R_2_PIN, GPIO_PIN_SET);
		} else if (duty > 0){
			HAL_GPIO_WritePin(MD_R_1_PORT, MD_R_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_R_2_PORT, MD_R_2_PIN, GPIO_PIN_RESET);
		}else {
			HAL_GPIO_WritePin(MD_R_1_PORT, MD_R_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_R_2_PORT, MD_R_2_PIN, GPIO_PIN_SET);
		}

	}else if(MD_ID == MD_THITA_ID){
		if (duty > 0) {
			HAL_GPIO_WritePin(MD_THITA_1_PORT, MD_THITA_1_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MD_THITA_2_PORT, MD_THITA_2_PIN, GPIO_PIN_SET);
		} else if (duty < 0){
			HAL_GPIO_WritePin(MD_THITA_1_PORT, MD_THITA_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_THITA_2_PORT, MD_THITA_2_PIN, GPIO_PIN_RESET);
		}else {
			HAL_GPIO_WritePin(MD_THITA_1_PORT, MD_THITA_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_THITA_2_PORT, MD_THITA_2_PIN, GPIO_PIN_SET);
		}

	}else if(MD_ID == MD_Z_ID){
		if (duty > 0) {
			HAL_GPIO_WritePin(MD_Z_1_PORT, MD_Z_1_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MD_Z_2_PORT, MD_Z_2_PIN, GPIO_PIN_SET);
		} else if (duty < 0){
			HAL_GPIO_WritePin(MD_Z_1_PORT, MD_Z_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_Z_2_PORT, MD_Z_2_PIN, GPIO_PIN_RESET);
		}else {
			HAL_GPIO_WritePin(MD_Z_1_PORT, MD_Z_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_Z_2_PORT, MD_Z_2_PIN, GPIO_PIN_SET);
		}

	}else 	if(MD_ID == MD_BOX1_ID){
		if (duty > 0) {
			HAL_GPIO_WritePin(MD_BOX1_1_PORT, MD_BOX1_1_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MD_BOX1_2_PORT, MD_BOX1_2_PIN, GPIO_PIN_SET);
		} else if (duty < 0){
			HAL_GPIO_WritePin(MD_BOX1_1_PORT, MD_BOX1_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_BOX1_2_PORT, MD_BOX1_2_PIN, GPIO_PIN_RESET);
		}else {
			HAL_GPIO_WritePin(MD_BOX1_1_PORT, MD_BOX1_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_BOX1_2_PORT, MD_BOX1_2_PIN, GPIO_PIN_SET);
		}

	}else if(MD_ID == MD_BOX2_ID){
		if (duty > 0) {
			HAL_GPIO_WritePin(MD_BOX2_1_PORT, MD_BOX2_1_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MD_BOX2_2_PORT, MD_BOX2_2_PIN, GPIO_PIN_SET);
		} else if (duty < 0){
			HAL_GPIO_WritePin(MD_BOX2_1_PORT, MD_BOX2_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_BOX2_2_PORT, MD_BOX2_2_PIN, GPIO_PIN_RESET);
		}else {
			HAL_GPIO_WritePin(MD_BOX2_1_PORT, MD_BOX2_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_BOX2_2_PORT, MD_BOX2_2_PIN, GPIO_PIN_SET);
		}

	}
}



/*
 * 指定されたduty比でモータを回す
 * @param	spd_duty : duty比。-1 ~ 1
 * @return
 */
void CoordinateSetDuty(float duty,int MD_ID){
	uint16_t pwm = 0;

	//-1 ~ 1に制限
	if(duty  !=MOTOR_BRAKE){
		duty = fmax(fminf(duty,1),-1);
	}
	if(MD_ID == MD_R_ID){
		//回転方向を設定
		CoordinateSetDirection(duty,MD_ID);

		//Duty比の絶対値をとるとともに、DUTY比を制限する
		if(duty != MOTOR_BRAKE){
			duty = fabsf(duty);
			pwm = duty * PWM_ARR;

			//各チャンネルにコンペアマッチ値を設定
			__HAL_TIM_SET_COMPARE(&MD_R_TIM_HANDLER, MD_R_PWM_TIM_CH, 	pwm);
		}else if(duty == MOTOR_BRAKE){
			__HAL_TIM_SET_COMPARE(&MD_R_TIM_HANDLER, MD_R_PWM_TIM_CH, 	0);
			HAL_GPIO_WritePin(MD_R_1_PORT, MD_R_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_R_2_PORT, MD_R_2_PIN, GPIO_PIN_SET);
		}
	}else if(MD_ID == MD_THITA_ID){
		//回転方向を設定
		CoordinateSetDirection(duty,MD_ID);

		//Duty比の絶対値をとるとともに、DUTY比を制限する
		if(duty != MOTOR_BRAKE){
			duty = fabsf(duty);
			pwm = duty * PWM_ARR;

			//各チャンネルにコンペアマッチ値を設定
			__HAL_TIM_SET_COMPARE(&MD_THITA_TIM_HANDLER, MD_THITA_PWM_TIM_CH, 	pwm);
		}else if(duty == MOTOR_BRAKE){
			__HAL_TIM_SET_COMPARE(&MD_THITA_TIM_HANDLER, MD_THITA_PWM_TIM_CH, 	0);
			HAL_GPIO_WritePin(MD_THITA_1_PORT, MD_THITA_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_THITA_2_PORT, MD_THITA_2_PIN, GPIO_PIN_SET);
		}
	}else if(MD_ID == MD_Z_ID){
		//回転方向を設定
		CoordinateSetDirection(duty,MD_ID);

		//Duty比の絶対値をとるとともに、DUTY比を制限する
		if(duty != MOTOR_BRAKE){
			duty = fabsf(duty);
			pwm = duty * PWM_ARR;

			//各チャンネルにコンペアマッチ値を設定
			__HAL_TIM_SET_COMPARE(&MD_Z_TIM_HANDLER, MD_Z_PWM_TIM_CH, 	pwm);
		}else if(duty == MOTOR_BRAKE){
			__HAL_TIM_SET_COMPARE(&MD_Z_TIM_HANDLER, MD_Z_PWM_TIM_CH, 	0);
			HAL_GPIO_WritePin(MD_Z_1_PORT, MD_Z_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_Z_2_PORT, MD_Z_2_PIN, GPIO_PIN_SET);
		}
	}else if(MD_ID == MD_BOX1_ID){
		//回転方向を設定
		CoordinateSetDirection(duty,MD_ID);

		//Duty比の絶対値をとるとともに、DUTY比を制限する
		if(duty != MOTOR_BRAKE){
			duty = fabsf(duty);
			pwm = duty * PWM_ARR;

			//各チャンネルにコンペアマッチ値を設定
			__HAL_TIM_SET_COMPARE(&MD_BOX1_TIM_HANDLER, MD_BOX1_PWM_TIM_CH, 	pwm);
		}else if(duty == MOTOR_BRAKE){
			__HAL_TIM_SET_COMPARE(&MD_BOX1_TIM_HANDLER, MD_BOX1_PWM_TIM_CH, 	0);
			HAL_GPIO_WritePin(MD_BOX1_1_PORT, MD_BOX1_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_BOX1_2_PORT, MD_BOX1_2_PIN, GPIO_PIN_SET);
		}
	}else if(MD_ID == MD_BOX2_ID){
		//回転方向を設定
		CoordinateSetDirection(duty,MD_ID);

		//Duty比の絶対値をとるとともに、DUTY比を制限する
		if(duty != MOTOR_BRAKE){
			duty = fabsf(duty);
			pwm = duty * PWM_ARR;

			//各チャンネルにコンペアマッチ値を設定
			__HAL_TIM_SET_COMPARE(&MD_BOX2_TIM_HANDLER, MD_BOX2_PWM_TIM_CH, 	pwm);
		}else if(duty == MOTOR_BRAKE){
			__HAL_TIM_SET_COMPARE(&MD_BOX2_TIM_HANDLER, MD_BOX2_PWM_TIM_CH, 	0);
			HAL_GPIO_WritePin(MD_BOX2_1_PORT, MD_BOX2_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_BOX2_2_PORT, MD_BOX2_2_PIN, GPIO_PIN_SET);
		}
	}
}

/*
 * dutyの正負からモータの回転方向を指定
 * @param	duty_r, duty_theta, duty_z, duty_hand : 各軸のduty比
 * @return
 */


/*
 * タイマENABLE
 * @param
 * @return
 */
void CoordinateEnable(void) {

	HAL_TIM_PWM_Start(&MD_R_TIM_HANDLER, MD_R_PWM_TIM_CH);
	HAL_TIM_PWM_Start(&MD_THITA_TIM_HANDLER, MD_THITA_PWM_TIM_CH);
	HAL_TIM_PWM_Start(&MD_Z_TIM_HANDLER, MD_Z_PWM_TIM_CH);

	HAL_TIM_PWM_Start(&MD_BOX1_TIM_HANDLER, MD_BOX1_PWM_TIM_CH);
	HAL_TIM_PWM_Start(&MD_BOX2_TIM_HANDLER, MD_BOX2_PWM_TIM_CH);
	//	CoordinateSetDuty(0);
}

/*
 * タイマDISABLE
 * @param
 * @return
 */
void CoordinateDisable(void) {
//	CoordinateSetDuty(0);
	HAL_TIM_PWM_Stop(&MD_R_TIM_HANDLER, MD_R_PWM_TIM_CH);
	HAL_TIM_PWM_Stop(&MD_THITA_TIM_HANDLER, MD_THITA_PWM_TIM_CH);
	HAL_TIM_PWM_Stop(&MD_Z_TIM_HANDLER, MD_Z_PWM_TIM_CH);

	HAL_TIM_PWM_Stop(&MD_BOX1_TIM_HANDLER, MD_BOX1_PWM_TIM_CH);
	HAL_TIM_PWM_Stop(&MD_BOX2_TIM_HANDLER, MD_BOX2_PWM_TIM_CH);
}





