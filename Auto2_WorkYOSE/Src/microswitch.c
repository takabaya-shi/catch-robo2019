/*
 * microswitch.c
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */


#include "microswitch.h"

/*
 * 全てのマイクロスイッチを調べる
 * @param
 * @return	SWITCH_ON/SWITCH_OFF
 */

/*
 * マイクロスイッチのON/OFFを返す
 * @param	switch_num : ボタンの番号
 * @return	MICROSW_ON / MICROSW_OFF
 */
uint8_t MicroSwitchIsOn(uint8_t switch_num) {
#ifdef MICROSW_POSITIVE_LOGIC
	switch (switch_num) {
	case MICSW_X_MAX     : if (HAL_GPIO_ReadPin(MICSW_X_MAX_PORT, MICSW_X_MAX_PIN) == GPIO_PIN_SET) return MICROSW_ON;
						   else																		return MICROSW_OFF;
						   break;
	case MICSW_Y_MAX     : if (HAL_GPIO_ReadPin(MICSW_Y_MAX_PORT, MICSW_Y_MAX_PIN) == GPIO_PIN_SET) return MICROSW_ON;
						   else																		return MICROSW_OFF;
					       break;
	default              : return MICROSW_OFF;
	}
#endif

	//負論理
#ifdef MICROSW_NEGATIVE_LOGIC
	switch (switch_num) {
	case MICSW_X_MAX     : if (HAL_GPIO_ReadPin(MICSW_X_MAX_PORT, MICSW_X_MAX_PIN) == GPIO_PIN_SET) return MICROSW_OFF;
						   else																		return MICROSW_ON;
					       break;
	case MICSW_Y_MAX     : if (HAL_GPIO_ReadPin(MICSW_Y_MAX_PORT, MICSW_Y_MAX_PIN) == GPIO_PIN_SET) return MICROSW_OFF;
						   else																		return MICROSW_ON;
					       break;
	default              : return MICROSW_OFF;
	}
#endif
}

/*
 * マイクロスイッチがOFFになるまで待つ
 * @param	switch_num : ボタンの番号
 * @return
 */
void MicroSwitchWaitOff(uint8_t switch_num) {
	HAL_Delay(100);											//チャタリング防止
	while (MicroSwitchIsOn(switch_num) == MICROSW_ON) ;		//ボタンが押されている間待つ
	HAL_Delay(100);											//チャタリング防止
	while (MicroSwitchIsOn(switch_num) == MICROSW_ON) ;		//ボタンが押されている間待つ
}



