#include "sx126x_hal.h"

#include "sx126x_hal_context.h"

#include "gpio.h"
#include "spi.h"

void sx126x_hal_wait_on_busy(const void *radio) {
  const sx126x_hal_context_t *sx126x_context =
      (const sx126x_hal_context_t *)radio;
  uint8_t gpio_state;

  do {
    gpio_state =
        HAL_GPIO_ReadPin(sx126x_context->busy_port, sx126x_context->busy_pin);
  } while (gpio_state == GPIO_PIN_SET);
}

sx126x_hal_status_t sx126x_hal_reset(const void *context) {
  const sx126x_hal_context_t *sx126x_context =
      (const sx126x_hal_context_t *)context;

  HAL_GPIO_WritePin(sx126x_context->reset_port, sx126x_context->reset_pin,
                    GPIO_PIN_RESET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(sx126x_context->reset_port, sx126x_context->reset_pin,
                    GPIO_PIN_SET);

  return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_wakeup(const void *context) {
  const sx126x_hal_context_t *sx126x_context =
      (const sx126x_hal_context_t *)context;

  HAL_GPIO_WritePin(sx126x_context->cs_port, sx126x_context->cs_pin,
                    GPIO_PIN_RESET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(sx126x_context->cs_port, sx126x_context->cs_pin,
                    GPIO_PIN_SET);

  return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_write(const void *context,
                                     const uint8_t *command,
                                     const uint16_t command_length,
                                     const uint8_t *data,
                                     const uint16_t data_length) {
  const sx126x_hal_context_t *sx126x_context =
      (const sx126x_hal_context_t *)context;

  sx126x_hal_wait_on_busy(sx126x_context);

  HAL_GPIO_WritePin(sx126x_context->cs_port, sx126x_context->cs_pin,
                    GPIO_PIN_RESET);
  HAL_SPI_Transmit(sx126x_context->spi_handle, (uint8_t *)command,
                   command_length, 100);
  HAL_SPI_Transmit(sx126x_context->spi_handle, (uint8_t *)data, data_length,
                   100);
  HAL_GPIO_WritePin(sx126x_context->cs_port, sx126x_context->cs_pin,
                    GPIO_PIN_SET);

  return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_read(const void *context, const uint8_t *command,
                                    const uint16_t command_length,
                                    uint8_t *data, const uint16_t data_length) {
  const sx126x_hal_context_t *sx126x_context =
      (const sx126x_hal_context_t *)context;

  sx126x_hal_wait_on_busy(sx126x_context);

  HAL_GPIO_WritePin(sx126x_context->cs_port, sx126x_context->cs_pin,
                    GPIO_PIN_RESET);
  HAL_SPI_Transmit(sx126x_context->spi_handle, (uint8_t *)command,
                   command_length, 100);
  HAL_SPI_Receive(sx126x_context->spi_handle, (uint8_t *)data, data_length,
                  100);
  HAL_GPIO_WritePin(sx126x_context->cs_port, sx126x_context->cs_pin,
                    GPIO_PIN_SET);

  return SX126X_HAL_STATUS_OK;
}
