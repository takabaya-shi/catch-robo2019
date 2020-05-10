/*
 * motor.c
 *
 *  Created on: 2019/09/07
 *      Author: tomok
 */

#include "math.h"
#include "motor.h"
#include "stm32f4xx_hal.h"


extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;
/*-----------------------------------------------
 * ���W�����[�^
-----------------------------------------------*/
//static void CoordinateSetDirection(float duty,int MD_ID);
void CoordinateSetDirection(float duty,int MD_ID) {
	if(MD_ID == MD1_ID){
		if (duty > 0) {
			HAL_GPIO_WritePin(MD1_1_PORT, MD1_1_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MD1_2_PORT, MD1_2_PIN, GPIO_PIN_SET);
		} else if (duty < 0){
			HAL_GPIO_WritePin(MD1_1_PORT, MD1_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD1_2_PORT, MD1_2_PIN, GPIO_PIN_RESET);
		}else {
			HAL_GPIO_WritePin(MD1_1_PORT, MD1_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD1_2_PORT, MD1_2_PIN, GPIO_PIN_SET);
		}

	}else if(MD_ID == MD2_ID){
		if (duty > 0) {
			HAL_GPIO_WritePin(MD2_1_PORT, MD2_1_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MD2_2_PORT, MD2_2_PIN, GPIO_PIN_SET);
		} else if (duty < 0){
			HAL_GPIO_WritePin(MD2_1_PORT, MD2_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD2_2_PORT, MD2_2_PIN, GPIO_PIN_RESET);
		}else {
			HAL_GPIO_WritePin(MD2_1_PORT, MD2_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD2_2_PORT, MD2_2_PIN, GPIO_PIN_SET);
		}

	}else if(MD_ID == MD3_ID){
		if (duty > 0) {
			HAL_GPIO_WritePin(MD3_1_PORT, MD3_1_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MD3_2_PORT, MD3_2_PIN, GPIO_PIN_SET);
		} else if (duty < 0){
			HAL_GPIO_WritePin(MD3_1_PORT, MD3_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD3_2_PORT, MD3_2_PIN, GPIO_PIN_RESET);
		}else {
			HAL_GPIO_WritePin(MD3_1_PORT, MD3_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD3_2_PORT, MD3_2_PIN, GPIO_PIN_SET);
		}

	}else if(MD_ID == MD4_ID){
		if (duty > 0) {
			HAL_GPIO_WritePin(MD4_1_PORT, MD4_1_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MD4_2_PORT, MD4_2_PIN, GPIO_PIN_SET);
		} else if (duty < 0){
			HAL_GPIO_WritePin(MD4_1_PORT, MD4_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD4_2_PORT, MD4_2_PIN, GPIO_PIN_RESET);
		}else {
			HAL_GPIO_WritePin(MD4_1_PORT, MD4_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD4_2_PORT, MD4_2_PIN, GPIO_PIN_SET);
		}
	}
}



/*
 * �w�肳�ꂽduty��Ń��[�^����
 * @param	spd_duty : duty��B-1 ~ 1
 * @return
 */
