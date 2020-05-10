/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include "motor.h"
#include "microswitch.h"
#include "controller.h"
#include "encoder.h"
#include "robotstate.h"
#include "autoctrl.h"
#include "servomotor.h"
#include "coreless.h"
#include "auto_pass.h"
#include "brushless.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

ETH_HandleTypeDef heth;

SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim9;
TIM_HandleTypeDef htim10;
TIM_HandleTypeDef htim11;
TIM_HandleTypeDef htim13;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
uint16_t flag = 0;
static char s[255] = {'\0'};
float SERVO1_angle = SERVO1_ZERO_ANGLE;		//ボックス右
float SERVO2_angle = SERVO2_ZERO_ANGLE;		//ボックス真ん中
float SERVO3_angle = SERVO3_ZERO_ANGLE;		//ボックス左
float SERVO4_angle = SERVO4_ZERO_ANGLE;		//一個取り

int PREV_SERVO1_angle = SERVO1_ZERO_ANGLE;
int PREV_SERVO2_angle = SERVO2_ZERO_ANGLE;
int PREV_SERVO3_angle = SERVO3_ZERO_ANGLE;

float current_pos = 0;
int L1_flag = 0;
int L2_flag = 0;
int R1_flag = 0;
int R2_flag = 0;
int R3_flag = 0;
uint16_t prev_button_data = 0;
uint16_t MODE2_flag = 0;
float refrec_x_max;
float refrec_x_min;
float refrec_y_max;
float refrec_y_min;
float refrec_z_max;
float refrec_z_min;
float auto_diff = 0.007f;
uint16_t auto_flag = 1;
uint16_t auto_button_flag = 0;
int auto_return_count = 0;
uint16_t auto_BOX_flag = 0;
uint16_t auto_WORK_flag = 0;
uint16_t auto_escape_flag = 0;
uint16_t auto_center_flag = 0;
uint16_t auto_corner_flag = 0;
float BOX_vero = 0.0f;

int NF_y_button = 0;
int NF_x_button = 0;
int NF_z_button = 0;

