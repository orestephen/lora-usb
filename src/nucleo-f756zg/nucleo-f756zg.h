#ifndef __NULCEO_H
#define __NULCEO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"

// debugger pins
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SW0_Pin GPIO_PIN_3
#define SW0_GPIO_Port GPIOB

// usb pins
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA

// user pins
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB

// lora pins
#define LORA_nRESET_Pin GPIO_PIN_3
#define LORA_nRESET_GPIO_Port GPIOA
#define LORA_nCS_Pin GPIO_PIN_13
#define LORA_nCS_GPIO_Port GPIOF
#define LORA_ANT_SW_Pin GPIO_PIN_12
#define LORA_ANT_SW_GPIO_Port GPIOF
#define LORA_BUSY_Pin GPIO_PIN_13
#define LORA_BUSY_GPIO_Port GPIOE
#define LORA_DIO1_Pin GPIO_PIN_11
#define LORA_DIO1_GPIO_Port GPIOE
#define LORA_SPI_SCK_Pin GPIO_PIN_5
#define LORA_SPI_SCK_GPIO_Port GPIOA
#define LORA_SPI_SDO_Pin GPIO_PIN_6
#define LORA_SPI_SDO_GPIO_Port GPIOA
#define LORA_SPI_SDI_Pin GPIO_PIN_7
#define LORA_SPI_SDI_GPIO_Port GPIOA

void Error_Handler(void);
void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif
