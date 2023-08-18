#include "sx126x.h"

#include "sx126xCommand.h"
#include "sx126xRegister.h"
#include "sx126xBuffer.h"

#include <stddef.h>

// see DS_SX1261-2_V1.2 datasheet chapter 15.1
static int32_t sx126xWorkaroundLoraModulationQuality(sx126x_t* pContext, sx126xLoraBW_t bandwidth) {
    int32_t retCode = sx126xErrorNone;
    uint8_t txModulation = 0;

    if (retCode == sx126xErrorNone) {
        retCode = sx126xRegisterGetTxModulation(pContext, &txModulation);
    }

    if (retCode == sx126xErrorNone) {
        if (bandwidth == sx126xLoraBW500) {
            txModulation = (txModulation & ~(1 << 2));
        } else {
            txModulation = (txModulation | (1 << 2));
        }
        retCode = sx126xRegisterSetTxModulation(pContext, txModulation);
    }

    return retCode;
}

// see DS_SX1261-2_V1.2 datasheet chapter 15.2
static int32_t sx126xWorkaroundTxClamp(sx126x_t* pContext) {
    int32_t retCode = sx126xErrorNone;
    uint8_t txClampConfig = 0;

    retCode = sx126xRegisterGetTxClampConfig(pContext, &txClampConfig);

    if (retCode == sx126xErrorNone) {
        txClampConfig |= (0x0F << 1);
        retCode = sx126xRegisterSetTxClampConfig(pContext, txClampConfig);
    }

    return retCode;
}

// see DS_SX1261-2_V1.2 datasheet chapter 15.3
static int32_t sx126xWorkaroundLoraImplicitHeaderTimeout(sx126x_t* pContext) {
    int32_t retCode = sx126xErrorNone;
    uint8_t eventMask = 0;

    retCode = sx126xRegisterSetRtcControl(pContext, 0);

    if (retCode == sx126xErrorNone) {
        retCode = sx126xRegisterGetEventMask(pContext, &eventMask);
    }

    if (retCode == sx126xErrorNone) {
        eventMask |= (1 << 1);
        retCode = sx126xRegisterSetEventMask(pContext, eventMask);
    }

    return retCode;
}

// see DS_SX1261-2_V1.2 datasheet chapter 15.4
static int32_t sx126xWorkaroundIqPolarity(sx126x_t* pContext, sx126xLoraIqPolarity_t iqPolarity) {
    int32_t retCode = sx126xErrorNone;
    uint8_t polarity = 0;

    retCode = sx126xRegisterGetIqPolarity(pContext, &polarity);

    if (retCode == sx126xErrorNone) {
        if (iqPolarity == sx126xLoraIqPolarityInverted) {
            polarity &= ~(1 << 2);
        } else {
            polarity |= (1 << 2);
        }

        retCode = sx126xRegisterSetIqPolarity(pContext, polarity);
    }

    return retCode;
}

static int32_t sx126xIsStatusError(uint8_t status) {
    int32_t retCode = sx126xErrorNone;

    uint8_t cmdStatus = ((status & sx126xStatusMaskCmdStatus) >> sx126xStatusShiftCmdStatus);
    // uint8_t modeStatus = ((status & sx126xStatusMaskChipMode) >> sx126xStatusShiftChipMode);

    switch(cmdStatus) {
        case sx126xCmdStatusAllError:
        case sx126xCmdStatusCmdProcError:
        case sx126xCmdStatusCmdExcError:
            retCode = sx126xErrorDevice;
            break;
        case sx126xCmdStatusCmdTimeout:
        case sx126xCmdStatusDataAck:
        case sx126xCmdStatusNone:
        case sx126xCmdStatusTxDone:
        default:
            break;
    }

    return retCode;
}

