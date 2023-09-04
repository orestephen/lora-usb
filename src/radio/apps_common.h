#ifndef APPS_COMMON_H
#define APPS_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apps_configuration.h"
#include "sx126x.h"
#include "sx126x_hal_context.h"
#include <stdint.h>

#define RX_CONTINUOUS 0xFFFFFF

sx126x_hal_context_t *apps_common_sx126x_get_context();

void apps_common_shield_init(void);

void apps_common_sx126x_init(const sx126x_hal_context_t *context);

void apps_common_sx126x_radio_init(const void *context);

void apps_common_sx126x_receive(const void *context, uint8_t *buffer,
                                uint8_t *size, uint8_t max_size);

void apps_common_sx126x_irq_process(const void *context);

void apps_common_sx126x_print_config(void);

void apps_common_sx126x_print_version_info(void);

uint32_t get_time_on_air_in_ms(void);

inline static uint8_t apps_common_compute_lora_ldro(const sx126x_lora_sf_t sf,
                                                    const sx126x_lora_bw_t bw) {
  switch (bw) {
  case SX126X_LORA_BW_500:
    return 0;

  case SX126X_LORA_BW_250:
    if (sf == SX126X_LORA_SF12) {
      return 1;
    } else {
      return 0;
    }

  case SX126X_LORA_BW_125:
    if ((sf == SX126X_LORA_SF12) || (sf == SX126X_LORA_SF11)) {
      return 1;
    } else {
      return 0;
    }

  case SX126X_LORA_BW_062:
    if ((sf == SX126X_LORA_SF12) || (sf == SX126X_LORA_SF11) ||
        (sf == SX126X_LORA_SF10)) {
      return 1;
    } else {
      return 0;
    }

  case SX126X_LORA_BW_041:
    if ((sf == SX126X_LORA_SF12) || (sf == SX126X_LORA_SF11) ||
        (sf == SX126X_LORA_SF10) || (sf == SX126X_LORA_SF9)) {
      return 1;
    } else {
      return 0;
    }

  case SX126X_LORA_BW_031:
  case SX126X_LORA_BW_020:
  case SX126X_LORA_BW_015:
  case SX126X_LORA_BW_010:
  case SX126X_LORA_BW_007:
    return 1;

  default:
    return 0;
  }
}

void radio_on_dio_irq(void *context);
void on_tx_done(void);
void on_rx_done(void);
void on_preamble_detected(void);
void on_syncword_valid(void);
void on_header_valid(void);
void on_header_error(void);
void on_crc_error(void);
void on_rx_timeout(void);
void on_rx_error(void);
void on_cad_done_undetected(void);
void on_cad_done_detected(void);
void on_fhss_hop_done(void);

#ifdef __cplusplus
}
#endif

#endif
