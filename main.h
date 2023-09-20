/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SG90_Pin GPIO_PIN_6
#define SG90_GPIO_Port GPIOA
#define Right_Pin GPIO_PIN_8
#define Right_GPIO_Port GPIOE
#define Left_Pin GPIO_PIN_12
#define Left_GPIO_Port GPIOB
#define IN1_Pin GPIO_PIN_2
#define IN1_GPIO_Port GPIOG
#define IN2_Pin GPIO_PIN_4
#define IN2_GPIO_Port GPIOG
#define IN3_Pin GPIO_PIN_6
#define IN3_GPIO_Port GPIOG
#define IN4_Pin GPIO_PIN_8
#define IN4_GPIO_Port GPIOG
#define HC_SR04_Return_Pin GPIO_PIN_11
#define HC_SR04_Return_GPIO_Port GPIOG
#define HC_SR04_OUT_Pin GPIO_PIN_12
#define HC_SR04_OUT_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
