#include "gpio.h"
#include "nucleo-f756zg.h"
#include "spi.h"
#include "stm32f7xx_hal_gpio.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#include "apps_common.h"
#include "apps_utilities.h"
#include "smtc_hal_dbg_trace.h"
#include "sx126x.h"
#include "sx126x_regs.h"

extern uint8_t rx_buffer[];
extern uint32_t rx_buffer_length;

static sx126x_hal_context_t *context;

void start_radio(void) {
  context = apps_common_sx126x_get_context();
  apps_common_shield_init();
  apps_common_sx126x_init((void *)context);
  apps_common_sx126x_radio_init((void *)context);

  apps_common_sx126x_init((void *)context);
  apps_common_sx126x_radio_init((void *)context);

  sx126x_set_dio_irq_params(context, SX126X_IRQ_ALL,
                            SX126X_IRQ_TX_DONE | SX126X_IRQ_RX_DONE |
                                SX126X_IRQ_TIMEOUT | SX126X_IRQ_HEADER_ERROR |
                                SX126X_IRQ_CRC_ERROR,
                            SX126X_IRQ_NONE, SX126X_IRQ_NONE);

  sx126x_clear_irq_status(context, SX126X_IRQ_ALL);

  sx126x_set_rx(context, RX_CONTINUOUS);
}

int main(void) {

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USB_DEVICE_Init();

  // halt here until vcp is opened...

  memset(rx_buffer, 0, 1024);

  // start_radio();

  while (1) {

    HAL_Delay(50);
    HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);

    if (HAL_GPIO_ReadPin(LORA_DIO1_GPIO_Port, LORA_DIO1_Pin) == GPIO_PIN_SET) {
      radio_on_dio_irq(context);
    }

    if (dbug_enable == 1)
      apps_common_sx126x_irq_process(context);

    if (rx_buffer_length > 0 && dbug_enable == 0) {
      if (rx_buffer[0] == 'S')
        dbug_enable = 1;
      start_radio();
      HAL_DBG_TRACE_INFO("started radio\r\n");
      // CDC_Transmit_FS(rx_buffer, rx_buffer_length);
      rx_buffer_length = 0;
    }
  }
}

void on_tx_done(void) {
  HAL_Delay(500);

  sx126x_set_rx(context, RX_CONTINUOUS);
}

void on_rx_done(void) {
  uint8_t buffer_rx[PAYLOAD_LENGTH];
  uint8_t size;

  apps_common_sx126x_receive(context, buffer_rx, &size, PAYLOAD_LENGTH);

  CDC_Transmit_FS(buffer_rx, size);

  sx126x_set_rx(context, RX_CONTINUOUS);
}

void on_rx_timeout(void) { sx126x_set_rx(context, RX_CONTINUOUS); }

void on_rx_error(void) { sx126x_set_rx(context, RX_CONTINUOUS); }
