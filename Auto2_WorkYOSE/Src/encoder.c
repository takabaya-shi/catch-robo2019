/*
 * encoder.c
 *
 *  Created on: 2019/09/09
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
void GetPos(void) {
	int16_t X_diff, Y_diff;

	//�������擾
	EncGetData(&X_diff,&Y_diff);

	//���݈ʒu�����߂�

	//robot_pos     += (float)(r_diff * R_PINION_DIAMETER * M_PI) / (float)(ENC_R_RESOLUTION * MOTOR_R_GEARHEAD);
	//robot_pos     += (float)(-r_diff * R_PINION_DIAMETER * M_PI) / (float)(ENC_R_RESOLUTION * MOTOR_R_GEARHEAD);
	//robot_pos 	+= (float)(r_diff * PINION_DIAMETER * M_PI) / (float)(ENC_SELECT_RESOLUTION);

	posrec.x 		+= (float)(X_diff * 1) / (float)(ENC_X_RESOLUTION);
	posrec.y 		+= (float)(Y_diff * 1) / (float)(ENC_Y_RESOLUTION);

}

/*
 * �G���R�[�_�^�C�}ENABLE
 * @param
 * @return
 */
void EncEnable(void){
	HAL_TIM_Encoder_Start(&ENC_X_TIM_HANDLER,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&ENC_Y_TIM_HANDLER,TIM_CHANNEL_ALL);

	//�l�����Z�b�g
	ENC_X_TIM -> CNT	= 32768;
	ENC_Y_TIM -> CNT	= 32768;
}

/*
 * �G���R�[�_�^�C�}DISABLE
 * @param
 * @return
 */
void EncDisable(void){
	HAL_TIM_Encoder_Stop(&ENC_X_TIM_HANDLER,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Stop(&ENC_Y_TIM_HANDLER,TIM_CHANNEL_ALL);

	//�l�����Z�b�g
	ENC_X_TIM -> CNT	= 0;
	ENC_Y_TIM -> CNT	= 0;
}

/*
 * �G���R�[�_�^�C�}�J�E���g�l�̍�����Ԃ�
 * @param
 * @return
 * @note	�|�C���^�n���̕ϐ��Ɋe�G���R�[�_�̍��������BKS�TN�͕���\�S�~�̂��߁A�^�C�}�[���荞�݂ŏ������𖈉񂷂�ƒl��ǂޑO�ɏ���������Ă��܂��B
 */
void EncGetData(int16_t *enc_1_buf,int16_t *enc_2_buf){
	*enc_1_buf = ENC_X_TIM->CNT -32768;
	*enc_2_buf = ENC_Y_TIM->CNT -32768;

	//	*enc_1_buf = ENC_1_TIM->CNT;

	ENC_X_TIM -> CNT	= 32768;
	ENC_Y_TIM -> CNT	= 32768;

}

