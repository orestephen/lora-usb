#include "gpio.h"
#include "nucleo-f756zg.h"
#include "spi.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

extern uint8_t rx_buffer[];
extern uint32_t rx_buffer_length;

int main(void) {

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USB_DEVICE_Init();

  uint8_t datasent = 0;
  int32_t ret;

  while (1) {

    HAL_Delay(50);
    HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

    if (rx_buffer_length > 0) {
      CDC_Transmit_FS(rx_buffer, rx_buffer_length);
      rx_buffer_length = 0;
    }
  }
}
