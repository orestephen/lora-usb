#ifndef APPS_UTILITIES_H
#define APPS_UTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * -----------------------------------------------------------------------------
 * --- DEPENDENCIES ------------------------------------------------------------
 */

#include "sx126x_hal.h"
#include <stdint.h>

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC MACROS -----------------------------------------------------------
 */

/*!
 * @brief Stringify constants
 */
#define xstr(a) str(a)
#define str(a) #a

/*!
 * @brief Helper macro that returned a human-friendly message if a command does
 * not return SX126X_STATUS_OK
 *
 * @remark The macro is implemented to be used with functions returning a @ref
 * sx126x_status_t
 *
 * @param[in] rc  Return code
 */
#define ASSERT_SX126X_RC(rc)                                                   \
  {                                                                            \
    const sx126x_status_t status = rc;                                         \
    if (status != SX126X_STATUS_OK) {                                          \
      if (status == SX126X_STATUS_ERROR) {                                     \
        HAL_DBG_TRACE_ERROR("In %s - %s (line %d): %s\n", __FILE__, __func__,  \
                            __LINE__, xstr(SX126X_STATUS_ERROR));              \
      } else {                                                                 \
        HAL_DBG_TRACE_WARNING("In %s - %s (line %d): Status code = %d\n",      \
                              __FILE__, __func__, __LINE__, status);           \
      }                                                                        \
    }                                                                          \
  }

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC CONSTANTS --------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC TYPES ------------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS PROTOTYPES ---------------------------------------------
 */

#ifdef __cplusplus
}
#endif

#endif // APPS_UTILITIES_H

/* --- EOF ------------------------------------------------------------------ */
