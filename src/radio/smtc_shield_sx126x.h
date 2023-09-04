#ifndef SMTC_SHIELD_SX126X_H
#define SMTC_SHIELD_SX126X_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "smtc_shield_sx126x_types.h"

typedef const smtc_shield_sx126x_pa_pwr_cfg_t* ( *smtc_shield_sx126x_get_pa_pwr_cfg_f )(
    const uint32_t rf_freq_in_hz, int8_t expected_output_pwr_in_dbm );

typedef bool ( *smtc_shield_sx126x_is_dio2_set_as_rf_switch_f )( void );

typedef sx126x_reg_mod_t ( *smtc_shield_sx126x_get_reg_mode_f )( void );

typedef const smtc_shield_sx126x_xosc_cfg_t* ( *smtc_shield_sx126x_get_xosc_cfg_f )( void );

typedef struct smtc_shield_sx126x_s
{
    smtc_shield_sx126x_get_pa_pwr_cfg_f           get_pa_pwr_cfg;
    smtc_shield_sx126x_is_dio2_set_as_rf_switch_f is_dio2_set_as_rf_switch;
    smtc_shield_sx126x_get_reg_mode_f             get_reg_mode;
    smtc_shield_sx126x_get_xosc_cfg_f             get_xosc_cfg;
} smtc_shield_sx126x_t;

static inline const smtc_shield_sx126x_pa_pwr_cfg_t* smtc_shield_sx126x_get_pa_pwr_cfg(
    smtc_shield_sx126x_t* shield, const uint32_t rf_freq_in_hz, int8_t expected_output_pwr_in_dbm )
{
    return shield->get_pa_pwr_cfg( rf_freq_in_hz, expected_output_pwr_in_dbm );
}

static inline bool smtc_shield_sx126x_is_dio2_set_as_rf_switch( smtc_shield_sx126x_t* shield )
{
    return shield->is_dio2_set_as_rf_switch( );
}

static inline sx126x_reg_mod_t smtc_shield_sx126x_get_reg_mode( smtc_shield_sx126x_t* shield )
{
    return shield->get_reg_mode( );
}

static inline const smtc_shield_sx126x_xosc_cfg_t* smtc_shield_sx126x_get_xosc_cfg( smtc_shield_sx126x_t* shield )
{
    return shield->get_xosc_cfg( );
}

#ifdef __cplusplus
}
#endif

#endif