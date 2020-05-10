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
 * �~�����W�n�ł̌��݈ʒu���\���̂ɕۑ�
 * @param
 * @return
 * @note	�O���[�o���\���̕ϐ��̌��ݍ��W���X�V
 */
float GetPos() {
	int16_t r_diff;
	float robot_pos = 0;


	//�������擾
	EncGetData(&r_diff);


	//���݈ʒu�����߂�

	//robot_pos     += (float)(r_diff * R_PINION_DIAMETER * M_PI) / (float)(ENC_R_RESOLUTION * MOTOR_R_GEARHEAD);
	//robot_pos     += (float)(-r_diff * R_PINION_DIAMETER * M_PI) / (float)(ENC_R_RESOLUTION * MOTOR_R_GEARHEAD);
	robot_pos 	+= (float)(r_diff * PINION_DIAMETER * M_PI) / (float)(ENC_SELECT_RESOLUTION);

	return robot_pos;
}

/*
 * �G���R�[�_�^�C�}ENABLE
 * @param
 * @return
 */
void EncEnable(void){
	HAL_TIM_Encoder_Start(&ENC_1_TIM_HANDLER,TIM_CHANNEL_ALL);

	//�l�����Z�b�g
	ENC_1_TIM -> CNT	= 32768;
}

/*
 * �G���R�[�_�^�C�}DISABLE
 * @param
 * @return
 */
void EncDisable(void){
	HAL_TIM_Encoder_Stop(&ENC_1_TIM_HANDLER,TIM_CHANNEL_ALL);

	//�l�����Z�b�g
	ENC_1_TIM -> CNT	= 0;
}

/*
 * �G���R�[�_�^�C�}�J�E���g�l�̍�����Ԃ�
 * @param
 * @return
 * @note	�|�C���^�n���̕ϐ��Ɋe�G���R�[�_�̍��������BKS�TN�͕���\�S�~�̂��߁A�^�C�}�[���荞�݂ŏ������𖈉񂷂�ƒl��ǂޑO�ɏ���������Ă��܂��B
 */
void EncGetData(int16_t *enc_1_buf){
	*enc_1_buf = ENC_1_TIM->CNT -32768;
//	*enc_1_buf = ENC_1_TIM->CNT;


	ENC_1_TIM -> CNT	= 32768;
}
