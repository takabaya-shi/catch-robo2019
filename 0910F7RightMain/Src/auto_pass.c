/*
 * auto_pass.c
 *
 *  Created on: 2019/09/12
 *      Author: tomok
 */


#include "motor.h"
#include "robotstate.h"
#include "encoder.h"
#include "auto_pass.h"
#include "microswitch.h"
#include "brushless.h"

int auto_count = 0;
uint16_t MSW_Z_MIN_FLAG = 0;
uint16_t MSW_Z_MAX_FLAG = 0;
uint16_t MSW_BOX_Z_MIN_FLAG = 0;
uint16_t MSW_BOX_Z_MAX_FLAG = 0;
uint16_t MSW_WORK_Z_MIN_FLAG = 0;
uint16_t MSW_WORK_Z_MAX_FLAG = 0;

//�~���̈��莩�������s���֐�
//��{�I��XYZ���W��CoordinateSetPosXYZ�Ŏ������āA���ۂɂ��̈ʒu�ɂȂ����玟�̒i�K�Ɉڍs����悤�ɂ��Ă���
//auto_flag��0�Ȃ�蓮�ł���ȊO�Ȃ玩���ł��邱�Ƃ�\���B�����̊Ԃł�auto_flag��0�������邱�ƂŎ蓮�ɂ����ɐ؂�ւ��
void Auto_Set(uint16_t *auto_flag,uint16_t *button_flag){
	float refrec_x_max;
	float refrec_x_min;
	float refrec_y_max;
	float refrec_y_min;
	float refrec_z_max;
	float refrec_z_min;
	float auto_diff = 0.007f;



	//�Z���������ꍇ
	//1
	if(*button_flag == AUTO_CIRCLE_BUTTON){
		if(*auto_flag == 1){
			auto_count = 0;
			GetPosCyl();
			//�ڕW�ʒu��ݒ�
			refrec.x = -0.133f;
			refrec.y = 0.183f;
			refrec.z = 0.001f;
			CoordinateSetPosXYZ(*auto_flag);
			auto_diff = 0.025f;
			//������x�̌��݈ʒu�̌덷�͋��e
			refrec_x_max = refrec.x + auto_diff;
			refrec_x_min = refrec.x - auto_diff;
			refrec_y_max = refrec.y + auto_diff;
			refrec_y_min = refrec.y - auto_diff;
			refrec_z_max = refrec.z + auto_diff;
			refrec_z_min = refrec.z - auto_diff;
			//�z��ON�̏�Ԃňړ�����
			BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 2.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
			BrushLessSet();
/*			if(MSW_Z_MIN_FLAG == 0){
				CoordinateSetDuty(0.2f, MD_Z_ID);
			}else{
				CoordinateSetDuty(MOTOR_BRAKE, MD_Z_ID);
			}
*/

			//CoordinateSetDuty(0.2f, MD_Z_ID);
			//���݈ʒu�����e�͈͓��Ȃ玟�̒i�K�Ɉڍs
			if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
				*auto_flag = 2;
			}else{
				*auto_flag = 1;
//				*auto_flag = 100;
				//*button_flag = 1;
/*				if(MicroSwitchIsOn(MICSW_Z_MAX) == MICROSW_OFF){
					CoordinateSetDuty(MOTOR_BRAKE, MD_Z_ID);
					MSW_Z_MIN_FLAG = 1;
				}
*/
			}
		}
		//2
		//if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
			if(*auto_flag == 2 ){
				GetPosCyl();
				refrec.x = -0.133f;
				refrec.y = 0.183f;
				//refrec.z = 0.558f;
				refrec.z = 0.638f;
				refrec_x_max = refrec.x + auto_diff;
				refrec_x_min = refrec.x - auto_diff;
				refrec_y_max = refrec.y + auto_diff;
				refrec_y_min = refrec.y - auto_diff;
				auto_diff = 0.025f;
				refrec_z_max = refrec.z + auto_diff;
				refrec_z_min = refrec.z - auto_diff;
				CoordinateSetPosXYZ(*auto_flag);
				if(MSW_Z_MIN_FLAG == 0){
					//CoordinateSetDuty(-0.2f, MD_Z_ID);
					CoordinateSetPosXYZ(*auto_flag);
				}else{
					CoordinateSetDuty(MOTOR_BRAKE, MD_Z_ID);
				}
				BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 2.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
				BrushLessSet();
				//�}�C�N���X�C�b�`���������܂�Z�����ɂ��낷
				if(MSW_Z_MIN_FLAG == 1){
				//if( /*(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max) || */MSW_Z_MIN_FLAG == 1){
					auto_count++;

					//*auto_flag = 3;
					//�z������������Ԃŏ����҂�
					if(auto_count < 200){
						HAL_Delay(1);
						CoordinateSetPosXYZ(*auto_flag);
						CoordinateSetDuty(MOTOR_BRAKE, MD_Z_ID);
					}else{
						*auto_flag = 3;
					}
					//HAL_Delay(500);
				}else{
					*auto_flag = 2;
					if(MicroSwitchIsOn(MICSW_Z_MIN) == MICROSW_OFF){
						CoordinateSetDuty(MOTOR_BRAKE, MD_Z_ID);
						MSW_Z_MIN_FLAG = 1;
					}
				}
			}


		//3
		//if(posrec.x > -0.136f && posrec.x < -0.13f && posrec.y < 0.188f && posrec.y > 0.178f && posrec.z > 0.553f && posrec.z < 0.563f){
			if(*auto_flag == 3 ){
				GetPosCyl();
				refrec.x = -0.133f;
				refrec.y = 0.183f;
				refrec.z = -0.01f;
				auto_diff = 0.015f;
				refrec_x_max = refrec.x + auto_diff;
				refrec_x_min = refrec.x - auto_diff;
				refrec_y_max = refrec.y + auto_diff;
				refrec_y_min = refrec.y - auto_diff;
				auto_diff = 0.001f;
				refrec_z_max = refrec.z + auto_diff;
				refrec_z_min = refrec.z - auto_diff;
				BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 2.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
				BrushLessSet();
				if(MSW_Z_MAX_FLAG == 0){
					CoordinateSetPosXYZ(*auto_flag);
					//CoordinateSetDuty(0.4f,MD_Z_ID);
				}
				//CoordinateSetDuty(0.5f,MD_Z_ID);
				//CoordinateSetPosXYZ(*auto_flag);


				if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
					*auto_flag = 4;
					//CoordinateSetPosXYZ(*auto_flag);
//					CoordinateSetDuty(0.0f,MD_Z_ID);
				}else if(MSW_Z_MAX_FLAG == 1){
					*auto_flag = 4;
				}else{
					*auto_flag = 3;
					if(MicroSwitchIsOn(MICSW_Z_MAX) == MICROSW_OFF){
						CoordinateSetDuty(0.0f,MD_Z_ID);
						//CoordinateSetPosXYZ(*auto_flag);
						MSW_Z_MAX_FLAG = 1;
					}
				}
			}

		//4
		//if(posrec.x > -0.136f && posrec.x < -0.13f && posrec.y < 0.188f && posrec.y > 0.178f && posrec.z > -0.005f && posrec.z < 0.005f){
			if(*auto_flag == 4 ){


				/*
				GetPosCyl();
				refrec.x = -0.046f;
				refrec.y = -0.010f;
				refrec.z = 0.000f;
				auto_diff = 0.005f;
				refrec_x_max = refrec.x + auto_diff;
				refrec_x_min = refrec.x - auto_diff;
				refrec_y_max = refrec.y + auto_diff;
				refrec_y_min = refrec.y - auto_diff;
				refrec_z_max = refrec.z + auto_diff;
				refrec_z_min = refrec.z - auto_diff;
				CoordinateSetPosXYZ(*auto_flag);
				if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
					*auto_flag = AUTO_RETUEN_FLAG;
					*button_flag = AUTO_RETUEN_FLAG;
					//BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM - 10.0f,650.0f),500.0f);
					//BrushLessSet();
				}else{
					*auto_flag = 4;
					//BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM - 20.5f,650.0f),500.0f);
					//BrushLessSet();
				}
				*/

				refrec.x = -0.046f;
				refrec.y = -0.010f;
				refrec.z = 0.000f;

				CoordinateSetDuty(0.0f, MD_R_ID);
				CoordinateSetDuty(0.0f, MD_THITA_ID);
				/*
				while(poscyl.r > 0.005f && poscyl.r < 0.000f){
					CoordinateSetDuty(-0.3f, MD_R_ID);
				}*/

				//�m���ɖڕW�ʒu�ɍ��킹�邽�߂ɁA�G���R�[�_�[�̒l�ł͂Ȃ��}�C�N���X�C�b�`���g��
				BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 2.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
				BrushLessSet();
				while(MicroSwitchIsOn(MICSW_R_MAX) == MICROSW_ON){
					CoordinateSetDuty(-0.3f, MD_R_ID);
					CoordinateSetDuty(0.0f, MD_THITA_ID);
					BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 2.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
					BrushLessSet();
				}
				CoordinateSetDuty(0.0f, MD_R_ID);
				CoordinateSetDuty(0.0f, MD_THITA_ID);
				while(MicroSwitchIsOn(MICSW_THETA_MAX) == MICROSW_ON){
					CoordinateSetDuty(0.02f, MD_THITA_ID);
					BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 2.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
					BrushLessSet();
				}
				CoordinateSetDuty(0.0f, MD_R_ID);
				CoordinateSetDuty(0.0f, MD_THITA_ID);
				*auto_flag = AUTO_RETUEN_FLAG;
				*button_flag = AUTO_RETUEN_FLAG;


			}

	}


	/*
	//���̏ꍇ
	//2
	if(*button_flag == AUTO_TRIANGLE_BUTTON){
		if(*auto_flag == 1){
			GetPosCyl();
			refrec.x = -0.039f;
			refrec.y = 0.062f;
			refrec.z = 0.001f;
			auto_diff = 0.015f;
			refrec_x_max = refrec.x + auto_diff;
			refrec_x_min = refrec.x - auto_diff;
			refrec_y_max = refrec.y + auto_diff;
			refrec_y_min = refrec.y - auto_diff;
			refrec_z_max = refrec.z + auto_diff;
			refrec_z_min = refrec.z - auto_diff;
			CoordinateSetPosXYZ(*auto_flag);
			if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
				*auto_flag = 2;
			}else{
				*auto_flag = 1;
			}
		}
		//2
		//if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
			if(*auto_flag == 2 ){
				GetPosCyl();
				refrec.x = -0.039f;
				refrec.y = 0.062f;
				refrec.z = 0.558f;
				refrec_x_max = refrec.x + auto_diff;
				refrec_x_min = refrec.x - auto_diff;
				refrec_y_max = refrec.y + auto_diff;
				refrec_y_min = refrec.y - auto_diff;
				auto_diff = 0.025f;
				refrec_z_max = refrec.z + auto_diff;
				refrec_z_min = refrec.z - auto_diff;
				CoordinateSetPosXYZ(*auto_flag);
				if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
					//*auto_flag = 3;


					auto_count++;

					if(auto_count < 50){
						HAL_Delay(1);
						CoordinateSetPosXYZ(*auto_flag);
					}else{
						*auto_flag = 3;
					}
				}else{
					*auto_flag = 2;
				}
			}

		//3
		//if(posrec.x > -0.136f && posrec.x < -0.13f && posrec.y < 0.188f && posrec.y > 0.178f && posrec.z > 0.553f && posrec.z < 0.563f){
			if(*auto_flag == 3 ){
				GetPosCyl();
				refrec.x = -0.039f;
				refrec.y = 0.062f;
				refrec.z = 0.005f;
				auto_diff = 0.015f;
				refrec_x_max = refrec.x + auto_diff;
				refrec_x_min = refrec.x - auto_diff;
				refrec_y_max = refrec.y + auto_diff;
				refrec_y_min = refrec.y - auto_diff;
				refrec_z_max = refrec.z + auto_diff;
				refrec_z_min = refrec.z - auto_diff;
				CoordinateSetPosXYZ(*auto_flag);
//				CoordinateSetDuty(0.5f,MD_Z_ID);

				if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
					*auto_flag = 4;
				}else{
					*auto_flag = 3;

			}

		//4
		//if(posrec.x > -0.136f && posrec.x < -0.13f && posrec.y < 0.188f && posrec.y > 0.178f && posrec.z > -0.005f && posrec.z < 0.005f){
			if(*auto_flag == 4 ){
				GetPosCyl();
				refrec.x = -0.046f;
				refrec.y = -0.010f;
				refrec.z = 0.001f;
				auto_diff = 0.025f;
				refrec_x_max = refrec.x + auto_diff;
				refrec_x_min = refrec.x - auto_diff;
				refrec_y_max = refrec.y + auto_diff;
				refrec_y_min = refrec.y - auto_diff;
				refrec_z_max = refrec.z + auto_diff;
				refrec_z_min = refrec.z - auto_diff;
				CoordinateSetPosXYZ(*auto_flag);
				if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
					*auto_flag = AUTO_RETUEN_FLAG;
					*button_flag = AUTO_RETUEN_FLAG;
				}else{
					*auto_flag = 4;
				}
			}
	}



	//���̏ꍇ
	//3
	if(*button_flag == AUTO_SQUARE_BUTTON){
		if(*auto_flag == 1){
			GetPosCyl();
			refrec.x = -0.080f;
			refrec.y = 0.194f;
			refrec.z = 0.0f;
			refrec_x_max = refrec.x + auto_diff;
			refrec_x_min = refrec.x - auto_diff;
			refrec_y_max = refrec.y + auto_diff;
			refrec_y_min = refrec.y - auto_diff;
			refrec_z_max = refrec.z + auto_diff;
			refrec_z_min = refrec.z - auto_diff;
			CoordinateSetPosXYZ(*auto_flag);
			if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
				*auto_flag = 2;
			}else{
				*auto_flag = 1;
			}
		}
		//2
		//if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
			if(*auto_flag == 2 ){
				GetPosCyl();
				refrec.x = -0.080f;
				refrec.y = 0.194f;
				refrec.z = 0.558f;
				refrec_x_max = refrec.x + auto_diff;
				refrec_x_min = refrec.x - auto_diff;
				refrec_y_max = refrec.y + auto_diff;
				refrec_y_min = refrec.y - auto_diff;
				auto_diff = 0.015f;
				refrec_z_max = refrec.z + auto_diff;
				refrec_z_min = refrec.z - auto_diff;
				CoordinateSetPosXYZ(*auto_flag);
				if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
					*auto_flag = 3;
				}else{
					*auto_flag = 2;
				}
			}

		//3
		//if(posrec.x > -0.136f && posrec.x < -0.13f && posrec.y < 0.188f && posrec.y > 0.178f && posrec.z > 0.553f && posrec.z < 0.563f){
			if(*auto_flag == 3 ){
				GetPosCyl();
				refrec.x = -0.080f;
				refrec.y = 0.194f;
				refrec.z = 0.075f;
				auto_diff = 0.007f;
				refrec_x_max = refrec.x + auto_diff;
				refrec_x_min = refrec.x - auto_diff;
				refrec_y_max = refrec.y + auto_diff;
				refrec_y_min = refrec.y - auto_diff;
				refrec_z_max = refrec.z + auto_diff;
				refrec_z_min = refrec.z - auto_diff;
				CoordinateSetPosXYZ(*auto_flag);
//				CoordinateSetDuty(0.5f,MD_Z_ID);

				if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
					*auto_flag = 4;

				}else{
					*auto_flag = 3;

			}

		//4
		//if(posrec.x > -0.136f && posrec.x < -0.13f && posrec.y < 0.188f && posrec.y > 0.178f && posrec.z > -0.005f && posrec.z < 0.005f){
			if(*auto_flag == 4 ){
				GetPosCyl();
				refrec.x = -0.046f;
				refrec.y = -0.004f;
				refrec.z = 0.075f;
				refrec_x_max = refrec.x + auto_diff;
				refrec_x_min = refrec.x - auto_diff;
				refrec_y_max = refrec.y + auto_diff;
				refrec_y_min = refrec.y - auto_diff;
				refrec_z_max = refrec.z + auto_diff;
				refrec_z_min = refrec.z - auto_diff;
				CoordinateSetPosXYZ(*auto_flag);
				if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
					*auto_flag = 0;
					*button_flag = AUTO_RETUEN_FLAG;
				}else{
					*auto_flag = 4;
				}
			}
		}
		*/
}