static uint16_t button_data = 0;
analog_stick_norm analog_left_norm, analog_right_norm;
analog_stick_polar analog_left_polar, analog_right_polar;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ETH_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM6_Init(void);
static void MX_TIM8_Init(void);
static void MX_TIM9_Init(void);
static void MX_TIM10_Init(void);
static void MX_TIM11_Init(void);
static void MX_TIM13_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	//TIM6割り込み
	if (htim->Instance == TIM6) {
		//SPI communication with DUALSHOCK2

		//読み込み
		PSControllerGetData(&button_data, &analog_left_norm, &analog_right_norm, &analog_left_polar, &analog_right_polar);
		flag = filter(button_data, analog_left_norm, analog_right_norm, analog_left_polar, analog_right_polar);


		if(flag == 1){
			if(button_data == CONTROLLER_CIRCLE){
				//auto_pos = 1
				//円筒を自動で一個取りする

				auto_button_flag = 1;
//				AutoSet(auto_flag,auto_button_flag);
			}else if(button_data == CONTROLLER_TRIANGLE){
				//auto_pos = 1
				//中央に自動で移動する

				auto_center_flag = 1;
//				AutoSet(auto_flag,auto_button_flag);
			}else if(button_data == CONTROLLER_LEFT){
				//auto_pos = 1
				//端を時計回りに自動で移動する

				auto_corner_flag = 1;
//				AutoSet(auto_flag,auto_button_flag);
			}else if(button_data == CONTROLLER_L1){
				//BOX取りのサーボをあげる


				SERVO1_angle = fmaxf((SERVO1_angle - 0.5f), SERVO1_MIN_ANGLE);
				SERVO2_angle = fmaxf((SERVO2_angle - 0.5f), SERVO2_MIN_ANGLE);
				SERVO3_angle = fmaxf((SERVO3_angle - 0.5f), SERVO3_MIN_ANGLE);
			}else if(button_data == CONTROLLER_L2){
				//BOX取りのサーボをさげる
				//正が下げる向き

				//SERVO1_angle = fminf((SERVO1_angle + 1), SERVO1_MAX_ANGLE);
				SERVO2_angle = fminf((SERVO2_angle + 0.5f), SERVO2_MAX_ANGLE);
				SERVO3_angle = fminf((SERVO3_angle + 0.5f), SERVO3_MAX_ANGLE);
			}else if(button_data == CONTROLLER_R1){
				//円筒の吸引ONOFF
				if(prev_button_data != button_data){
					if(R1_flag == 0){
						//吸引ON

						R1_flag = 1;
					}else if(R1_flag == 1){
						//吸引OFF

						R1_flag = 0;
					}
				}

			}else if(button_data == CONTROLLER_SQUARE){
				//BOX取りの吸引左ONOFF
				if(prev_button_data != button_data){
					if(R2_flag == 0){
						//吸引ON

						//HAL_GPIO_WritePin(CORELESS1_PORT, CORELESS1_PIN, GPIO_PIN_SET);
						//HAL_GPIO_WritePin(CORELESS2_PORT, CORELESS2_PIN, GPIO_PIN_SET);
						//HAL_GPIO_WritePin(CORELESS3_PORT, CORELESS3_PIN, GPIO_PIN_SET);
						HAL_GPIO_WritePin(CORELESS4_PORT, CORELESS4_PIN, GPIO_PIN_SET);
						HAL_GPIO_WritePin(CORELESS5_PORT, CORELESS5_PIN, GPIO_PIN_SET);
						HAL_GPIO_WritePin(CORELESS6_PORT, CORELESS6_PIN, GPIO_PIN_SET);
						R2_flag = 1;
					}else if(R2_flag == 1){
						//吸引OFF

						//HAL_GPIO_WritePin(CORELESS1_PORT, CORELESS1_PIN, GPIO_PIN_RESET);
						//HAL_GPIO_WritePin(CORELESS2_PORT, CORELESS2_PIN, GPIO_PIN_RESET);
						//HAL_GPIO_WritePin(CORELESS3_PORT, CORELESS3_PIN, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(CORELESS4_PORT, CORELESS4_PIN, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(CORELESS5_PORT, CORELESS5_PIN, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(CORELESS6_PORT, CORELESS6_PIN, GPIO_PIN_RESET);
						R2_flag = 0;
					}
				}
			}else if(button_data == CONTROLLER_CROSS){
				//BOX取りの吸引左ONOFF
				if(prev_button_data != button_data){
					if(R3_flag == 0){
						//吸引ON

						HAL_GPIO_WritePin(CORELESS1_PORT, CORELESS1_PIN, GPIO_PIN_SET);
						HAL_GPIO_WritePin(CORELESS2_PORT, CORELESS2_PIN, GPIO_PIN_SET);
						HAL_GPIO_WritePin(CORELESS3_PORT, CORELESS3_PIN, GPIO_PIN_SET);
						//HAL_GPIO_WritePin(CORELESS4_PORT, CORELESS4_PIN, GPIO_PIN_SET);
						//HAL_GPIO_WritePin(CORELESS5_PORT, CORELESS5_PIN, GPIO_PIN_SET);
						//HAL_GPIO_WritePin(CORELESS6_PORT, CORELESS6_PIN, GPIO_PIN_SET);
						R3_flag = 1;
					}else if(R3_flag == 1){
						//吸引OFF

						HAL_GPIO_WritePin(CORELESS1_PORT, CORELESS1_PIN, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(CORELESS2_PORT, CORELESS2_PIN, GPIO_PIN_RESET);
						HAL_GPIO_WritePin(CORELESS3_PORT, CORELESS3_PIN, GPIO_PIN_RESET);
						//HAL_GPIO_WritePin(CORELESS4_PORT, CORELESS4_PIN, GPIO_PIN_RESET);
						//HAL_GPIO_WritePin(CORELESS5_PORT, CORELESS5_PIN, GPIO_PIN_RESET);
						//HAL_GPIO_WritePin(CORELESS6_PORT, CORELESS6_PIN, GPIO_PIN_RESET);
						R3_flag = 0;
					}
				}
			}else if(button_data == CONTROLLER_UP){
				//ボックス取りを前進.台形加減速
				//CoordinateSetDuty(-0.585f,MD_BOX1_ID);
				//CoordinateSetDuty(-0.5f,MD_BOX2_ID);
				BOX_vero = fmaxf(fminf(BOX_vero + 0.0005f,0.05f),-0.05f);
				CoordinateSetDuty(( -1.0f ) * BOX_vero,MD_BOX1_ID);
				CoordinateSetDuty(BOX_vero,MD_BOX2_ID);
			}else if(button_data == CONTROLLER_DOWN){
				//ボックス取りを後進.台形加減速
				BOX_vero = fmaxf(fminf(BOX_vero - 0.0005f,0.05f),-0.05f);
				CoordinateSetDuty(( -1.0f ) * BOX_vero,MD_BOX1_ID);
				CoordinateSetDuty(BOX_vero,MD_BOX2_ID);
			}else if(button_data == CONTROLLER_RIGHT){
				//決まった位置にサーボを爆速で動かす

				SERVO1_angle = fmaxf(SERVO1_BOX_ANGLE, SERVO1_MIN_ANGLE);
				SERVO2_angle = fmaxf(SERVO2_BOX_ANGLE, SERVO2_MIN_ANGLE);
				SERVO3_angle = fmaxf(SERVO3_BOX_ANGLE, SERVO3_MIN_ANGLE);
		    	ServoSetAngle(SERVO1_angle,SERVO1_ID);
		    	ServoSetAngle(SERVO2_angle,SERVO2_ID);
		    	ServoSetAngle(SERVO3_angle,SERVO3_ID);
			}else if(button_data == CONTROLLER_START){
				//下の方からボックス送りのとこまで自動で動かす

				if(prev_button_data != button_data){
					auto_BOX_flag = 1;
				}
			}else if(button_data == CONTROLLER_SELECT){
				//ボックス送りから底辺の中央まで、まずXYを合わせて、そのあと吸引をONにしてZ軸を下す

				if(prev_button_data != button_data){
					auto_WORK_flag = 1;
				}
			}else if(button_data == (CONTROLLER_L1 + CONTROLLER_L2 + CONTROLLER_R1 + CONTROLLER_R2)){
				//手動と自動を切り替え
				//手動の途中で動かなくなった場合はこれで手動操作する

				auto_flag = 0;
				auto_BOX_flag = 0;
				auto_WORK_flag = 0;
				auto_button_flag = 0;
			}else{
				if(BOX_vero > 0.0f){
					BOX_vero = BOX_vero - 0.0005f;
				}else if(BOX_vero < 0.0f){
					BOX_vero = BOX_vero + 0.0005f;
				}else{
					BOX_vero = MOTOR_BRAKE;
				}
				CoordinateSetDuty(( -1.0f ) * BOX_vero,MD_BOX1_ID);
				CoordinateSetDuty(BOX_vero,MD_BOX2_ID);
			}
			//BOX取りをP制御（不要）？
			//CoordinateSetPosBOX();

			//ブラシレスを段階的に制御
			//自動の処理をする間は    flag != 0 となる。帰ってくると 0 なる。
			if(R1_flag == 1 && auto_flag == 0 && auto_BOX_flag == 0 && auto_WORK_flag == 0){
				BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM + 1.5f,BRUSHLESS_MAX),BRUSHLESS_MIN);
				BrushLessSet();
			}else if(R1_flag == 0 && auto_flag == 0 && auto_BOX_flag == 0 && auto_WORK_flag == 0){
				BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM - 1.5f,BRUSHLESS_MAX),BRUSHLESS_MIN);
				BrushLessSet();
			}

    	prev_button_data = button_data;

    	ServoSetAngle(SERVO1_angle,SERVO1_ID);
    	ServoSetAngle(SERVO2_angle,SERVO2_ID);
    	ServoSetAngle(SERVO3_angle,SERVO3_ID);

			/*-----------------------------------------------
			 * 円筒座標系モータ
			-----------------------------------------------*/
			//現在座標を更新
			GetPosCyl();

			//NF用に追加。ボタンで円筒操作
			if(button_data == CONTROLLER_UP){
							//ボックス取りを前進.台形加減速
				NF_y_button = 1;
			}else if(button_data == CONTROLLER_DOWN){
				NF_y_button = -1;
			}else if(button_data == CONTROLLER_RIGHT){
				NF_x_button = 1;
			}else if(button_data == CONTROLLER_LEFT){
				NF_x_button = -1;
			}else if(button_data == CONTROLLER_TRIANGLE){
				NF_z_button = 1;
			}else if(button_data == CONTROLLER_CROSS){
				NF_z_button = -1;
			}else{
				NF_x_button = 0;
				NF_y_button = 0;
				NF_z_button = 0;
			}


			//自動で円筒が一個取りした後にコントローラから円筒を動かす
			//自動が完了もしくは切り替えでauto_flag = 0になる
			if(auto_flag == 0){
				GetPosCyl();
				//コントローラの入力により目標直交座標を更新

/*
				refrec.x = posrec.x + (NF_x_button)  * 0.0015;
				refrec.y = posrec.y + NF_y_button     * 0.0015;
				refrec.z = posrec.z + NF_z_button    * 0.0015;
*/

				refrec.x = posrec.x + (-analog_left_norm.x)  * 0.0015;
				refrec.y = posrec.y + analog_left_norm.y     * 0.0015;
				refrec.z = posrec.z + analog_right_norm.y    * 0.0015;

				CoordinateSetPosXYZ(auto_flag);
			}
		}

		  //sprintf(s,"SERVO1: %d SERVO2: %d SERVO3: %d  \r\n",SERVO1_angle,SERVO2_angle,SERVO3_angle);

		//GetPosCyl();
		//refrec.x = posrec.x + (analog_right_norm.x)  * 0.0035;
		//refrec.y = posrec.y + analog_right_norm.y     * 0.0035;
		//CoordinateSetPosXYZ(auto_flag);
		//sprintf(s,"posrec.x %d posrec.y %d poscyl.r: %d poscyl.theta: %d refcyl.theta: %d poscyl.z %d refcyl.z: %d auto_WORK_flag: %d \r\n",(int)(posrec.x*1000.0f),(int)(posrec.y*1000.0f),(int)(poscyl.r*1000.0f),(int)(poscyl.theta*1000.0f/M_PI),(int)(refcyl.theta*1000.0f/M_PI),(int)(poscyl.z*1000.0f),(int)(refcyl.z*1000.0f),(int)auto_WORK_flag);
		//HAL_UART_Transmit(&huart3,(uint8_t *)s, strlen(s), 100);

	}

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ETH_Init();
  MX_SPI3_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM6_Init();
  MX_TIM8_Init();
  MX_TIM9_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM13_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  //円筒モータENABLE
  CoordinateEnable();

  //座標を原点に設定
  ResetPos();

  //エンコーダENABLE
  EncEnable();

  //ブラシレスENABLE
  BrushLessEnable();

  //サーボENABLE
  ServoEnable();

  //少し待ち
  HAL_Delay(300);

  //制御割り込み開始
  HAL_TIM_Base_Start_IT(&htim6);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  	//sprintf(s, "button_data: %d left_norm.x: %d left_norm.y: %d analog_right_norm.y: %d \r\n", (int)button_data,(int)(analog_left_norm.x*100.0),(int)(analog_left_norm.y*100.0),(int)(analog_right_norm.y*100.0));
  	//HAL_UART_Transmit(&huart3,(uint8_t *)s, strlen(s), 100);
  	sprintf(s, "posrec.x: %d posrec.y: %d poscyl.r %d poscyl.theta: %d poscyl.z %d refrec.x %d refrec.y: %d refcyl.r: %d refcyl.theta: %d refcyl.z: %d \r\n" , (int)(posrec.x*1000.0f),(int)(posrec.y*1000.0f),(int)(poscyl.r*1000.0f),(int)(poscyl.theta*1000.0f/M_PI),(int)(poscyl.z*1000.0f),(int)(refrec.x*1000.0f),(int)(refrec.y*1000.0f),(int)(refcyl.r*1000.0f),(int)(refcyl.theta*1000.0f/M_PI),(int)(refcyl.z*1000.0f));
	  //sprintf(s, "posrec.x: %d posrec.y: %d poscyl.r %d poscyl.theta: %d poscyl.z %d refrec.x %d refrec.y: %d refcyl.r: %d refcyl.theta: %d refcyl.z: %d auto_flag: %d SW: %d %d %d %d %d %d auto_flag: %d auto_button_flag: %d BRUSHLESS_PWM: %d auto_BOX_flag: %d auto_WORK_flag: %d \r\n", (int)(posrec.x*1000.0f),(int)(posrec.y*1000.0f),(int)(poscyl.r*1000.0f),(int)(poscyl.theta*1000.0f/M_PI),(int)(poscyl.z*1000.0f),(int)(refrec.x*1000.0f),(int)(refrec.y*1000.0f),(int)(refcyl.r*1000.0f),(int)(refcyl.theta*1000.0f/M_PI),(int)(refcyl.z*1000.0f),auto_flag,MicroSwitchIsOn(MICSW_R_MAX),MicroSwitchIsOn(MICSW_THETA_MAX),MicroSwitchIsOn(MICSW_Z_MAX),MicroSwitchIsOn(MICSW_BOX_MAX),MicroSwitchIsOn(MICSW_BOX_MIN),MicroSwitchIsOn(MICSW_Z_MIN),auto_flag,auto_button_flag,(int)(BRUSHLESS_PWM * 10.0f),auto_BOX_flag,auto_WORK_flag);
	  //sprintf(s,"SERVO1: %d SERVO2: %d SERVO3: %d  \r\n",SERVO1_angle,SERVO2_angle,SERVO3_angle);

	    HAL_UART_Transmit(&huart3,(uint8_t *)s, strlen(s), 100);

	    if(auto_flag == 0){
			GetPosCyl();

			refrec.x = posrec.x;
			refrec.y = posrec.y;
			refrec.z = posrec.z;

			//CoordinateSetPosXYZ(auto_flag);
	    }

		//自動で円筒で一個取りする
		//自動で動いた後に、auto_flag = 0を代入するようになっている
		//auto_button_flagでボタンによって特定の場所を変更する
		if(auto_flag != 0){
			//auto_button_flag = 1;
			Auto_Set(&auto_flag,&auto_button_flag);
		}

		//自動から帰って来た時に吸引保持のため
		if(auto_button_flag == AUTO_RETUEN_FLAG){
			for(int i=0;i<1000;i++){
				BRUSHLESS_PWM  = fmaxf(fminf(BRUSHLESS_PWM - 2.5f,650.0f),500.0f);
				BrushLessSet();
				HAL_Delay(1);
				auto_flag = 1;
				CoordinateSetPosXYZ(auto_flag);
				CoordinateSetDuty(0.0f,MD_THITA_ID);
				CoordinateSetDuty(0.0f,MD_R_ID);
			}
			auto_flag = 0;
			auto_button_flag = AUTO_ESCAPE_FLAG;
		}

		//初めの自動（一個取り）の後に、BOX取りと自動（ショベル）の邪魔にならない場所に避難
		if(auto_button_flag == AUTO_ESCAPE_FLAG ){
			Auto_SetEscape(&auto_button_flag);
			//auto_escape_flag = 1;
		}


		//BOX送りのとこまで、Z軸をまず上げて、そのあとXYを移動する
		if(auto_BOX_flag != 0){
			Auto_SetPosBOX(&auto_BOX_flag);
			if(auto_BOX_flag == AUTO_RETUEN_BOX_FLAG){
				auto_BOX_flag = 0;
				auto_button_flag = 0;
			}
		}

		//ワークのある場所まで、まずXYを合わせて、そのあと吸引をONにしてZ軸を下す
		if(auto_WORK_flag != 0){
			Auto_SetPosWork(&auto_WORK_flag);
			if(auto_WORK_flag == AUTO_RETUEN_WORK_FLAG){
				auto_WORK_flag = 0;
				auto_button_flag = 0;
			}
		}

		//端とかから中央に合わせる
		if(auto_center_flag == 1){
			Auto_SetCenter(&auto_center_flag);
			auto_center_flag = 0;
		}

		//端とかから時計回りに動かす
		if(auto_corner_flag == 1){
			Auto_SetCorner(&auto_corner_flag);
			auto_corner_flag = 0;
		}


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure LSE Drive Capability 
  */
  HAL_PWR_EnableBkUpAccess();
  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART3;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ETH Initialization Function
  * @param None
  * @retval None
  */