// TODO: need to test
static int32_t sx126xSetSymbolTimeoutLora(sx126x_t* pContext, uint8_t symbolNumber) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t mant = (((symbolNumber > sx126xMaxSymbolNumberTimeout) ? sx126xMaxSymbolNumberTimeout : symbolNumber) + 1) >> 1;
        uint8_t exp = 0;
        uint8_t reg = 0;

        while (mant > 31) {
            mant = (mant + 3) >> 2;
            exp++;
        }

        reg = mant << (2 * exp + 1);

        retCode = sx126xCommandSetSymbolTimeoutLora(pContext, reg);

        if (retCode == sx126xErrorNone) {
            if (symbolNumber != 0) {
                reg = exp + (mant << 3);
                retCode = sx126xRegisterSetLoraSyncTimeout(pContext, reg);
            }
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xGetPayloadLora(sx126x_t* pContext, uint8_t* pBuffer, uint8_t bufferLength) {
    int32_t retCode = sx126xErrorNone;

    uint8_t size;
    uint8_t offset;

    if (retCode == sx126xErrorNone) {
        retCode = sx126xWorkaroundLoraImplicitHeaderTimeout(pContext);
    }

    if (retCode == sx126xErrorNone) {
        retCode = sx126xCommandGetRxBufferStatus(pContext, &size, &offset);
        // TODO check that size is less than or equal to bufferlength
    }

    if (retCode == sx126xErrorNone) {
        if (bufferLength >= size) {
            // TODO check that size is less than or equal to bufferlength
            retCode = sx126xBufferGetRxBuffer(pContext, offset, pBuffer, size);

            if (retCode == sx126xErrorNone) {
                retCode = size;
            }
        } else {
            retCode = sx126xErrorNone;
        }
    }

    return retCode;
}

int32_t sx126xSetRfFrequency(sx126x_t* pContext, uint32_t frequency) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        if (pContext->calibrated == 0) {
            retCode = sx126xCommandCalibrateImage(pContext, frequency);
            if (retCode == sx126xErrorNone) {
                pContext->calibrated = 1;
            }
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetRfFrequency(pContext, frequency);
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xSetSyncword(sx126x_t* pContext, uint8_t syncword) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint16_t word = 0;
        
        word |= ((syncword & (0x0F << 4)) | 0x04) << 8;
        word |= (((syncword & 0x0F) << 4) | 0x04);

        retCode = sx126xRegisterSetSyncwordLora(pContext, word);
    }

    return retCode;
}

static uint32_t sx126xGetBandwidthHertzLora(sx126x_t* pContext) {
    uint32_t bandwidthHz = 0;

    switch(pContext->modulationParams.params.lora.bandwidth) {
        case sx126xLoraBW007:
            bandwidthHz = 7812UL;
            break;
        case sx126xLoraBW010:
            bandwidthHz = 10417UL;
            break;
        case sx126xLoraBW015:
            bandwidthHz = 15625UL;
            break;
        case sx126xLoraBW020:
            bandwidthHz = 20833UL;
            break;
        case sx126xLoraBW031:
            bandwidthHz = 31250UL;
            break;
        case sx126xLoraBW041:
            bandwidthHz = 41667UL;
            break;
        case sx126xLoraBW062:
            bandwidthHz = 62500UL;
            break;
        case sx126xLoraBW125:
            bandwidthHz = 125000UL;
            break;
        case sx126xLoraBW250:
            bandwidthHz = 250000UL;
            break;
        case sx126xLoraBW500:
            bandwidthHz = 500000UL;
            break;
    }

    return bandwidthHz;
}

int32_t sx126xGetTimeOnAirLora(sx126x_t* pContext, uint8_t payloadLength, uint32_t* airTime) {
    int32_t retCode = sx126xErrorNone;

    double begining;
    double middle;
    double ending;
    double nominator;
    double denominator;

    nominator = (8 * payloadLength) + (pContext->packetParams.params.lora.crcMode ? 16 : 0) - (pContext->modulationParams.params.lora.spreadingFactor * 4) + (pContext->packetParams.params.lora.headerType ? 0 : 20);

    if (pContext->modulationParams.params.lora.spreadingFactor <= 6) {
        nominator += 8;
        begining = 6.25;
    } else {
        begining = 4.25;
    }

    if (pContext->modulationParams.params.lora.lowDatarateOptimize == sx126xLoraLowDataRateOptimizeOn) {
        denominator = 4 * (pContext->modulationParams.params.lora.spreadingFactor - 2);
    } else {
        denominator = 4 * pContext->modulationParams.params.lora.spreadingFactor;
    }


    middle = (double)((pContext->packetParams.params.lora.preambleLength) + begining + 8 + (nominator/denominator) * (pContext->modulationParams.params.lora.coderate + 4));
    ending = (double)((1 << pContext->modulationParams.params.lora.spreadingFactor) / (double)(sx126xGetBandwidthHertzLora(pContext)));

    *airTime = (uint32_t)((double)(ending * 1000) * (double)(middle));
    
    return retCode;
}