//BOX����̂Ƃ��܂ŁAZ�����܂��グ�āA���̂���XY���ړ�����
void Auto_SetPosBOX(uint16_t *auto_BOX_flag){
	float refrec_x_max;
	float refrec_x_min;
	float refrec_y_max;
	float refrec_y_min;
	float refrec_z_max;
	float refrec_z_min;
	float auto_diff = 0.01f;

	//1
	if(*auto_BOX_flag == 1){

		/*
		GetPosCyl();
		refrec.x = posrec.x;
		refrec.y = posrec.y;
		//refrec.z = 0.001f;
		auto_diff = 0.015f;
		refrec_x_max = refrec.x + auto_diff;
		refrec_x_min = refrec.x - auto_diff;
		refrec_y_max = refrec.y + auto_diff;
		refrec_y_min = refrec.y - auto_diff;
		refrec_z_max = refrec.z + auto_diff;
		refrec_z_min = refrec.z - auto_diff;
		CoordinateSetPosXYZ(*auto_BOX_flag);
		if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min ){
			*auto_BOX_flag = 2;
		}else if(MSW_BOX_Z_MAX_FLAG == 1){
			*auto_BOX_flag = 2;
			MSW_BOX_Z_MAX_FLAG = 0;
		}else{
			*auto_BOX_flag = 1;
			if(MicroSwitchIsOn(MICSW_Z_MAX) == MICROSW_OFF){
				//CoordinateSetDuty(0.2f,MD_Z_ID);
				CoordinateSetPosXYZ(*auto_BOX_flag);
				MSW_BOX_Z_MAX_FLAG = 1;
			}

		}*/
		while(MicroSwitchIsOn(MICSW_Z_MAX) == MICROSW_ON){
			CoordinateSetDuty(0.4f, MD_Z_ID);
			//����DUTY�ŏ�Ɉړ�
		}
		*auto_BOX_flag = 2;
		CoordinateSetDuty(0.0f, MD_Z_ID);
	}
	//2
	if(*auto_BOX_flag == 2){
		/*
		GetPosCyl();
		refrec.x = -0.046f;
		refrec.y = -0.010f;
		refrec.z = 0.001f;
		auto_diff = 0.020f;
		refrec_x_max = refrec.x + auto_diff;
		refrec_x_min = refrec.x - auto_diff;
		refrec_y_max = refrec.y + auto_diff;
		refrec_y_min = refrec.y - auto_diff;
		refrec_z_max = refrec.z + auto_diff;
		refrec_z_min = refrec.z - auto_diff;
		CoordinateSetPosXYZ(*auto_BOX_flag);
		if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
			*auto_BOX_flag = AUTO_RETUEN_BOX_FLAG;
		}else{
			*auto_BOX_flag = 2;
		}
		*/

		BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 2.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
		BrushLessSet();
		while(MicroSwitchIsOn(MICSW_R_MAX) == MICROSW_ON){
			CoordinateSetDuty(-0.3f, MD_R_ID);
			CoordinateSetDuty(0.0f, MD_THITA_ID);
			BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 2.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
			BrushLessSet();
		}
		CoordinateSetDuty(0.0f, MD_R_ID);
		CoordinateSetDuty(0.0f, MD_THITA_ID);
		while(MicroSwitchIsOn(MICSW_THETA_MAX) == MICROSW_ON){
			CoordinateSetDuty(0.02f, MD_THITA_ID);
			BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 2.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
			BrushLessSet();
		}
		CoordinateSetDuty(0.0f, MD_R_ID);
		CoordinateSetDuty(0.0f, MD_THITA_ID);
		*auto_BOX_flag = AUTO_RETUEN_BOX_FLAG;


	}
}


