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
#define Off_Pin GPIO_PIN_13
#define Off_GPIO_Port GPIOC
#define Idig_Pin GPIO_PIN_14
#define Idig_GPIO_Port GPIOC
#define OtherC15_Pin GPIO_PIN_15
#define OtherC15_GPIO_Port GPIOC
#define OtherC0_Pin GPIO_PIN_0
#define OtherC0_GPIO_Port GPIOC
#define OtherC1_Pin GPIO_PIN_1
#define OtherC1_GPIO_Port GPIOC
#define OtherC3_Pin GPIO_PIN_2
#define OtherC3_GPIO_Port GPIOC
#define OtherC4_Pin GPIO_PIN_3
#define OtherC4_GPIO_Port GPIOC
#define OtherA0_Pin GPIO_PIN_0
#define OtherA0_GPIO_Port GPIOA
#define OtherA1_Pin GPIO_PIN_1
#define OtherA1_GPIO_Port GPIOA
#define data1820_Pin GPIO_PIN_2
#define data1820_GPIO_Port GPIOA
#define ADC_Temp_Pin GPIO_PIN_3
#define ADC_Temp_GPIO_Port GPIOA
#define ADC_Mode_Pin GPIO_PIN_4
#define ADC_Mode_GPIO_Port GPIOA
#define OtherA5_Pin GPIO_PIN_5
#define OtherA5_GPIO_Port GPIOA
#define OtherA6_Pin GPIO_PIN_6
#define OtherA6_GPIO_Port GPIOA
#define OtherA7_Pin GPIO_PIN_7
#define OtherA7_GPIO_Port GPIOA
#define DIR3_Pin GPIO_PIN_4
#define DIR3_GPIO_Port GPIOC
#define OtherC5_Pin GPIO_PIN_5
#define OtherC5_GPIO_Port GPIOC
#define FCS_Pin GPIO_PIN_0
#define FCS_GPIO_Port GPIOB
#define Door_Pin GPIO_PIN_1
#define Door_GPIO_Port GPIOB
#define down_In_Pin GPIO_PIN_2
#define down_In_GPIO_Port GPIOB
#define Fdata_Pin GPIO_PIN_12
#define Fdata_GPIO_Port GPIOB
#define FCLK_Pin GPIO_PIN_13
#define FCLK_GPIO_Port GPIOB
#define EXTI14_Pin GPIO_PIN_14
#define EXTI14_GPIO_Port GPIOB
#define Sp_Pin GPIO_PIN_15
#define Sp_GPIO_Port GPIOB
#define Latch_Pin GPIO_PIN_6
#define Latch_GPIO_Port GPIOC
#define OE_Pin GPIO_PIN_7
#define OE_GPIO_Port GPIOC
#define Right_in_Pin GPIO_PIN_8
#define Right_in_GPIO_Port GPIOC
#define OtherC9_Pin GPIO_PIN_9
#define OtherC9_GPIO_Port GPIOC
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
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define Enc_1_Pin GPIO_PIN_15
#define Enc_1_GPIO_Port GPIOA
#define grill_In_Pin GPIO_PIN_11
#define grill_In_GPIO_Port GPIOC
#define OtherC12_Pin GPIO_PIN_12
#define OtherC12_GPIO_Port GPIOC
#define exti_Enc_2_Pin GPIO_PIN_2
#define exti_Enc_2_GPIO_Port GPIOD
#define exti_Enc_2_EXTI_IRQn EXTI2_IRQn
#define Enc_2_Pin GPIO_PIN_3
#define Enc_2_GPIO_Port GPIOB
#define Other5_Pin GPIO_PIN_4
#define Other5_GPIO_Port GPIOB
#define MOSI_Pin GPIO_PIN_5
#define MOSI_GPIO_Port GPIOB
#define OtherB6_Pin GPIO_PIN_6
#define OtherB6_GPIO_Port GPIOB
#define OtherB7_Pin GPIO_PIN_7
#define OtherB7_GPIO_Port GPIOB
#define Button_Pin GPIO_PIN_8
#define Button_GPIO_Port GPIOB
#define Led_Pin GPIO_PIN_9
#define Led_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define Latch Latch_GPIO_Port,Latch_Pin
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