void CoordinateSetDuty(float duty,int MD_ID){
	uint16_t pwm = 0;

	//-1 ~ 1�ɐ���
	if(duty  !=MOTOR_BRAKE){
		duty = fmax(fminf(duty,1),-1);
	}
	if(MD_ID == MD1_ID){
		//��]������ݒ�
		CoordinateSetDirection(duty,MD_ID);

		//Duty��̐�Βl���Ƃ�ƂƂ��ɁADUTY��𐧌�����
		if(duty != MOTOR_BRAKE){
			duty = fabsf(duty);
			pwm = duty * PWM_ARR;

			//�e�`�����l���ɃR���y�A�}�b�`�l��ݒ�
			__HAL_TIM_SET_COMPARE(&MD1_TIM_HANDLER, MD1_PWM_TIM_CH, 	pwm);
		}else if(duty == MOTOR_BRAKE){
			__HAL_TIM_SET_COMPARE(&MD1_TIM_HANDLER, MD1_PWM_TIM_CH, 	0);
			HAL_GPIO_WritePin(MD1_1_PORT, MD1_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD1_2_PORT, MD1_2_PIN, GPIO_PIN_SET);
		}
	}else if(MD_ID == MD2_ID){
		//��]������ݒ�
		CoordinateSetDirection(duty,MD_ID);

		//Duty��̐�Βl���Ƃ�ƂƂ��ɁADUTY��𐧌�����
		if(duty != MOTOR_BRAKE){
			duty = fabsf(duty);
			pwm = duty * PWM_ARR;

			//�e�`�����l���ɃR���y�A�}�b�`�l��ݒ�
			__HAL_TIM_SET_COMPARE(&MD2_TIM_HANDLER, MD2_PWM_TIM_CH, 	pwm);
		}else if(duty == MOTOR_BRAKE){
			__HAL_TIM_SET_COMPARE(&MD2_TIM_HANDLER, MD2_PWM_TIM_CH, 	0);
			HAL_GPIO_WritePin(MD2_1_PORT, MD2_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD2_2_PORT, MD2_2_PIN, GPIO_PIN_SET);
		}
	}else if(MD_ID == MD3_ID){
		//��]������ݒ�
		CoordinateSetDirection(duty,MD_ID);

		//Duty��̐�Βl���Ƃ�ƂƂ��ɁADUTY��𐧌�����
		if(duty != MOTOR_BRAKE){
			duty = fabsf(duty);
			pwm = duty * PWM_ARR;

			//�e�`�����l���ɃR���y�A�}�b�`�l��ݒ�
			__HAL_TIM_SET_COMPARE(&MD3_TIM_HANDLER, MD3_PWM_TIM_CH, 	pwm);
		}else if(duty == MOTOR_BRAKE){
			__HAL_TIM_SET_COMPARE(&MD3_TIM_HANDLER, MD3_PWM_TIM_CH, 	0);
			HAL_GPIO_WritePin(MD3_1_PORT, MD3_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD3_2_PORT, MD3_2_PIN, GPIO_PIN_SET);
		}
	}else if(MD_ID == MD4_ID){
		//��]������ݒ�
		CoordinateSetDirection(duty,MD_ID);

		//Duty��̐�Βl���Ƃ�ƂƂ��ɁADUTY��𐧌�����
		if(duty != MOTOR_BRAKE){
			duty = fabsf(duty);
			pwm = duty * PWM_ARR;
			//�e�`�����l���ɃR���y�A�}�b�`�l��ݒ�
			__HAL_TIM_SET_COMPARE(&MD4_TIM_HANDLER, MD4_PWM_TIM_CH, 	pwm);
		}else if(duty == MOTOR_BRAKE){
			__HAL_TIM_SET_COMPARE(&MD4_TIM_HANDLER, MD4_PWM_TIM_CH, 	0);
			HAL_GPIO_WritePin(MD4_1_PORT, MD4_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD4_2_PORT, MD4_2_PIN, GPIO_PIN_SET);
		}
	}
}

/*
 * duty�̐������烂�[�^�̉�]�������w��
 * @param	duty_r, duty_theta, duty_z, duty_hand : �e����duty��
 * @return
 */


/*
 * �^�C�}ENABLE
 * @param
 * @return
 */
void CoordinateEnable(void) {

	HAL_TIM_PWM_Start(&MD1_TIM_HANDLER, MD1_PWM_TIM_CH);
	HAL_TIM_PWM_Start(&MD2_TIM_HANDLER, MD2_PWM_TIM_CH);
	HAL_TIM_PWM_Start(&MD3_TIM_HANDLER, MD3_PWM_TIM_CH);
	HAL_TIM_PWM_Start(&MD4_TIM_HANDLER, MD4_PWM_TIM_CH);
//	CoordinateSetDuty(0);
}

/*
 * �^�C�}DISABLE
 * @param
 * @return
 */
void CoordinateDisable(void) {
//	CoordinateSetDuty(0);
	HAL_TIM_PWM_Stop(&MD1_TIM_HANDLER, MD1_PWM_TIM_CH);
	HAL_TIM_PWM_Stop(&MD2_TIM_HANDLER, MD2_PWM_TIM_CH);
	HAL_TIM_PWM_Stop(&MD3_TIM_HANDLER, MD3_PWM_TIM_CH);
	HAL_TIM_PWM_Stop(&MD4_TIM_HANDLER, MD4_PWM_TIM_CH);
}




