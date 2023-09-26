#include "bootloader.h"

#include "stm32f7xx_hal.h"

// #include "gpio.h"

#define BOOTLOADER_ADDRESS 0x1FF00000
#define BOOTLOADER_MAGIC 0x1FF0EDBE
typedef void (*pFunction)(void);

void bootloadSet(void) { RTC->BKP0R = BOOTLOADER_MAGIC; }
void bootloadReset(void) { HAL_NVIC_SystemReset(); }

void bootloadCheck(void) {
  if (RTC->BKP0R != BOOTLOADER_MAGIC)
    return;

  RTC->BKP0R = 0;

  uint32_t jumpAddress = *(__IO uint32_t *)(0x1FF00004);
  pFunction jumpApplication = (pFunction)jumpAddress;

  __set_MSP(*(__IO uint32_t *)BOOTLOADER_ADDRESS);
  SCB->VTOR = BOOTLOADER_ADDRESS;
  jumpApplication();
}

// void buttonCheck(void) {
//   GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//   // init gpio for button input
//   __HAL_RCC_GPIOC_CLK_ENABLE();
//   GPIO_InitStruct.Pin = USER_Btn_Pin;
//   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//   GPIO_InitStruct.Pull = GPIO_NOPULL;
//   HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);
//
//   // inital wait for double pressing for bootloader entry
//   HAL_Delay(1000);
//
//   // test if button held for 5 seconds
//   uint8_t count = 0;
//   while (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET)
//   {
//     HAL_Delay(1000);
//     count++;
//     if (count == 5)
//       bootloadReset();
//   }
// }
