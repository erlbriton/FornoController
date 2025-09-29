/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_spi.h"
#include "stm32f4xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
//extern uint32_t adcTemp[ ];
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
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define C14_Pin GPIO_PIN_14
#define C14_GPIO_Port GPIOC
#define C15_Pin GPIO_PIN_15
#define C15_GPIO_Port GPIOC
#define C0_Pin GPIO_PIN_0
#define C0_GPIO_Port GPIOC
#define C1_Pin GPIO_PIN_1
#define C1_GPIO_Port GPIOC
#define C3_Pin GPIO_PIN_2
#define C3_GPIO_Port GPIOC
#define C4_Pin GPIO_PIN_3
#define C4_GPIO_Port GPIOC
#define A0_Pin GPIO_PIN_0
#define A0_GPIO_Port GPIOA
#define A1_Pin GPIO_PIN_1
#define A1_GPIO_Port GPIOA
#define data1820_Pin GPIO_PIN_2
#define data1820_GPIO_Port GPIOA
#define ADC_Temp_Pin GPIO_PIN_3
#define ADC_Temp_GPIO_Port GPIOA
#define ADC_Mode_Pin GPIO_PIN_4
#define ADC_Mode_GPIO_Port GPIOA
#define DIR3_Pin GPIO_PIN_4
#define DIR3_GPIO_Port GPIOC
#define C5_Pin GPIO_PIN_5
#define C5_GPIO_Port GPIOC
#define FCS_Pin GPIO_PIN_0
#define FCS_GPIO_Port GPIOB
#define Door_Pin GPIO_PIN_1
#define Door_GPIO_Port GPIOB
#define down_In_Pin GPIO_PIN_2
#define down_In_GPIO_Port GPIOB
#define FCLK_Pin GPIO_PIN_12
#define FCLK_GPIO_Port GPIOB
#define Fdata_Pin GPIO_PIN_13
#define Fdata_GPIO_Port GPIOB
#define EXTI14_Pin GPIO_PIN_14
#define EXTI14_GPIO_Port GPIOB
#define Sp_Pin GPIO_PIN_15
#define Sp_GPIO_Port GPIOB
#define Latch_Pin GPIO_PIN_6
#define Latch_GPIO_Port GPIOC
#define C8_Pin GPIO_PIN_8
#define C8_GPIO_Port GPIOC
#define right_In_Pin GPIO_PIN_9
#define right_In_GPIO_Port GPIOC
#define MR_Pin GPIO_PIN_8
#define MR_GPIO_Port GPIOA
#define TX1_Pin GPIO_PIN_9
#define TX1_GPIO_Port GPIOA
#define RX1_Pin GPIO_PIN_10
#define RX1_GPIO_Port GPIOA
#define Fan_out_Pin GPIO_PIN_11
#define Fan_out_GPIO_Port GPIOA
#define Light_Pin GPIO_PIN_12
#define Light_GPIO_Port GPIOA
#define Enc_1_Pin GPIO_PIN_15
#define Enc_1_GPIO_Port GPIOA
#define grill_In_Pin GPIO_PIN_11
#define grill_In_GPIO_Port GPIOC
#define C12_Pin GPIO_PIN_12
#define C12_GPIO_Port GPIOC
#define exti2Enc_Pin GPIO_PIN_2
#define exti2Enc_GPIO_Port GPIOD
#define exti2Enc_EXTI_IRQn EXTI2_IRQn
#define Enc_2_Pin GPIO_PIN_3
#define Enc_2_GPIO_Port GPIOB
#define Other5_Pin GPIO_PIN_4
#define Other5_GPIO_Port GPIOB
#define MOSI_Pin GPIO_PIN_5
#define MOSI_GPIO_Port GPIOB
#define B6_Pin GPIO_PIN_6
#define B6_GPIO_Port GPIOB
#define OE_Pin GPIO_PIN_7
#define OE_GPIO_Port GPIOB
#define Button_Pin GPIO_PIN_8
#define Button_GPIO_Port GPIOB
#define B9Other_Pin GPIO_PIN_9
#define B9Other_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define Latch Latch_GPIO_Port,Latch_Pin
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
