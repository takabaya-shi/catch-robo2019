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

//円筒の一個取り自動化を行う関数
//基本的にXYZ座標をCoordinateSetPosXYZで実現して、実際にその位置になったら次の段階に移行するようにしている
//auto_flagは0なら手動でそれ以外なら自動であることを表す。自動の間でもauto_flagに0を代入することで手動にすぐに切り替わる
void Auto_Set(uint16_t *auto_flag,uint16_t *button_flag){
	float refrec_x_max;
	float refrec_x_min;
	float refrec_y_max;
	float refrec_y_min;
	float refrec_z_max;
	float refrec_z_min;
	float auto_diff = 0.007f;



	//〇を押した場合
	//1
	if(*button_flag == AUTO_CIRCLE_BUTTON){
		if(*auto_flag == 1){
			auto_count = 0;
			GetPosCyl();
			//目標位置を設定
			refrec.x = -0.133f;
			refrec.y = 0.183f;
			refrec.z = 0.001f;
			CoordinateSetPosXYZ(*auto_flag);
			auto_diff = 0.025f;
			//ある程度の現在位置の誤差は許容
			refrec_x_max = refrec.x + auto_diff;
			refrec_x_min = refrec.x - auto_diff;
			refrec_y_max = refrec.y + auto_diff;
			refrec_y_min = refrec.y - auto_diff;
			refrec_z_max = refrec.z + auto_diff;
			refrec_z_min = refrec.z - auto_diff;
			//吸引ONの状態で移動する
			BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 2.0f,BRUSHLESS_MAX),BRUSHLESS_MIN);
			BrushLessSet();
/*			if(MSW_Z_MIN_FLAG == 0){
				CoordinateSetDuty(0.2f, MD_Z_ID);
			}else{
				CoordinateSetDuty(MOTOR_BRAKE, MD_Z_ID);
			}
*/

			//CoordinateSetDuty(0.2f, MD_Z_ID);
			//現在位置が許容範囲内なら次の段階に移行
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
				//マイクロスイッチが押されるまでZを下におろす
				if(MSW_Z_MIN_FLAG == 1){
				//if( /*(posrec.x > refrec_x_min && posrec.x < refrec_x_max && posrec.y < refrec_y_max && posrec.y > refrec_y_min && posrec.z > refrec_z_min && posrec.z < refrec_z_max) || */MSW_Z_MIN_FLAG == 1){
					auto_count++;

					//*auto_flag = 3;
					//吸引を下した状態で少し待つ
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

				//確実に目標位置に合わせるために、エンコーダーの値ではなくマイクロスイッチを使う
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
	//△の場合
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



	//□の場合
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

//BOX送りのとこまで、Z軸をまず上げて、そのあとXYを移動する
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
			//正のDUTYで上に移動
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


//ワークのある場所まで、まずXYを合わせて、そのあと吸引をONにしてZ軸を下す
void Auto_SetPosWork(uint16_t *auto_work_flag){
		/*
		while(MicroSwitchIsOn(MICSW_Z_MAX) == MICROSW_ON){
			CoordinateSetDuty(0.2f, MD_Z_ID);
			//正のDUTYで上に移動
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
		//9/14の朝五時に追加
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




		//多分うまくいくであろう微妙なやつ
		//Z軸のエンコーダが振動によってずれ始めるとこの関数は使い物にならなくなる。修正すべきだが時間が足りなかった
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





//BOX取りと自動（ショベル）の邪魔にならない場所に避難
//初めの一個取り後に自動で呼ばれる
//auto_button_flagにAUTO_ESCAPE_FLAGを代入して使いまわす
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

//△ボタンを押すことで中心に円筒を移動させる。Zをあげてワークを回収する際の微調整に使う
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

//端にいるときに時計周りに円筒を自動で動かす。端にたまったワークを回収するための関数
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

		//現在座標が右なら右上から右下に動かす
		if(posrec.x > posrec_RU_x_min && posrec.x < posrec_RU_x_max && posrec.y < posrec_RU_y_max && posrec.y > posrec_RU_y_min){

			//目標座標は右下
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

		//現在座標が下なら右下から左下に動かす
		if(posrec.x > posrec_RD_x_min && posrec.x < posrec_RD_x_max && posrec.y < posrec_RD_y_max && posrec.y > posrec_RD_y_min){

			//目標座標は左下
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

		//現在座標が左なら左下から左上に動かす
		if(posrec.x > posrec_LD_x_min && posrec.x < posrec_LD_x_max && posrec.y < posrec_LD_y_max && posrec.y > posrec_LD_y_min){

			//目標座標は左上
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

		//現在座標が上なら左上から右上に動かす
		if(posrec.x > posrec_LU_x_min && posrec.x < posrec_LU_x_max && posrec.y < posrec_LU_y_max && posrec.y > posrec_LU_y_min){

			//目標座標は右上
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
