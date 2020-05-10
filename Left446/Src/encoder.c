/*
 * encoder.c
 *
 *  Created on: 2019/09/07
 *      Author: tomok
 */

#include "encoder.h"


//float robot_pos = 0;
float current_diff = 0;
float prev_diff = 0;
float integral = 0;

void PIDOut(float current_pos,float target_pos){
	float duty;
	current_diff = target_pos     - current_pos;
	integral = integral + (current_diff + prev_diff) /2.0f * MD_DELTA_T;

	duty     = current_diff * (PID_P) + 0.01f * (current_diff - prev_diff)/MD_DELTA_T + integral * 0.0f;
	prev_diff = current_diff;

	CoordinateSetDuty(duty);
}


/*
 * 円筒座標系での現在位置を構造体に保存
 * @param
 * @return
 * @note	グローバル構造体変数の現在座標を更新
 */
float GetPos() {
	int16_t r_diff;
	float robot_pos = 0;


	//差分を取得
	EncGetData(&r_diff);


	//現在位置を求める

	//robot_pos     += (float)(r_diff * R_PINION_DIAMETER * M_PI) / (float)(ENC_R_RESOLUTION * MOTOR_R_GEARHEAD);
	//robot_pos     += (float)(-r_diff * R_PINION_DIAMETER * M_PI) / (float)(ENC_R_RESOLUTION * MOTOR_R_GEARHEAD);
	robot_pos 	+= (float)(r_diff * PINION_DIAMETER * M_PI) / (float)(ENC_SELECT_RESOLUTION);

	return robot_pos;
}

/*
 * エンコーダタイマENABLE
 * @param
 * @return
 */
void EncEnable(void){
	HAL_TIM_Encoder_Start(&ENC_1_TIM_HANDLER,TIM_CHANNEL_ALL);

	//値をリセット
	ENC_1_TIM -> CNT	= 32768;
}

/*
 * エンコーダタイマDISABLE
 * @param
 * @return
 */
void EncDisable(void){
	HAL_TIM_Encoder_Stop(&ENC_1_TIM_HANDLER,TIM_CHANNEL_ALL);

	//値をリセット
	ENC_1_TIM -> CNT	= 0;
}

/*
 * エンコーダタイマカウント値の差分を返す
 * @param
 * @return
 * @note	ポインタ渡しの変数に各エンコーダの差分を代入。KS５Nは分解能ゴミのため、タイマー割り込みで初期化を毎回すると値を読む前に初期化されてしまう。
 */
void EncGetData(int16_t *enc_1_buf){
	*enc_1_buf = ENC_1_TIM->CNT -32768;
//	*enc_1_buf = ENC_1_TIM->CNT;


	ENC_1_TIM -> CNT	= 32768;
}
