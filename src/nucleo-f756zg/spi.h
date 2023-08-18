#ifndef __SPI_H
#define __SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "nucleo-f756zg.h"

extern SPI_HandleTypeDef hspi1;

void MX_SPI1_Init(void);

#ifdef __cplusplus
}
#endif

#endif
