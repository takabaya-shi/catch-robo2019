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
#include "stm32f7xx_hal.h"

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
#define MSW8_Pin GPIO_PIN_2
#define MSW8_GPIO_Port GPIOE
#define MSW9_Pin GPIO_PIN_4
#define MSW9_GPIO_Port GPIOE
#define SERVO2_Pin GPIO_PIN_5
#define SERVO2_GPIO_Port GPIOE
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define MD2_INB_Pin GPIO_PIN_3
#define MD2_INB_GPIO_Port GPIOF
#define CORELESS7_Pin GPIO_PIN_4
#define CORELESS7_GPIO_Port GPIOF
#define SERVO1_Pin GPIO_PIN_6
#define SERVO1_GPIO_Port GPIOF
#define SERVO3_Pin GPIO_PIN_7
#define SERVO3_GPIO_Port GPIOF
#define BRUSHLESS_Pin GPIO_PIN_8
#define BRUSHLESS_GPIO_Port GPIOF
#define BUZZER_Pin GPIO_PIN_9
#define BUZZER_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define MSW4_Pin GPIO_PIN_0
#define MSW4_GPIO_Port GPIOC
#define RMII_MDC_Pin GPIO_PIN_1
#define RMII_MDC_GPIO_Port GPIOC
#define MSW3_Pin GPIO_PIN_2
#define MSW3_GPIO_Port GPIOC
#define MSW2_Pin GPIO_PIN_3
#define MSW2_GPIO_Port GPIOC
#define ENC1_A_Pin GPIO_PIN_0
#define ENC1_A_GPIO_Port GPIOA
#define RMII_REF_CLK_Pin GPIO_PIN_1
#define RMII_REF_CLK_GPIO_Port GPIOA
#define RMII_MDIO_Pin GPIO_PIN_2
#define RMII_MDIO_GPIO_Port GPIOA
#define MSW1_Pin GPIO_PIN_4
#define MSW1_GPIO_Port GPIOA
#define CORELESS4_Pin GPIO_PIN_6
#define CORELESS4_GPIO_Port GPIOA
#define RMII_CRS_DV_Pin GPIO_PIN_7
#define RMII_CRS_DV_GPIO_Port GPIOA
#define RMII_RXD0_Pin GPIO_PIN_4
#define RMII_RXD0_GPIO_Port GPIOC
#define RMII_RXD1_Pin GPIO_PIN_5
#define RMII_RXD1_GPIO_Port GPIOC
#define CORELESS5_Pin GPIO_PIN_1
#define CORELESS5_GPIO_Port GPIOB
#define MD3_INB_Pin GPIO_PIN_14
#define MD3_INB_GPIO_Port GPIOF
#define MD2_INA_Pin GPIO_PIN_15
#define MD2_INA_GPIO_Port GPIOF
#define PWMH1_Pin GPIO_PIN_9
#define PWMH1_GPIO_Port GPIOE
#define MD4_INA_Pin GPIO_PIN_10
#define MD4_INA_GPIO_Port GPIOE
#define PWMH2_Pin GPIO_PIN_11
#define PWMH2_GPIO_Port GPIOE
#define MD4_INB_Pin GPIO_PIN_12
#define MD4_INB_GPIO_Port GPIOE
#define PWMH3_Pin GPIO_PIN_13
#define PWMH3_GPIO_Port GPIOE
#define PWMH4_Pin GPIO_PIN_14
#define PWMH4_GPIO_Port GPIOE
#define MD3_INA_Pin GPIO_PIN_15
#define MD3_INA_GPIO_Port GPIOE
#define MD7_INB_Pin GPIO_PIN_11
#define MD7_INB_GPIO_Port GPIOB
#define MD7_INA_Pin GPIO_PIN_12
#define MD7_INA_GPIO_Port GPIOB
#define RMII_TXD1_Pin GPIO_PIN_13
#define RMII_TXD1_GPIO_Port GPIOB
#define CORELESS6_Pin GPIO_PIN_14
#define CORELESS6_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define ENC3_A_Pin GPIO_PIN_12
#define ENC3_A_GPIO_Port GPIOD
#define ENC3_B_Pin GPIO_PIN_13
#define ENC3_B_GPIO_Port GPIOD
#define MD1_INA_Pin GPIO_PIN_14
#define MD1_INA_GPIO_Port GPIOD
#define MD1_INB_Pin GPIO_PIN_15
#define MD1_INB_GPIO_Port GPIOD
#define MSW6_Pin GPIO_PIN_2
#define MSW6_GPIO_Port GPIOG
#define MSW7_Pin GPIO_PIN_3
#define MSW7_GPIO_Port GPIOG
#define BUTTON3_Pin GPIO_PIN_4
#define BUTTON3_GPIO_Port GPIOG
#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOG
#define BUTTON2_Pin GPIO_PIN_7
#define BUTTON2_GPIO_Port GPIOG
#define LED3_Pin GPIO_PIN_8
#define LED3_GPIO_Port GPIOG
#define PWMH5_Pin GPIO_PIN_6
#define PWMH5_GPIO_Port GPIOC
#define PWMH6_Pin GPIO_PIN_7
#define PWMH6_GPIO_Port GPIOC
#define PWMH7_Pin GPIO_PIN_8
#define PWMH7_GPIO_Port GPIOC
#define PWMH8_Pin GPIO_PIN_9
#define PWMH8_GPIO_Port GPIOC
#define MD6_INB_Pin GPIO_PIN_8
#define MD6_INB_GPIO_Port GPIOA
#define MD5_INB_Pin GPIO_PIN_11
#define MD5_INB_GPIO_Port GPIOA
#define MD5_INA_Pin GPIO_PIN_12
#define MD5_INA_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define BUTTON1_Pin GPIO_PIN_15
#define BUTTON1_GPIO_Port GPIOA
#define SPI_SS_Pin GPIO_PIN_2
#define SPI_SS_GPIO_Port GPIOD
#define MSW5_Pin GPIO_PIN_3
#define MSW5_GPIO_Port GPIOD
#define SPI_CS2_Pin GPIO_PIN_7
#define SPI_CS2_GPIO_Port GPIOD
#define CORELESS2_Pin GPIO_PIN_9
#define CORELESS2_GPIO_Port GPIOG
#define RMII_TX_EN_Pin GPIO_PIN_11
#define RMII_TX_EN_GPIO_Port GPIOG
#define CORELESS3_Pin GPIO_PIN_12
#define CORELESS3_GPIO_Port GPIOG
#define RMII_TXD0_Pin GPIO_PIN_13
#define RMII_TXD0_GPIO_Port GPIOG
#define ENC1_B_Pin GPIO_PIN_3
#define ENC1_B_GPIO_Port GPIOB
#define ENC2_A_Pin GPIO_PIN_4
#define ENC2_A_GPIO_Port GPIOB
#define ENC2_B_Pin GPIO_PIN_5
#define ENC2_B_GPIO_Port GPIOB
#define MD6_INA_Pin GPIO_PIN_6
#define MD6_INA_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
#define MD8_INA_Pin GPIO_PIN_8
#define MD8_INA_GPIO_Port GPIOB
#define MD8_INB_Pin GPIO_PIN_9
#define MD8_INB_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_0
#define LED4_GPIO_Port GPIOE
#define CORELESS1_Pin GPIO_PIN_1
#define CORELESS1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
