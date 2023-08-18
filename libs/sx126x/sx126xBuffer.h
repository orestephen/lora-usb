#ifndef __SX126X_BUFFER_H__
#define __SX126X_BUFFER_H__

#include "sx126x.h"
#include "sx126xTypes.h"

int32_t sx126xBufferSetTxBuffer(sx126x_t* pContext, uint8_t address, uint8_t* pBuffer, uint8_t bufferLength);
int32_t sx126xBufferGetRxBuffer(sx126x_t* pContext, uint8_t address, uint8_t* pBuffer, uint8_t bufferLength);

#endif