//���[�N�̂���ꏊ�܂ŁA�܂�XY�����킹�āA���̂��Ƌz����ON�ɂ���Z��������
void Auto_SetPosWork(uint16_t *auto_work_flag){
		/*
		while(MicroSwitchIsOn(MICSW_Z_MAX) == MICROSW_ON){
			CoordinateSetDuty(0.2f, MD_Z_ID);
			//����DUTY�ŏ�Ɉړ�
		}
		while(poscyl.theta < (float)(0.725f * M_PI)  && poscyl.theta > (float)(0.775f * M_PI) ){
			CoordinateSetDuty(0.02f, MD_THITA_ID);
			refcyl.z = poscyl.z;
			CoordinateSetDuty( ( ( refcyl.z - poscyl.z ) * -25.5f),MD_Z_ID);
			*auto_work_flag = 100;
		}
		CoordinateSetDuty(0.0f, MD_THITA_ID);
		CoordinateSetDuty(0.0f, MD_R_ID);
		while(poscyl.r < (float)(0.20f)  && poscyl.r > (float)(0.23f) ){
			CoordinateSetDuty(0.3f, MD_R_ID);
			refcyl.z = poscyl.z;
			CoordinateSetDuty( ( ( refcyl.z - poscyl.z ) * -25.5f),MD_Z_ID);
			*auto_work_flag = 101;
		}
		CoordinateSetDuty(0.0f, MD_THITA_ID);
		CoordinateSetDuty(0.0f, MD_R_ID);

		while(MicroSwitchIsOn(MICSW_Z_MIN) == MICROSW_ON){
			CoordinateSetDuty(-0.1f, MD_Z_ID);
			*auto_work_flag = 102;
		}
		*auto_work_flag = AUTO_RETUEN_WORK_FLAG;
		MSW_WORK_Z_MIN_FLAG = 0;
		*/


	/*
		//9/14�̒��܎��ɒǉ�
		if(*auto_work_flag == 1){
			//1
			GetPosCyl();
			if(MicroSwitchIsOn(MICSW_Z_MAX) == MICROSW_OFF){
				//CoordinateSetDuty(0.2f,MD_Z_ID);
				CoordinateSetPosXYZ(*auto_work_flag);
				//MSW_WORK_Z_MAX_FLAG = 1;
				*auto_work_flag = 2;
			}else{
				CoordinateSetDuty(0.2f,MD_Z_ID);
				*auto_work_flag = 1;
			}
		}
		if(*auto_work_flag == 2){
			//2
			CoordinateSetDuty(0.02f, MD_THITA_ID);
			refcyl.z = poscyl.z;
			CoordinateSetDuty( ( ( refcyl.z - poscyl.z ) * -25.5f),MD_Z_ID);
			if(poscyl.theta > (float)(0.725f * M_PI)  && poscyl.theta < (float)(0.775f * M_PI) ){
				*auto_work_flag = 3;
				CoordinateSetDuty(0.0f, MD_THITA_ID);
				CoordinateSetDuty(0.0f, MD_R_ID);
			}else{
				*auto_work_flag = 2;
			}
		}
		if(*auto_work_flag == 3){
			//3
			CoordinateSetDuty(0.1f, MD_R_ID);
			refcyl.z = poscyl.z;
			CoordinateSetDuty( ( ( refcyl.z - poscyl.z ) * -25.5f),MD_Z_ID);
			if(poscyl.r > (float)(0.20f)  && poscyl.r < (float)(0.23f) ){
				*auto_work_flag = AUTO_RETUEN_WORK_FLAG;
				CoordinateSetDuty(0.0f, MD_THITA_ID);
				CoordinateSetDuty(0.0f, MD_R_ID);
			}else{
				*auto_work_flag = 3;
			}
		}
		*/




		//�������܂������ł��낤�����Ȃ��
		//Z���̃G���R�[�_���U���ɂ���Ă���n�߂�Ƃ��̊֐��͎g�����ɂȂ�Ȃ��Ȃ�B�C�����ׂ��������Ԃ�����Ȃ�����
		float refrec_x_max;
		float refrec_x_min;
		float refrec_y_max;
		float refrec_y_min;
		float refrec_z_max;
		float refrec_z_min;
		float auto_diff = 0.01f;

		//1
		if(*auto_work_flag == 1){
			GetPosCyl();
			refrec.x = -0.133f;
			refrec.y = 0.183f;
			refrec.z = 0.01f;
			auto_diff = 0.015f;
			refrec_x_max = refrec.x + auto_diff;
			refrec_x_min = refrec.x - auto_diff;
			refrec_y_max = refrec.y + auto_diff;
			refrec_y_min = refrec.y - auto_diff;
			refrec_z_max = refrec.z + auto_diff;
			refrec_z_min = refrec.z - auto_diff;
			CoordinateSetPosXYZ(*auto_work_flag);
			if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
				*auto_work_flag = 2;
			}else if(MSW_WORK_Z_MAX_FLAG == 1){
				*auto_work_flag = 2;
				MSW_WORK_Z_MAX_FLAG = 0;
			}else{

				*auto_work_flag = 1;
				if(MicroSwitchIsOn(MICSW_Z_MAX) == MICROSW_OFF){
					//CoordinateSetDuty(0.2f,MD_Z_ID);
					CoordinateSetPosXYZ(*auto_work_flag);
					MSW_WORK_Z_MAX_FLAG = 1;
				}

			}
		}
		//2
		if(*auto_work_flag == 2){
			GetPosCyl();
			refrec.x = -0.133f;
			refrec.y = 0.183f;
			refrec.z = 0.638f;
			auto_diff = 0.020f;
			refrec_x_max = refrec.x + auto_diff;
			refrec_x_min = refrec.x - auto_diff;
			refrec_y_max = refrec.y + auto_diff;
			refrec_y_min = refrec.y - auto_diff;
			refrec_z_max = refrec.z + auto_diff;
			refrec_z_min = refrec.z - auto_diff;
			CoordinateSetPosXYZ(*auto_work_flag);
	//		BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 2.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
	//		BrushLessSet();
			if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
				*auto_work_flag = AUTO_RETUEN_WORK_FLAG;
			}else if(MSW_WORK_Z_MIN_FLAG == 1){
				*auto_work_flag = AUTO_RETUEN_WORK_FLAG;
				MSW_WORK_Z_MIN_FLAG = 0;
			}else{
				*auto_work_flag = 2;
				if(MicroSwitchIsOn(MICSW_Z_MIN) == MICROSW_OFF){
					CoordinateSetDuty(MOTOR_BRAKE, MD_Z_ID);
					MSW_WORK_Z_MIN_FLAG = 1;
				}

			}
		}
	}





