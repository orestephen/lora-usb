#ifndef SMTC_SHIELD_SX126X_TYPES_H
#define SMTC_SHIELD_SX126X_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "sx126x.h"

#define SMTC_SHIELD_SX126X_FREQ_MIN 150000000
#define SMTC_SHIELD_SX126X_FREQ_MAX 960000000

#define SMTC_SHIELD_SX1261_MIN_PWR -17
#define SMTC_SHIELD_SX1261_MAX_PWR 15

#define SMTC_SHIELD_SX1262_MIN_PWR -9
#define SMTC_SHIELD_SX1262_MAX_PWR 22

#define SMTC_SHIELD_SX1268_MIN_PWR -9
#define SMTC_SHIELD_SX1268_MAX_PWR 22

typedef struct smtc_shield_sx126x_pa_pwr_cfg_s
{
    int8_t                 power;
    sx126x_pa_cfg_params_t pa_config;
} smtc_shield_sx126x_pa_pwr_cfg_t;

typedef struct smtc_shield_sx126x_xosc_cfg_s
{
    bool                        tcxo_is_radio_controlled;
    sx126x_tcxo_ctrl_voltages_t supply_voltage;
    uint32_t                    startup_time_in_tick;
} smtc_shield_sx126x_xosc_cfg_t;

#ifdef __cplusplus
}
#endif

#endif