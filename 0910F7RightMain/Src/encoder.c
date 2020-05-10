/*
 * encoder.c
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#include "encoder.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

/*
 * 円筒座標系での現在位置を構造体に保存
 * @param
 * @return
 * @note	グローバル構造体変数の現在座標を更新
 */
void GetPosCyl(void) {
	int16_t r_diff, theta_diff, z_diff;

	//差分を取得
	EncGetCountDiff(&r_diff, &theta_diff, &z_diff);

	//現在位置を求める
	poscyl.r     = (float)(r_diff * R_PINION_DIAMETER * 2 * M_PI * 500.0f * 520.0f) / (float)(ENC_R_RESOLUTION * 540.0f * 450.0f* MOTOR_R_GEARHEAD);
	//poscyl.theta += (float)(theta_diff * 2 * M_PI) / (float)(ENC_THETA_RESOLUTION * MOTOR_THETA_GEARHEAD * THETA_GEARRATIO);
	poscyl.theta	+= (float)(theta_diff * 94.0f * M_PI * 500.0f)/(float)(ENC_THITA_RESOLUTION * 1.0f * 180.0f * 781.0f);
	//poscyl.theta	= (float)(theta_diff * 68.0f * M_PI)/(float)(1024.0f * 4 * 180.0f);
	poscyl.z     = (float)(z_diff * Z_PINION_DIAMETER * M_PI * 2) / (float)(ENC_Z_RESOLUTION / 2);

	Cyl2Rec(&poscyl, &posrec);
}

/*
 * エンコーダタイマカウント値の差分を返す
 * @param
 * @return
 * @note	ポインタ渡しの変数に各エンコーダの差分を代入
 */
void EncGetCountDiff(int16_t *r_diff, int16_t *theta_diff, int16_t *z_diff) {
	//差分を返す
	//*r_diff     = ENC_R_TIMx->CNT     - 32768;
	*theta_diff = ENC_THETA_TIMx->CNT - 32768;
	//*z_diff     = ENC_Z_TIMx->CNT     - 32768;

	*r_diff     = ENC_R_TIMx->CNT;
	*z_diff     = ENC_Z_TIMx->CNT;
	//*theta_diff = ENC_THETA_TIMx->CNT - 32768;



	//値をリセット
//	ENC_R_TIMx->CNT     = 32768;
	ENC_THETA_TIMx->CNT = 32768;
	//ENC_Z_TIMx->CNT     = 32768;
}

/*
 * エンコーダタイマENABLE
 * @param
 * @return
 */
void EncEnable(void) {
	HAL_TIM_Encoder_Start(&ENC_R_TIM_HANDLER,     TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&ENC_THETA_TIM_HANDLER, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&ENC_Z_TIM_HANDLER,     TIM_CHANNEL_ALL);

	//値をリセット
//	ENC_R_TIMx->CNT     = 32768;
	ENC_THETA_TIMx->CNT = 32768;
//	ENC_Z_TIMx->CNT     = 32768;
	ENC_R_TIMx->CNT = 0;
	ENC_Z_TIMx->CNT = 0;
//	ENC_THETA_TIMx->CNT = 0;
}

/*
 * エンコーダタイマDISABLE
 * @param
 * @return
 */
void EncDisable(void) {
	HAL_TIM_Encoder_Stop(&ENC_R_TIM_HANDLER,     TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Stop(&ENC_THETA_TIM_HANDLER, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Stop(&ENC_Z_TIM_HANDLER,     TIM_CHANNEL_ALL);

	//値をリセット
	ENC_R_TIMx->CNT     = 32768;
	ENC_THETA_TIMx->CNT = 32768;
	ENC_Z_TIMx->CNT     = 32768;
}


