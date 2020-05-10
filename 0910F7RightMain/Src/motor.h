/*
 * motor.h
 *
 *  Created on: 2019/09/09
 *      Author: tomok
 */

//#include "math.h"
#include "stm32f7xx_hal.h"
#include "coreless.h"
//#include "struct.h"



/*-----------------------------------------------
 * 座標軸DCモータ(r, theta, z)
-----------------------------------------------*/
void CoordinateSetDuty(float duty,int MD_ID);
void CoordinateEnable(void);
void CoordinateDisable(void);
void CoordinateSetDirection(float duty,int MD_ID);
void CoordinateSetPosRTZ(void);
void CoordinateSetPosPID(void);
void CoordinateSetPosXYZ(uint16_t auto_flag);

//座標軸DCモータタイマハンドラ
#define MD_R_TIM_HANDLER		htim1	//1
#define MD_THITA_TIM_HANDLER		htim1	//2
#define MD_Z_TIM_HANDLER		htim1	//3

#define MD_BOX2_TIM_HANDLER		htim8	//7

//#define MD_BOX1_TIM_HANDLER		htim8	//8

//#define MD_BOX1_TIM_HANDLER		htim1	//4

//#define MD_Z_TIM_HANDLER		htim1	//2


//#define MD_BOX1_TIM_HANDLER		htim8	//6

#define MD_BOX1_TIM_HANDLER		htim8	//5

//PWMのARR値（MAXの値）
#define PWM_ARR 			10000.0f
//モータPWMチャンネル
#define MD_R_PWM_TIM_CH				TIM_CHANNEL_1
#define MD_THITA_PWM_TIM_CH				TIM_CHANNEL_2
#define MD_Z_PWM_TIM_CH				TIM_CHANNEL_3

#define MD_BOX2_PWM_TIM_CH				TIM_CHANNEL_3	//7

//#define MD_BOX1_PWM_TIM_CH				TIM_CHANNEL_4	//8

//#define MD_Z_PWM_TIM_CH				TIM_CHANNEL_2	//2


//#define MD_BOX1_PWM_TIM_CH				TIM_CHANNEL_4	//4

//#define MD_BOX1_PWM_TIM_CH				TIM_CHANNEL_2		//6

#define MD_BOX1_PWM_TIM_CH				TIM_CHANNEL_1		//5

//DCモータ回転方向GPIO
#define MD_R_1_PORT				GPIOD		//1
#define MD_R_1_PIN				GPIO_PIN_14
#define MD_R_2_PORT				GPIOD
#define MD_R_2_PIN				GPIO_PIN_15


#define MD_THITA_1_PORT				GPIOF		//2
#define MD_THITA_1_PIN				GPIO_PIN_15
#define MD_THITA_2_PORT				GPIOF
#define MD_THITA_2_PIN				GPIO_PIN_3


#define MD_Z_1_PORT				GPIOE		//3
#define MD_Z_1_PIN				GPIO_PIN_15
#define MD_Z_2_PORT				GPIOF
#define MD_Z_2_PIN				GPIO_PIN_14


#define MD_BOX2_1_PORT				GPIOB		//7
#define MD_BOX2_1_PIN				GPIO_PIN_12
#define MD_BOX2_2_PORT				GPIOB
#define MD_BOX2_2_PIN				GPIO_PIN_11


/*
#define MD_BOX1_1_PORT				GPIOB		//8
#define MD_BOX1_1_PIN				GPIO_PIN_8
#define MD_BOX1_2_PORT				GPIOB
#define MD_BOX1_2_PIN				GPIO_PIN_9
*/

/*
#define MD_Z_1_PORT				GPIOF		//2
#define MD_Z_1_PIN				GPIO_PIN_15
#define MD_Z_2_PORT				GPIOF
#define MD_Z_2_PIN				GPIO_PIN_3
*/

/*
#define MD_BOX1_1_PORT				GPIOE		//4
#define MD_BOX1_1_PIN				GPIO_PIN_10
#define MD_BOX1_2_PORT				GPIOE
#define MD_BOX1_2_PIN				GPIO_PIN_12
*/

/*
#define MD_BOX1_1_PORT				GPIOB		//6
#define MD_BOX1_1_PIN				GPIO_PIN_6
#define MD_BOX1_2_PORT				GPIOA
#define MD_BOX1_2_PIN				GPIO_PIN_8
*/

#define MD_BOX1_1_PORT				GPIOA		//5
#define MD_BOX1_1_PIN				GPIO_PIN_12
#define MD_BOX1_2_PORT				GPIOA
#define MD_BOX1_2_PIN				GPIO_PIN_11


//モタドラのID
#define MD_R_ID		1		//奥側のコンベア
#define MD_THITA_ID		2		//手前側のコンベア
#define MD_Z_ID		3		//プッシャー
#define MD_BOX1_ID		4		//BOX取り右
#define MD_BOX2_ID		5		//BOX取り左

//モータブレーキ
#define MOTOR_BRAKE					0.0f

