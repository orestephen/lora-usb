#include "smtc_shield_sx126x_types.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

const smtc_shield_sx126x_pa_pwr_cfg_t smtc_shield_sx1261mb2bas_pa_pwr_cfg_table
    [SMTC_SHIELD_SX1261_MAX_PWR - SMTC_SHIELD_SX1261_MIN_PWR + 1] = {
        // Expected output power = -17dBm
        {
            .power = -14,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -16dBm
            .power = -13,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -15dBm
            .power = -12,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -14dBm
            .power = -10,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -13dBm
            .power = -12,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x04,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -12dBm
            .power = -9,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x01,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -11dBm
            .power = -9,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x02,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -10dBm
            .power = -6,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -9dBm
            .power = -6,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x01,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -8dBm
            .power = -4,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -7dBm
            .power = -5,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x03,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -6dBm
            .power = -2,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -5dBm
            .power = -1,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -4dBm
            .power = 0,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -3dBm
            .power = 1,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -2dBm
            .power = 2,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = -1dBm
            .power = 3,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 0dBm
            .power = 3,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x01,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 1dBm
            .power = 3,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x03,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 2dBm
            .power = 6,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 3dBm
            .power = 7,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 4dBm
            .power = 6,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x03,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 5dBm
            .power = 9,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 6dBm
            .power = 8,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x03,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 7dBm
            .power = 12,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 8dBm
            .power = 13,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 9dBm
            .power = 14,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x00,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 10dBm
            .power = 14,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x01,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 11dBm
            .power = 14,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x01,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 12dBm
            .power = 14,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x03,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 13dBm
            .power = 14,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x04,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 14dBm
            .power = 14,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x05,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
        {
            // Expected output power = 15dBm
            .power = 14,
            .pa_config =
                {
                    .hp_max = 0x00,
                    .pa_duty_cycle = 0x07,
                    .device_sel = 0x01,
                    .pa_lut = 0x01,
                },
        },
};

const smtc_shield_sx126x_xosc_cfg_t smtc_shield_sx1261mb2bas_xosc_cfg = {
    .tcxo_is_radio_controlled = false,
    .supply_voltage = SX126X_TCXO_CTRL_3_0V,
    .startup_time_in_tick = 300,
};

const smtc_shield_sx126x_pa_pwr_cfg_t *
smtc_shield_sx1261mb2bas_get_pa_pwr_cfg(const uint32_t rf_freq_in_hz,
                                        int8_t expected_output_pwr_in_dbm) {
  if ((SMTC_SHIELD_SX126X_FREQ_MIN <= rf_freq_in_hz) &&
      (rf_freq_in_hz <= SMTC_SHIELD_SX126X_FREQ_MAX)) {
    if ((SMTC_SHIELD_SX1261_MIN_PWR <= expected_output_pwr_in_dbm) &&
        (expected_output_pwr_in_dbm <= SMTC_SHIELD_SX1261_MAX_PWR)) {
      return &(smtc_shield_sx1261mb2bas_pa_pwr_cfg_table
                   [expected_output_pwr_in_dbm - SMTC_SHIELD_SX1261_MIN_PWR]);
    }
  }

  return NULL;
}

bool smtc_shield_sx1261mb2bas_is_dio2_set_as_rf_switch(void) { return true; }

sx126x_reg_mod_t smtc_shield_sx1261mb2bas_get_reg_mode(void) {
  return SX126X_REG_MODE_DCDC;
}

const smtc_shield_sx126x_xosc_cfg_t *
smtc_shield_sx1261mb2bas_get_xosc_cfg(void) {
  return &smtc_shield_sx1261mb2bas_xosc_cfg;
}
