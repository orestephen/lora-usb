#ifndef SMTC_SHIELD_SX1261MB2BAS_H
#define SMTC_SHIELD_SX1261MB2BAS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "smtc_shield_sx126x_types.h"
#include <stdbool.h>
#include <stdint.h>

#define SMTC_SHIELD_SX1261MB2BAS_INSTANTIATE                                   \
  {                                                                            \
    .get_pa_pwr_cfg = smtc_shield_sx1261mb2bas_get_pa_pwr_cfg,                 \
    .is_dio2_set_as_rf_switch =                                                \
        smtc_shield_sx1261mb2bas_is_dio2_set_as_rf_switch,                     \
    .get_reg_mode = smtc_shield_sx1261mb2bas_get_reg_mode,                     \
    .get_xosc_cfg = smtc_shield_sx1261mb2bas_get_xosc_cfg,                     \
  }

const smtc_shield_sx126x_pa_pwr_cfg_t *
smtc_shield_sx1261mb2bas_get_pa_pwr_cfg(const uint32_t rf_freq_in_hz,
                                        int8_t expected_output_pwr_in_dbm);

bool smtc_shield_sx1261mb2bas_is_dio2_set_as_rf_switch(void);

sx126x_reg_mod_t smtc_shield_sx1261mb2bas_get_reg_mode(void);

const smtc_shield_sx126x_xosc_cfg_t *
smtc_shield_sx1261mb2bas_get_xosc_cfg(void);

#ifdef __cplusplus
}
#endif

#endif