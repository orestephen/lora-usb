#include "sx126xRegister.h"

#include <stddef.h>

#define sx126xMaxRetentionRegisters 4

int32_t sx126xRegisterGetRetentionAddress(sx126x_t* pContext, uint8_t slot, uint16_t* pAddress) {
    int32_t retCode = sx126xErrorNone;
    
    uint8_t data[2];
    
    if (pContext != NULL && slot < sx126xMaxRetentionRegisters) {
        data[0] = 0;
        data[1] = 0;

        retCode = pContext->readRegisters(sx126xRegisterRetentionList + 1 + (slot * 2), data, 2);
    } else {
        retCode = sx126xErrorContext;
    }

    if (retCode == sx126xErrorNone) {
        *pAddress = (data[0] << 8) | data[1];
    }

    return retCode;
}

int32_t sx126xRegisterSetRetentionAddress(sx126x_t* pContext, uint8_t slot, uint16_t address) {
    int32_t retCode = sx126xErrorNone;
    
    uint8_t data[3];

    if (pContext != NULL && slot < sx126xMaxRetentionRegisters) {
        data[0] = (uint8_t)((address >> 8) & 0xFF);
        data[1] = (uint8_t)(address & 0xFF);

        retCode = pContext->writeRegisters(sx126xRegisterRetentionList + 1 + (slot * 2), data, 2);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetRetentionCount(sx126x_t* pContext, uint8_t count) {
    int32_t retCode = sx126xErrorNone;
    
    if (pContext != NULL && count < sx126xMaxRetentionRegisters) {
        retCode = pContext->writeRegisters(sx126xRegisterRetentionList, &count, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetLoraSyncTimeout(sx126x_t* pContext, uint8_t timeout) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeRegisters(sx126xRegisterLoraSyncTimeout, &timeout, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetSyncwordLora(sx126x_t* pContext, uint16_t syncword) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[2];

        data[0] = (uint8_t)((syncword >> 8) & 0xFF);
        data[1] = (uint8_t)(syncword & 0xFF);

        if (retCode == sx126xErrorNone) {
            retCode = pContext->writeRegisters(sx126xRegisterLoraSyncWord, &data[0], 1);
        }

        if (retCode == sx126xErrorNone) {
            retCode = pContext->writeRegisters(sx126xRegisterLoraSyncWord + 1, &data[1], 1);
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetSyncwordFsk(sx126x_t* pContext, uint8_t* pSyncword, uint8_t syncwordLength) {
    int32_t retCode = sx126xErrorNone;
    uint8_t length = sx126xRegisterFskNodeAddress - sx126xRegisterFskSyncWord;

    if (pContext != NULL && pSyncword != NULL && syncwordLength == length) {
        retCode = pContext->writeRegisters(sx126xRegisterFskSyncWord, pSyncword, length);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetCrcSeedFsk(sx126x_t* pContext, uint16_t seed) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[2];

        data[0] = (uint8_t)((seed >> 8) & 0xFF);
        data[1] = (uint8_t)(seed & 0xFF);

        retCode = pContext->writeRegisters(sx126xRegisterFskCrcSeed, data, 2);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetCrcPolynomialFsk(sx126x_t* pContext, uint16_t polynomial) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[2];

        data[0] = (uint8_t)((polynomial >> 8) & 0xFF);
        data[1] = (uint8_t)(polynomial & 0xFF);

        retCode = pContext->writeRegisters(sx126xRegisterFskCrcPolynomial, data, 2);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetWhiteningSeedFsk(sx126x_t* pContext, uint16_t seed) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[2];

        data[0] = (uint8_t)((seed >> 8) & 0xFF);
        data[1] = (uint8_t)(seed & 0xFF);

        retCode = pContext->writeRegisters(sx126xRegisterFskWhiteningSeed, data, 2);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterGetTxModulation(sx126x_t* pContext, uint8_t* pModulation) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && pModulation != NULL) {
        *pModulation = 0;
        retCode = pContext->readRegisters(sx126xRegisterTxModulation, pModulation, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetTxModulation(sx126x_t* pContext, uint8_t modulation) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeRegisters(sx126xRegisterTxModulation, &modulation, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterGetTxClampConfig(sx126x_t* pContext, uint8_t* pClampConfig) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && pClampConfig != NULL) {
        *pClampConfig = 0;
        retCode = pContext->readRegisters(sx126xRegisterTxClampConfig, pClampConfig, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetTxClampConfig(sx126x_t* pContext, uint8_t clampConfig) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeRegisters(sx126xRegisterTxClampConfig, &clampConfig, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetRtcControl(sx126x_t* pContext, uint8_t control) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeRegisters(sx126xRegisterRtcControl, &control, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterGetEventMask(sx126x_t* pContext, uint8_t* pMask) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && pMask != NULL) {
        *pMask = 0;
        retCode = pContext->readRegisters(sx126xRegisterEventMask, pMask, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetEventMask(sx126x_t* pContext, uint8_t mask) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeRegisters(sx126xRegisterEventMask, &mask, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterGetIqPolarity(sx126x_t* pContext, uint8_t* pPolarity) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && pPolarity != NULL) {
        *pPolarity = 0;
        retCode = pContext->readRegisters(sx126xRegisterIqPolarity, pPolarity, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xRegisterSetIqPolarity(sx126x_t* pContext, uint8_t polarity) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeRegisters(sx126xRegisterIqPolarity, &polarity, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}