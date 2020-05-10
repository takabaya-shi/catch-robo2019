/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define ENC2A_Pin GPIO_PIN_0
#define ENC2A_GPIO_Port GPIOA
#define ENC2B_Pin GPIO_PIN_1
#define ENC2B_GPIO_Port GPIOA
#define VCP_TX_Pin GPIO_PIN_2
#define VCP_TX_GPIO_Port GPIOA
#define MicroSW1_Pin GPIO_PIN_3
#define MicroSW1_GPIO_Port GPIOA
#define MicroSW2_Pin GPIO_PIN_4
#define MicroSW2_GPIO_Port GPIOA
#define MD1_INA_Pin GPIO_PIN_6
#define MD1_INA_GPIO_Port GPIOA
#define MD1_INB_Pin GPIO_PIN_7
#define MD1_INB_GPIO_Port GPIOA
#define MD2_INA_Pin GPIO_PIN_0
#define MD2_INA_GPIO_Port GPIOB
#define MD2_INB_Pin GPIO_PIN_1
#define MD2_INB_GPIO_Port GPIOB
#define ENC1A_Pin GPIO_PIN_8
#define ENC1A_GPIO_Port GPIOA
#define ENC1B_Pin GPIO_PIN_9
#define ENC1B_GPIO_Port GPIOA
#define SERVO1_Pin GPIO_PIN_12
#define SERVO1_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define VCP_RX_Pin GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define LD3_Pin GPIO_PIN_3
#define LD3_GPIO_Port GPIOB
#define MD2_PWM_Pin GPIO_PIN_5
#define MD2_PWM_GPIO_Port GPIOB
#define MD1_PWM_Pin GPIO_PIN_7
#define MD1_PWM_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
