/*
 * motor.c
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

#include "math.h"
#include "motor.h"
#include "stm32f3xx_hal.h"


extern TIM_HandleTypeDef htim3;

/*-----------------------------------------------
 * ���W�����[�^
-----------------------------------------------*/
//static void CoordinateSetDirection(float duty,int MD_ID);
void CoordinateSetDirection(float duty,int MD_ID) {
	if(MD_ID == MD_X_ID){
		if (duty > 0) {
			HAL_GPIO_WritePin(MD_X_1_PORT, MD_X_1_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MD_X_2_PORT, MD_X_2_PIN, GPIO_PIN_SET);
		} else if (duty < 0){
			HAL_GPIO_WritePin(MD_X_1_PORT, MD_X_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_X_2_PORT, MD_X_2_PIN, GPIO_PIN_RESET);
		}else {
			HAL_GPIO_WritePin(MD_X_1_PORT, MD_X_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_X_2_PORT, MD_X_2_PIN, GPIO_PIN_SET);
		}

	}else if(MD_ID == MD_Y_ID){
		if (duty > 0) {
			HAL_GPIO_WritePin(MD_Y_1_PORT, MD_Y_1_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(MD_Y_2_PORT, MD_Y_2_PIN, GPIO_PIN_SET);
		} else if (duty < 0){
			HAL_GPIO_WritePin(MD_Y_1_PORT, MD_Y_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_Y_2_PORT, MD_Y_2_PIN, GPIO_PIN_RESET);
		}else {
			HAL_GPIO_WritePin(MD_Y_1_PORT, MD_Y_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_Y_2_PORT, MD_Y_2_PIN, GPIO_PIN_SET);
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
	if(MD_ID == MD_X_ID){
		//��]������ݒ�
		CoordinateSetDirection(duty,MD_ID);

		//Duty��̐�Βl���Ƃ�ƂƂ��ɁADUTY��𐧌�����
		if(duty != MOTOR_BRAKE){
			duty = fabsf(duty);
			pwm = duty * PWM_ARR;

			//�e�`�����l���ɃR���y�A�}�b�`�l��ݒ�
			__HAL_TIM_SET_COMPARE(&MD_X_TIM_HANDLER, MD_X_PWM_TIM_CH, 	pwm);
		}else if(duty == MOTOR_BRAKE){
			__HAL_TIM_SET_COMPARE(&MD_X_TIM_HANDLER, MD_X_PWM_TIM_CH, 	0);
			HAL_GPIO_WritePin(MD_X_1_PORT, MD_X_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_X_2_PORT, MD_X_2_PIN, GPIO_PIN_SET);
		}
	}else if(MD_ID == MD_Y_ID){
		//��]������ݒ�
		CoordinateSetDirection(duty,MD_ID);

		//Duty��̐�Βl���Ƃ�ƂƂ��ɁADUTY��𐧌�����
		if(duty != MOTOR_BRAKE){
			duty = fabsf(duty);
			pwm = duty * PWM_ARR;
			//�e�`�����l���ɃR���y�A�}�b�`�l��ݒ�
			__HAL_TIM_SET_COMPARE(&MD_Y_TIM_HANDLER, MD_Y_PWM_TIM_CH, 	pwm);
		}else if(duty == MOTOR_BRAKE){
			__HAL_TIM_SET_COMPARE(&MD_Y_TIM_HANDLER, MD_Y_PWM_TIM_CH, 	0);
			HAL_GPIO_WritePin(MD_Y_1_PORT, MD_Y_1_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(MD_Y_2_PORT, MD_Y_2_PIN, GPIO_PIN_SET);
		}
	}
}

/*
 * duty�̐������烂�[�^�̉�]�������w��
 * @param	duty_r, duty_theta, duty_z, duty_hand : �e����duty��
 * @return
 */


/*
 * �ڕW�~�����W�ʒu�ɓ�����
 * @param
 * @return
 */
void CoordinateSetPosPID(void) {
	float duty_X, duty_Y, duty_BOX1, duty_BOX2;
	static float prev_z = 0;

	//�e���[�^��Duty�������
	duty_X     = (posrec.x     - refrec.x)     * (-17.5f);
	duty_Y = (posrec.y - refrec.y) * (-7.5f) ;

	//���[�^�ɏo��
	CoordinateSetDuty(duty_X,MD_X_ID);
	CoordinateSetDuty(duty_Y,MD_Y_ID);
}


/*
 * �^�C�}ENABLE
 * @param
 * @return
 */
void CoordinateEnable(void) {

	HAL_TIM_PWM_Start(&MD_X_TIM_HANDLER, MD_X_PWM_TIM_CH);
	HAL_TIM_PWM_Start(&MD_Y_TIM_HANDLER, MD_Y_PWM_TIM_CH);
//	CoordinateSetDuty(0);
}

/*
 * �^�C�}DISABLE
 * @param
 * @return
 */
void CoordinateDisable(void) {
//	CoordinateSetDuty(0);
	HAL_TIM_PWM_Stop(&MD_X_TIM_HANDLER, MD_X_PWM_TIM_CH);
	HAL_TIM_PWM_Stop(&MD_Y_TIM_HANDLER, MD_Y_PWM_TIM_CH);
}


