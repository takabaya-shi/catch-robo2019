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
#include "stm32f4xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define ENCA_Pin GPIO_PIN_0
#define ENCA_GPIO_Port GPIOA
#define ENCB_Pin GPIO_PIN_1
#define ENCB_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define SERVO2_Pin GPIO_PIN_6
#define SERVO2_GPIO_Port GPIOA
#define SERVO1_Pin GPIO_PIN_7
#define SERVO1_GPIO_Port GPIOA
#define MicroSW1_Pin GPIO_PIN_5
#define MicroSW1_GPIO_Port GPIOC
#define MicroSW2_Pin GPIO_PIN_0
#define MicroSW2_GPIO_Port GPIOB
#define MicroSW3_Pin GPIO_PIN_1
#define MicroSW3_GPIO_Port GPIOB
#define MIcroSW4_Pin GPIO_PIN_2
#define MIcroSW4_GPIO_Port GPIOB
#define MD4_INB_Pin GPIO_PIN_12
#define MD4_INB_GPIO_Port GPIOB
#define MD4_INA_Pin GPIO_PIN_13
#define MD4_INA_GPIO_Port GPIOB
#define MD3_INB_Pin GPIO_PIN_14
#define MD3_INB_GPIO_Port GPIOB
#define MD3_INA_Pin GPIO_PIN_15
#define MD3_INA_GPIO_Port GPIOB
#define MD2_INB_Pin GPIO_PIN_6
#define MD2_INB_GPIO_Port GPIOC
#define MD2_INA_Pin GPIO_PIN_7
#define MD2_INA_GPIO_Port GPIOC
#define MD4_PWM_Pin GPIO_PIN_8
#define MD4_PWM_GPIO_Port GPIOC
#define MD3_PWM_Pin GPIO_PIN_9
#define MD3_PWM_GPIO_Port GPIOC
#define MD2_PWM_Pin GPIO_PIN_8
#define MD2_PWM_GPIO_Port GPIOA
#define MD1_PWM_Pin GPIO_PIN_9
#define MD1_PWM_GPIO_Port GPIOA
#define MD1_INB_Pin GPIO_PIN_11
#define MD1_INB_GPIO_Port GPIOA
#define MD1_INA_Pin GPIO_PIN_12
#define MD1_INA_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SPI_SS_Pin GPIO_PIN_2
#define SPI_SS_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define SERVO3_Pin GPIO_PIN_9
#define SERVO3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
