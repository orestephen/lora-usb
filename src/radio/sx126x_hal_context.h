#ifndef SX126X_HAL_CONTEXT_H
#define SX126X_HAL_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio.h"
#include "spi.h"

struct sx126x_hal_context_struct {
  SPI_HandleTypeDef *spi_handle;
  uint32_t busy_pin;
  GPIO_TypeDef *busy_port;
  uint32_t reset_pin;
  GPIO_TypeDef *reset_port;
  uint32_t cs_pin;
  GPIO_TypeDef *cs_port;
  uint32_t ant_pin;
  GPIO_TypeDef *ant_port;
};

typedef struct sx126x_hal_context_struct sx126x_hal_context_t;

#ifdef __cplusplus
}
#endif

#endif