static void MX_ETH_Init(void)
{

  /* USER CODE BEGIN ETH_Init 0 */

  /* USER CODE END ETH_Init 0 */

   uint8_t MACAddr[6] ;

  /* USER CODE BEGIN ETH_Init 1 */

  /* USER CODE END ETH_Init 1 */
  heth.Instance = ETH;
  heth.Init.AutoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
  heth.Init.PhyAddress = LAN8742A_PHY_ADDRESS;
  MACAddr[0] = 0x00;
  MACAddr[1] = 0x80;
  MACAddr[2] = 0xE1;
  MACAddr[3] = 0x00;
  MACAddr[4] = 0x00;
  MACAddr[5] = 0x00;
  heth.Init.MACAddr = &MACAddr[0];
  heth.Init.RxMode = ETH_RXPOLLING_MODE;
  heth.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
  heth.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;

  /* USER CODE BEGIN MACADDRESS */
    
  /* USER CODE END MACADDRESS */

  if (HAL_ETH_Init(&heth) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ETH_Init 2 */

  /* USER CODE END ETH_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_LSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 95;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim4, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 48;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 9999;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 95;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 999;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */
  HAL_TIM_MspPostInit(&htim8);

}

/**
  * @brief TIM9 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM9_Init(void)
{

  /* USER CODE BEGIN TIM9_Init 0 */

  /* USER CODE END TIM9_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM9_Init 1 */

  /* USER CODE END TIM9_Init 1 */
  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 191;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 9999;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM9_Init 2 */

  /* USER CODE END TIM9_Init 2 */
  HAL_TIM_MspPostInit(&htim9);

}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 191;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 9999;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim10, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */
  HAL_TIM_MspPostInit(&htim10);

}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 191;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 9999;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim11, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */
  HAL_TIM_MspPostInit(&htim11);

}