//BOX���Ǝ����i�V���x���j�̎ז��ɂȂ�Ȃ��ꏊ�ɔ��
//���߂̈����Ɏ����ŌĂ΂��
//auto_button_flag��AUTO_ESCAPE_FLAG�������Ďg���܂킷
void Auto_SetEscape(uint16_t *auto_button_flag){
	float refrec_x_max;
	float refrec_x_min;
	float refrec_y_max;
	float refrec_y_min;
	float refrec_z_max;
	float refrec_z_min;
	float auto_diff = 0.01f;

	if(*auto_button_flag == AUTO_ESCAPE_FLAG){
		GetPosCyl();
		refrec.x = 0.014f;
		refrec.y = 0.104f;
		refrec.z = 0.001f;
		auto_diff = 0.005f;
		refrec_x_max = refrec.x + auto_diff;
		refrec_x_min = refrec.x - auto_diff;
		refrec_y_max = refrec.y + auto_diff;
		refrec_y_min = refrec.y - auto_diff;
		refrec_z_max = refrec.z + auto_diff;
		refrec_z_min = refrec.z - auto_diff;
		CoordinateSetPosXYZ(*auto_button_flag);
		if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max){
			*auto_button_flag = 0;

			GetPosCyl();
			refrec.x= posrec.x;
			refrec.y= posrec.y;
			refrec.z= posrec.z;
		}else{
			*auto_button_flag = AUTO_ESCAPE_FLAG;
		}
	}
}