// TODO move all register access to other file....
int32_t sx126xGetRandomNumber(sx126x_t* pContext, uint32_t* number) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        // uint8_t data[4];
        uint8_t regAnaLna = 0;
        uint8_t regAnaMixer = 0;
        uint8_t tempRegAnaLna = 0;
        uint8_t tempRegAnaMixer = 0;

        if (retCode == sx126xErrorNone) {
            retCode = pContext->readRegisters(sx126xRegisterAnaLna, &regAnaLna, 1);
        }

        if (retCode == sx126xErrorNone) {
            tempRegAnaLna = regAnaLna & ~(1 << 0);
            retCode = pContext->writeRegisters(sx126xRegisterAnaLna, &tempRegAnaLna, 1);
        }

        if (retCode == sx126xErrorNone) {
            retCode = pContext->readRegisters(sx126xRegisterAnaMixer, &regAnaMixer, 1);
        }

        if (retCode == sx126xErrorNone) {
            tempRegAnaMixer = regAnaMixer & ~(1 << 7);
            retCode = pContext->writeRegisters(sx126xRegisterAnaLna, &tempRegAnaMixer, 1);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetDioIrqParams(pContext, sx126xIrqMaskNone, sx126xIrqMaskNone, sx126xIrqMaskNone, sx126xIrqMaskNone);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetRx(pContext, sx126xTimeoutContinuous);
        }

        if (retCode == sx126xErrorNone) {
            retCode = pContext->readRegisters(sx126xRegisterRandomNumber, (uint8_t*)number, 4);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetStandby(pContext, sx126xStdbyConfigRc);
        }

        if (retCode == sx126xErrorNone) {
            retCode = pContext->writeRegisters(sx126xRegisterAnaLna, &regAnaLna, 1);
        }

        if (retCode == sx126xErrorNone) {
            retCode = pContext->writeRegisters(sx126xRegisterAnaLna, &regAnaMixer, 1);
        }

    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

static int32_t sx126xConfigLora(sx126x_t* pContext, uint32_t bandwidth, uint32_t datarate, uint8_t coderate, uint16_t preambleLength, uint8_t headerType, uint8_t payloadLength, uint8_t crcEnable, uint8_t iqInverted) {
    int32_t retCode = sx126xErrorNone;

    sx126xModulationParamsLora_t* modulationParams;
    sx126xPacketParamsLora_t* packetParams;

    modulationParams = &pContext->modulationParams.params.lora;
    packetParams = &pContext->packetParams.params.lora;

    pContext->modulationParams.packetType = sx126xPacketLora;

    modulationParams->spreadingFactor = (sx126xLoraSF_t) datarate;
    modulationParams->bandwidth = (sx126xLoraBW_t) bandwidth;
    modulationParams->coderate = (sx126xLoraCR_t) coderate;

    if (((modulationParams->bandwidth == sx126xLoraBW007) && ((modulationParams->spreadingFactor == sx126xLoraSF11) || (modulationParams->spreadingFactor == sx126xLoraSF12))) || ((modulationParams->bandwidth == sx126xLoraBW015) && (modulationParams->spreadingFactor == sx126xLoraSF12))) {
        modulationParams->lowDatarateOptimize = sx126xLoraLowDataRateOptimizeOn;
    } else {
        modulationParams->lowDatarateOptimize = sx126xLoraLowDataRateOptimizeOff;
    }

    pContext->packetParams.packetType = sx126xPacketLora;

    packetParams->headerType = headerType ? sx126xLoraHeaderTypeFixed : sx126xLoraHeaderTypeVariable;
    packetParams->crcMode = crcEnable ? sx126xLoraCrcOn : sx126xLoraCrcOff;
    packetParams->iqPolarity = iqInverted ? sx126xLoraIqPolarityInverted : sx126xLoraIqPolarityStandard;
    packetParams->packetLength = payloadLength;

    if ((modulationParams->spreadingFactor == sx126xLoraSF5 || modulationParams->spreadingFactor == sx126xLoraSF6) && preambleLength < 12) {
        packetParams->preambleLength = 12;
    } else {
        packetParams->preambleLength = preambleLength;
    }

    return retCode;
}

