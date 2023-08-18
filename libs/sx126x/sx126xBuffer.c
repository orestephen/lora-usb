#include "sx126xBuffer.h"

#include <stddef.h>

int32_t sx126xBufferSetTxBuffer(sx126x_t* pContext, uint8_t address, uint8_t* pBuffer, uint8_t bufferLength) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && pBuffer != NULL) {
        retCode = pContext->writeBuffer(address, pBuffer, bufferLength);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xBufferGetRxBuffer(sx126x_t* pContext, uint8_t address, uint8_t* pBuffer, uint8_t bufferLength) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && pBuffer != NULL && bufferLength <= 256 - address) {
        retCode = pContext->readBuffer(address, pBuffer, bufferLength);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}