//���{�^�����������ƂŒ��S�ɉ~�����ړ�������BZ�������ă��[�N���������ۂ̔������Ɏg��
void Auto_SetCenter(uint16_t *auto_center_flag){
	float refrec_x_max;
	float refrec_x_min;
	float refrec_y_max;
	float refrec_y_min;
	//float refrec_z_max;
	//float refrec_z_min;
	float auto_diff = 0.01f;

	if(*auto_center_flag == 1){
		GetPosCyl();
		refrec.x = -0.126f;
		refrec.y = 0.154f;
		//refrec.z = 0.001f;
		auto_diff = 0.015f;
		refrec_x_max = refrec.x + auto_diff;
		refrec_x_min = refrec.x - auto_diff;
		refrec_y_max = refrec.y + auto_diff;
		refrec_y_min = refrec.y - auto_diff;
		//refrec_z_max = refrec.z + auto_diff;
		//refrec_z_min = refrec.z - auto_diff;
		CoordinateSetPosXYZ(*auto_center_flag);
		BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 10.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
		BrushLessSet();
		if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min){
			*auto_center_flag = AUTO_CENTER_FLAG;
		}else{
			*auto_center_flag = 0;
		}
	}
}

//�[�ɂ���Ƃ��Ɏ��v����ɉ~���������œ������B�[�ɂ��܂������[�N��������邽�߂̊֐�
void Auto_SetCorner(uint16_t *auto_corner_flag){
	float refrec_x_max;
	float refrec_x_min;
	float refrec_y_max;
	float refrec_y_min;
	float posrec_RU_x;
	float posrec_RU_y;
	float posrec_RD_x;
	float posrec_RD_y;
	float posrec_LD_x;
	float posrec_LD_y;
	float posrec_LU_x;
	float posrec_LU_y;
	float posrec_RU_x_max;
	float posrec_RU_x_min;
	float posrec_RU_y_max;
	float posrec_RU_y_min;
	float posrec_RD_x_max;
	float posrec_RD_x_min;
	float posrec_RD_y_max;
	float posrec_RD_y_min;
	float posrec_LD_x_max;
	float posrec_LD_x_min;
	float posrec_LD_y_max;
	float posrec_LD_y_min;
	float posrec_LU_x_max;
	float posrec_LU_x_min;
	float posrec_LU_y_max;
	float posrec_LU_y_min;

	//float refrec_z_max;
	//float refrec_z_min;
	float auto_diff = 0.01f;
	float auto_X_diff = 0.01f;
	float auto_Y_diff = 0.01f;

	posrec_RU_x = 0.003f;
	posrec_RU_y = 0.233f;
	posrec_RD_x = 0.0f;
	posrec_RD_y = 0.0f;
	posrec_LD_x = -0.414f;
	posrec_LD_y = 0.142f;
	posrec_LU_x = -0.345f;
	posrec_LU_y = 0.342f;

	auto_X_diff = 0.03f;
	auto_Y_diff = 0.2f;
	posrec_RU_x_max = posrec_RU_x + auto_X_diff;
	posrec_RU_x_min = posrec_RU_x - auto_X_diff;
	posrec_RU_y_max = posrec_RU_y + auto_Y_diff;
	posrec_RU_y_min = posrec_RU_y - auto_Y_diff;

	auto_X_diff = 0.35f;
	auto_Y_diff = 0.03f;
	posrec_RD_x_max = posrec_RD_x + auto_X_diff;
	posrec_RD_x_min = posrec_RD_x - auto_X_diff;
	posrec_RD_y_max = posrec_RD_y + auto_Y_diff;
	posrec_RD_y_min = posrec_RD_y - auto_Y_diff;

	auto_X_diff = 0.03f;
	auto_Y_diff = 0.15f;
	posrec_LD_x_max = posrec_LD_x + auto_X_diff;
	posrec_LD_x_min = posrec_LD_x - auto_X_diff;
	posrec_LD_y_max = posrec_LD_y + auto_Y_diff;
	posrec_LD_y_min = posrec_LD_y - auto_Y_diff;

	auto_X_diff = 0.35f;
	auto_Y_diff = 0.07f;
	posrec_LU_x_max = posrec_LU_x + auto_X_diff;
	posrec_LU_x_min = posrec_LU_x - auto_X_diff;
	posrec_LU_y_max = posrec_LU_y + auto_Y_diff;
	posrec_LU_y_min = posrec_LU_y - auto_Y_diff;


	if(*auto_corner_flag == 1){
		GetPosCyl();
		//refrec.z = 0.001f;
		auto_diff = 0.010f;

		//���ݍ��W���E�Ȃ�E�ォ��E���ɓ�����
		if(posrec.x > posrec_RU_x_min && posrec.x < posrec_RU_x_max && posrec.y < posrec_RU_y_max && posrec.y > posrec_RU_y_min){

			//�ڕW���W�͉E��
			refrec.x = 0.0f;
			refrec.y = 0.0f;
			//refrec.z = 0.001f;
			auto_diff = 0.015f;
			refrec_x_max = refrec.x + auto_diff;
			refrec_x_min = refrec.x - auto_diff;
			refrec_y_max = refrec.y + auto_diff;
			refrec_y_min = refrec.y - auto_diff;
			//refrec_z_max = refrec.z + auto_diff;
			//refrec_z_min = refrec.z - auto_diff;
			CoordinateSetPosXYZ(*auto_corner_flag);
			if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min){
				*auto_corner_flag = AUTO_CORNER_FLAG;
			}else{
				*auto_corner_flag = 0;
			}


		}

		//���ݍ��W�����Ȃ�E�����獶���ɓ�����
		if(posrec.x > posrec_RD_x_min && posrec.x < posrec_RD_x_max && posrec.y < posrec_RD_y_max && posrec.y > posrec_RD_y_min){

			//�ڕW���W�͍���
			refrec.x = -0.414f;
			refrec.y = 0.142f;
			//refrec.z = 0.001f;
			auto_diff = 0.015f;
			refrec_x_max = refrec.x + auto_diff;
			refrec_x_min = refrec.x - auto_diff;
			refrec_y_max = refrec.y + auto_diff;
			refrec_y_min = refrec.y - auto_diff;
			//refrec_z_max = refrec.z + auto_diff;
			//refrec_z_min = refrec.z - auto_diff;
			CoordinateSetPosXYZ(*auto_corner_flag);

			if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min){
				*auto_corner_flag = AUTO_CORNER_FLAG;
			}else{
				*auto_corner_flag = 0;
			}


		}

		//���ݍ��W�����Ȃ獶�����獶��ɓ�����
		if(posrec.x > posrec_LD_x_min && posrec.x < posrec_LD_x_max && posrec.y < posrec_LD_y_max && posrec.y > posrec_LD_y_min){

			//�ڕW���W�͍���
			refrec.x = -0.345f;
			refrec.y = 0.342f;
			//refrec.z = 0.001f;
			auto_diff = 0.015f;
			refrec_x_max = refrec.x + auto_diff;
			refrec_x_min = refrec.x - auto_diff;
			refrec_y_max = refrec.y + auto_diff;
			refrec_y_min = refrec.y - auto_diff;
			//refrec_z_max = refrec.z + auto_diff;
			//refrec_z_min = refrec.z - auto_diff;
			CoordinateSetPosXYZ(*auto_corner_flag);

			if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min){
				*auto_corner_flag = AUTO_CORNER_FLAG;
			}else{
				*auto_corner_flag = 0;
			}


		}

		//���ݍ��W����Ȃ獶�ォ��E��ɓ�����
		if(posrec.x > posrec_LU_x_min && posrec.x < posrec_LU_x_max && posrec.y < posrec_LU_y_max && posrec.y > posrec_LU_y_min){

			//�ڕW���W�͉E��
			refrec.x = 0.003f;
			refrec.y = 0.233f;
			//refrec.z = 0.001f;
			auto_diff = 0.015f;
			refrec_x_max = refrec.x + auto_diff;
			refrec_x_min = refrec.x - auto_diff;
			refrec_y_max = refrec.y + auto_diff;
			refrec_y_min = refrec.y - auto_diff;
			//refrec_z_max = refrec.z + auto_diff;
			//refrec_z_min = refrec.z - auto_diff;
			CoordinateSetPosXYZ(*auto_corner_flag);

			if(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min){
				*auto_corner_flag = AUTO_CORNER_FLAG;
			}else{
				*auto_corner_flag = 0;
			}

		}
	}
}
