#include "gpio.h"
#include "nucleo-f756zg.h"
#include "shell/boardShell.h"
#include "shell/shell.h"
#include "spi.h"
#include "stm32f7xx_hal_gpio.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#include "boardShell.h"
#include "boardStdio.h"

extern uint8_t rx_buffer[];
extern uint32_t rx_buffer_length;

int main(void) {

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USB_DEVICE_Init();

  boardShellInit();

  while (1) {

    HAL_Delay(50);
    HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

    boardShellProcess();
  }
}