int32_t sx126xSetRxConfigLora(sx126x_t* pContext, uint32_t bandwidth, uint32_t spreadingFactor, uint8_t coderate, uint16_t preambleLength, uint16_t symbolTimeout, uint8_t headerType, uint8_t packetLength, uint8_t crcEnable, uint8_t iqInverted) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        if (retCode == sx126xErrorNone) {
            retCode = sx126xConfigLora(pContext, bandwidth, spreadingFactor, coderate, preambleLength, headerType, packetLength, crcEnable, iqInverted);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetPacketType(pContext, sx126xPacketLora);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetModulationParamsLora(pContext, pContext->modulationParams.params.lora);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetPacketParamsLora(pContext, pContext->packetParams.params.lora);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xSetSymbolTimeoutLora(pContext, symbolTimeout);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xWorkaroundIqPolarity(pContext, pContext->packetParams.params.lora.iqPolarity);
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xSetTxConfigLora(sx126x_t* pContext, uint32_t bandwidth, uint32_t spreadingFactor, uint8_t coderate, uint16_t preambleLength, uint8_t headerType, uint8_t packetLength, uint8_t crcEnable, uint8_t iqInverted) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        if (retCode == sx126xErrorNone) {
            retCode = sx126xConfigLora(pContext, bandwidth, spreadingFactor, coderate, preambleLength, headerType, packetLength, crcEnable, iqInverted);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetPacketType(pContext, sx126xPacketLora);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetModulationParamsLora(pContext, pContext->modulationParams.params.lora);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetPacketParamsLora(pContext, pContext->packetParams.params.lora);
        }
        
        if (retCode == sx126xErrorNone) {
            retCode = sx126xWorkaroundLoraModulationQuality(pContext, pContext->modulationParams.params.lora.bandwidth);
        }

    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx1261SetTxParams(sx126x_t* pContext, int8_t power, sx126xRampTime_t rampTime) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        if (power > 15) {
            power = 15;
        } else if (power < -17) {
            power = -17;
        }

        if (retCode == sx126xErrorNone) {
            if (power == 15) {
                power = 14;
                retCode = sx126xCommandSetPaConfig(pContext, 6, 0, 1, 1);
            } else {
                retCode = sx126xCommandSetPaConfig(pContext, 4, 0, 1, 1);
            }
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetTxParams(pContext, power, rampTime);
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx1262SetTxParams(sx126x_t* pContext, int8_t power, sx126xRampTime_t rampTime) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        if (power > 22) {
            power = 22;
        } else if (power < -9) {
            power = -9;
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xWorkaroundTxClamp(pContext);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetPaConfig(pContext, 4, 7, 0, 1);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetTxParams(pContext, power, rampTime);
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xStartTxLora(sx126x_t* pContext, uint8_t* pBuffer, uint8_t bufferLength, uint32_t timeout) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        if (timeout >= sx126xTimeoutMax) {
            timeout = sx126xTimeoutMax;
        } else {
            timeout = timeout * sx126xTimeoutStep;
        }

        if (retCode == sx126xErrorNone) {
            pContext->packetParams.params.lora.packetLength = bufferLength;
            retCode = sx126xCommandSetPacketParamsLora(pContext, pContext->packetParams.params.lora);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xBufferSetTxBuffer(pContext, 0, pBuffer, bufferLength);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetTx(pContext, timeout);
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xStartRxLora(sx126x_t* pContext, uint32_t timeout) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        if (timeout > sx126xTimeoutMax) {
            timeout = sx126xTimeoutContinuous;
        } else {
            timeout = timeout * sx126xTimeoutStep;
        }

        if (retCode == sx126xErrorNone) {
            pContext->packetParams.params.lora.packetLength = sx126xMaxBufferLength;
            retCode = sx126xCommandSetPacketParamsLora(pContext, pContext->packetParams.params.lora);
        }

        if (retCode == sx126xErrorNone) {
            retCode = sx126xCommandSetRx(pContext, timeout);
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}




















































































// int32_t sx126xGetRandomNumber(sx126x_t* pContext, uint32_t* number) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         // uint8_t data[4];
//         uint8_t regAnaLna = 0;
//         uint8_t regAnaMixer = 0;
//         uint8_t tempRegAnaLna = 0;
//         uint8_t tempRegAnaMixer = 0;

//         if (retCode == sx126xErrorNone) {
//             retCode = pContext->readRegisters(sx126xRegisterAnaLna, &regAnaLna, 1);
//         }

//         if (retCode == sx126xErrorNone) {
//             tempRegAnaLna = regAnaLna & ~(1 << 0);
//             retCode = pContext->writeRegisters(sx126xRegisterAnaLna, &tempRegAnaLna, 1);
//         }

//         if (retCode == sx126xErrorNone) {
//             retCode = pContext->readRegisters(sx126xRegisterAnaMixer, &regAnaMixer, 1);
//         }

//         if (retCode == sx126xErrorNone) {
//             tempRegAnaMixer = regAnaMixer & ~(1 << 7);
//             retCode = pContext->writeRegisters(sx126xRegisterAnaLna, &tempRegAnaMixer, 1);
//         }

//         if (retCode == sx126xErrorNone) {
//             retCode = sx126xSetRx(pContext, sx126xTimeoutContinuous);
//         }

//         if (retCode == sx126xErrorNone) {
//             retCode = pContext->readRegisters(sx126xRegisterRandomNumber, (uint8_t*)number, 4);
//         }

//         if (retCode == sx126xErrorNone) {
//             retCode = sx126xSetStandby(pContext, sx126xStdbyConfigRc);
//         }

//         if (retCode == sx126xErrorNone) {
//             retCode = pContext->writeRegisters(sx126xRegisterAnaLna, &regAnaLna, 1);
//         }

//         if (retCode == sx126xErrorNone) {
//             retCode = pContext->writeRegisters(sx126xRegisterAnaLna, &regAnaMixer, 1);
//         }

//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }





































































































// int32_t sx126xGetStatus(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //TODO
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xSetChannel(sx126x_t* pContext, uint32_t frequency) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         if (pContext->calibrated == 0) {
//             retCode = sx126xRadioCalibrateImage(pContext, frequency);
//             if (retCode == sx126xErrorNone) {
//                 pContext->calibrated = 1;
//             }
//         }
        
//         if (retCode == sx126xErrorNone) {
//             retCode = sx126xRadioSetRfFrequency(pContext, frequency);
//         }
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xSetSyncwordLora(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xSetSyncwordFsk(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xGetTimeOnAir(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xGetRandomNumber(sx126x_t* pContext, uint32_t* number) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xSetRxDutyCyle(sx126x_t* pContext, uint32_t rxTime, uint32_t sleetTime) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }



// int32_t sx126xSetRxConfigFsk(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xSetTxConfigLora(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xSetTxConfigFsk(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xStartTxLora(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xStartTxFsk(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xTxLora(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xTxFsk(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// static int32_t sx126xRxBoost(sx126x_t* pContext) {
//     return pContext->writeRegisters(sx126xRegisterRxGain, 0x96, 1);
// }

// static int32_t sx126xGetPacketLora(sx126x_t* pContext, uint8_t* pBuffer, uint8_t bufferLength, uint8_t* bytesCopied) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL && bytesCopied != NULL) {
//         uint8_t length = 0;
//         uint8_t start = 0;

//         if (retCode == sx126xErrorNone) {
//             retCode = sx126xRadioGetRxBufferStatus(pContext, &length, &start);
//         }

//         if (retCode == sx126xErrorNone) {
//             if (pContext->packetParams.params.lora.headerType == sx126xLoraHeaderTypeFixed) {
//                 pContext->readRegisters(sx126xRegisterLoraPayloadLength, &length, 1);
//             }
//         }

//         if (retCode == sx126xErrorNone) {
//             if (bufferLength >= length) {
//                 retCode = pContext->readBuffer(start, pBuffer, length);
//             }
//         }

//         if (retCode == sx126xErrorNone) {
//             *bytesCopied = length;
//         }
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// static int32_t sx126xGetPacketGfsk(sx126x_t* pContext, uint8_t* pBuffer, uint8_t bufferLength, uint8_t* bytesCopied) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL && bytesCopied != NULL) {
//         uint8_t length = 0;
//         uint8_t start = 0;

//         if (retCode == sx126xErrorNone) {
//             retCode = sx126xRadioGetRxBufferStatus(pContext, &length, &start);
//         }

//         if (retCode == sx126xErrorNone) {
//             if (bufferLength >= length) {
//                 retCode = pContext->readBuffer(start, pBuffer, length);
//             }
//         }

//         if (retCode == sx126xErrorNone) {
//             *bytesCopied = length;
//         }
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xStartRxLora(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         retCode = sx126xRxBoost(pContext);

//         if (retCode == sx126xErrorNone) {
//             //
//         }
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xStartRxFsk(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         retCode = sx126xRxBoost(pContext);

//         if (retCode == sx126xErrorNone) {
//             //
//         }
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xRxLora(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         retCode = sx126xRxBoost(pContext);

//         if (retCode == sx126xErrorNone) {
//             //
//         }
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xRxFsk(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         retCode = sx126xRxBoost(pContext);

//         if (retCode == sx126xErrorNone) {
//             //
//         }
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xStartCad(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xStartCw(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xStartModulated(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xGetRssi(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }

// int32_t sx126xIrqProcess(sx126x_t* pContext) {
//     int32_t retCode = sx126xErrorNone;

//     if (pContext != NULL) {
//         //
//     } else {
//         retCode = sx126xErrorContext;
//     }

//     return retCode;
// }