/**
  * @brief TIM13 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM13_Init(void)
{

  /* USER CODE BEGIN TIM13_Init 0 */

  /* USER CODE END TIM13_Init 0 */

  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM13_Init 1 */

  /* USER CODE END TIM13_Init 1 */
  htim13.Instance = TIM13;
  htim13.Init.Prescaler = 191;
  htim13.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim13.Init.Period = 9999;
  htim13.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim13.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim13, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM13_Init 2 */

  /* USER CODE END TIM13_Init 2 */
  HAL_TIM_MspPostInit(&htim13);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, MD2_INB_Pin|CORELESS7_Pin|BUZZER_Pin|MD3_INB_Pin 
                          |MD2_INA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CORELESS4_Pin|MD6_INB_Pin|MD5_INB_Pin|MD5_INA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, CORELESS5_Pin|MD7_INB_Pin|MD7_INA_Pin|CORELESS6_Pin 
                          |MD6_INA_Pin|LD2_Pin|MD8_INA_Pin|MD8_INB_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, MD4_INA_Pin|MD4_INB_Pin|MD3_INA_Pin|LED4_Pin 
                          |CORELESS1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, MD1_INA_Pin|MD1_INB_Pin|SPI_SS_Pin|SPI_CS2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, LED2_Pin|LED1_Pin|LED3_Pin|CORELESS2_Pin 
                          |CORELESS3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : MSW8_Pin MSW9_Pin */
  GPIO_InitStruct.Pin = MSW8_Pin|MSW9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MD2_INB_Pin CORELESS7_Pin BUZZER_Pin MD3_INB_Pin 
                           MD2_INA_Pin */
  GPIO_InitStruct.Pin = MD2_INB_Pin|CORELESS7_Pin|BUZZER_Pin|MD3_INB_Pin 
                          |MD2_INA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : MSW4_Pin MSW3_Pin MSW2_Pin */
  GPIO_InitStruct.Pin = MSW4_Pin|MSW3_Pin|MSW2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : MSW1_Pin */
  GPIO_InitStruct.Pin = MSW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(MSW1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CORELESS4_Pin MD6_INB_Pin MD5_INB_Pin MD5_INA_Pin */
  GPIO_InitStruct.Pin = CORELESS4_Pin|MD6_INB_Pin|MD5_INB_Pin|MD5_INA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : CORELESS5_Pin MD7_INB_Pin MD7_INA_Pin CORELESS6_Pin 
                           MD6_INA_Pin LD2_Pin MD8_INA_Pin MD8_INB_Pin */
  GPIO_InitStruct.Pin = CORELESS5_Pin|MD7_INB_Pin|MD7_INA_Pin|CORELESS6_Pin 
                          |MD6_INA_Pin|LD2_Pin|MD8_INA_Pin|MD8_INB_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : MD4_INA_Pin MD4_INB_Pin MD3_INA_Pin LED4_Pin 
                           CORELESS1_Pin */
  GPIO_InitStruct.Pin = MD4_INA_Pin|MD4_INB_Pin|MD3_INA_Pin|LED4_Pin 
                          |CORELESS1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : MD1_INA_Pin MD1_INB_Pin SPI_SS_Pin SPI_CS2_Pin */
  GPIO_InitStruct.Pin = MD1_INA_Pin|MD1_INB_Pin|SPI_SS_Pin|SPI_CS2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : MSW6_Pin MSW7_Pin */
  GPIO_InitStruct.Pin = MSW6_Pin|MSW7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON3_Pin BUTTON2_Pin */
  GPIO_InitStruct.Pin = BUTTON3_Pin|BUTTON2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : LED2_Pin LED1_Pin LED3_Pin CORELESS2_Pin 
                           CORELESS3_Pin */
  GPIO_InitStruct.Pin = LED2_Pin|LED1_Pin|LED3_Pin|CORELESS2_Pin 
                          |CORELESS3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON1_Pin */
  GPIO_InitStruct.Pin = BUTTON1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MSW5_Pin */
  GPIO_InitStruct.Pin = MSW5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(MSW5_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
