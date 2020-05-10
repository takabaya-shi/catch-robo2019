/*
 * microswitch.c
 *
 *  Created on: 2019/09/02
 *      Author: tomok
 */

#include "microswitch.h"

/*
 * �S�Ẵ}�C�N���X�C�b�`�𒲂ׂ�
 * @param
 * @return	SWITCH_ON/SWITCH_OFF
 */

/*
 * �}�C�N���X�C�b�`��ON/OFF��Ԃ�
 * @param	switch_num : �{�^���̔ԍ�
 * @return	MICROSW_ON / MICROSW_OFF
 */
uint8_t MicroSwitchIsOn(uint8_t switch_num) {
#ifdef MICROSW_POSITIVE_LOGIC
	switch (switch_num) {
	case MICSW_R_MAX     : if (HAL_GPIO_ReadPin(MICSW_R_MAX_PORT, MICSW_R_MAX_PIN) == GPIO_PIN_SET) return MICROSW_ON;
						   else																		return MICROSW_OFF;
						   break;
	case MICSW_R_MIN     : if (HAL_GPIO_ReadPin(MICSW_R_MIN_PORT, MICSW_R_MIN_PIN) == GPIO_PIN_SET) return MICROSW_ON;
						   else																		return MICROSW_OFF;
					       break;
	case MICSW_THETA_MAX : if (HAL_GPIO_ReadPin(MICSW_THETA_MAX_PORT, MICSW_THETA_MAX_PIN) == GPIO_PIN_SET) return MICROSW_ON;
						   else																				return MICROSW_OFF;
					       break;
	case MICSW_THETA_MIN : if (HAL_GPIO_ReadPin(MICSW_THETA_MIN_PORT, MICSW_THETA_MIN_PIN) == GPIO_PIN_SET) return MICROSW_ON;
						   else																				return MICROSW_OFF;
					       break;
	case MICSW_Z_MAX     : if (HAL_GPIO_ReadPin(MICSW_Z_MAX_PORT, MICSW_Z_MAX_PIN) == GPIO_PIN_SET) return MICROSW_ON;
						   else																		return MICROSW_OFF;
					       break;
	case MICSW_Z_MIN     : if (HAL_GPIO_ReadPin(MICSW_Z_MIN_PORT, MICSW_Z_MIN_PIN) == GPIO_PIN_SET) return MICROSW_ON;
						   else																		return MICROSW_OFF;
					       break;
	default              : return MICROSW_OFF;
	}
#endif

	//���_��
#ifdef MICROSW_NEGATIVE_LOGIC
	switch (switch_num) {
	case MICSW_R_MAX     : if (HAL_GPIO_ReadPin(MICSW_R_MAX_PORT, MICSW_R_MAX_PIN) == GPIO_PIN_SET) return MICROSW_OFF;
						   else																		return MICROSW_ON;
					       break;
	case MICSW_R_MIN     : if (HAL_GPIO_ReadPin(MICSW_R_MIN_PORT, MICSW_R_MIN_PIN) == GPIO_PIN_SET) return MICROSW_OFF;
						   else																		return MICROSW_ON;
					       break;
	case MICSW_THETA_MAX : if (HAL_GPIO_ReadPin(MICSW_THETA_MAX_PORT, MICSW_THETA_MAX_PIN) == GPIO_PIN_SET) return MICROSW_OFF;
						   else																				return MICROSW_ON;
					       break;
	case MICSW_THETA_MIN : if (HAL_GPIO_ReadPin(MICSW_THETA_MIN_PORT, MICSW_THETA_MIN_PIN) == GPIO_PIN_SET) return MICROSW_OFF;
						   else																				return MICROSW_ON;
					       break;
	case MICSW_Z_MAX     : if (HAL_GPIO_ReadPin(MICSW_Z_MAX_PORT, MICSW_Z_MAX_PIN) == GPIO_PIN_SET) return MICROSW_OFF;
						   else																		return MICROSW_ON;
					       break;
	case MICSW_Z_MIN     : if (HAL_GPIO_ReadPin(MICSW_Z_MIN_PORT, MICSW_Z_MIN_PIN) == GPIO_PIN_SET) return MICROSW_OFF;
						   else																		return MICROSW_ON;
					       break;
	default              : return MICROSW_OFF;
	}
#endif
}

/*
 * �}�C�N���X�C�b�`��OFF�ɂȂ�܂ő҂�
 * @param	switch_num : �{�^���̔ԍ�
 * @return
 */
void MicroSwitchWaitOff(uint8_t switch_num) {
	HAL_Delay(100);											//�`���^�����O�h�~
	while (MicroSwitchIsOn(switch_num) == MICROSW_ON) ;		//�{�^����������Ă���ԑ҂�
	HAL_Delay(100);											//�`���^�����O�h�~
	while (MicroSwitchIsOn(switch_num) == MICROSW_ON) ;		//�{�^����������Ă���ԑ҂�
}

