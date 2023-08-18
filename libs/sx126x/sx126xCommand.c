#include "sx126xCommand.h"

#include "sx126x.h"

#include <stddef.h>

#define sx126xCommandXtalFreq 32000000

static uint32_t sx126xCommandGetFreqInPllSteps(uint32_t frequency) {
    return (uint32_t)((double)frequency / (double)((double)sx126xCommandXtalFreq / (1 << 25)));
}

int32_t sx126xCommandSetSleep(sx126x_t* pContext, sx126xSleepConfigStart_t start, sx126xSleepConfigRtcTimeout_t rtc) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data = 0;
        
        data = ((uint8_t)start << sx126xSleepConfigShiftStart) | (sx126xSleepConfigMaskReset) | ((uint8_t)rtc << sx126xSleepConfigShiftRtcTimeout);

        if (start == sx126xSleepConfigStartCold) {
            pContext->calibrated = 0;
        }

        retCode = pContext->writeCommand(sx126xOpcodeSetSleep, &data, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetStandby(sx126x_t* pContext, sx126xStdbyConfig_t config) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeCommand(sx126xOpcodeSetStandby, (uint8_t*)&config, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetFs(sx126x_t* pContext) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeCommand(sx126xOpcodeSetFs, NULL, 0);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetTx(sx126x_t* pContext, uint32_t timeout) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[3];
        
        data[0] = (uint8_t)((timeout >> 16) & 0xFF);
        data[1] = (uint8_t)((timeout >> 8) & 0xFF);
        data[2] = (uint8_t)(timeout & 0xFF);

        retCode = pContext->writeCommand(sx126xOpcodeSetTx, data, 3);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetRx(sx126x_t* pContext, uint32_t timeout) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[3];

        data[0] = (uint8_t)((timeout >> 16) & 0xFF);
        data[1] = (uint8_t)((timeout >> 8) & 0xFF);
        data[2] = (uint8_t)(timeout & 0xFF);

        retCode = pContext->writeCommand(sx126xOpcodeSetRx, data, 3);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetStopRxTimerOnPreamble(sx126x_t* pContext, sx126xStopTimerOnPreamble_t enable) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeCommand(sx126xOpcodeStopTimerOnPreamble, (uint8_t*)&enable, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetRxDutyCycle(sx126x_t* pContext, uint32_t rxTime, uint32_t sleepTime) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[6];

        data[0] = (uint8_t)((rxTime >> 16) & 0xFF);
        data[1] = (uint8_t)((rxTime >> 8) & 0xFF);
        data[2] = (uint8_t)(rxTime & 0xFF);
        data[3] = (uint8_t)((sleepTime >> 16) & 0xFF);
        data[4] = (uint8_t)((sleepTime >> 8) & 0xFF);
        data[5] = (uint8_t)(sleepTime & 0xFF);

        retCode = pContext->writeCommand(sx126xOpcodeSetRxDutyCycle, data, 6);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetCad(sx126x_t* pContext) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeCommand(sx126xOpcodeSetCad, NULL, 0);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetTxContinuousWave(sx126x_t* pContext) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeCommand(sx126xOpcodeSetTxContinuousWave, NULL, 0);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetTxContinuousPreamble(sx126x_t* pContext) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeCommand(sx126xOpcodeSetTxInfinitePreamble, NULL, 0);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetRegulatorMode(sx126x_t* pContext, sx126xRegulatorMode_t mode) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeCommand(sx126xOpcodeSetRegulatorMode, (uint8_t*)&mode, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandCalibrate(sx126x_t* pContext, uint8_t rc64k, uint8_t rc13m, uint8_t pll, uint8_t adcPulse, uint8_t adcBulkN, uint8_t adcBulkP, uint8_t image) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data = 0;

        data = (rc64k << sx126xCalibrateShiftRc64k) |
                (rc13m << sx126xCalibrateShiftRc13m) |
                (pll << sx126xCalibrateShiftPll) |
                (adcPulse << sx126xCalibrateShiftAdcPulse) |
                (adcBulkN << sx126xCalibrateShiftAdcBulkN) |
                (adcBulkP << sx126xCalibrateShiftAdcBulkP) |
                (image << sx126xCalibrateShiftImage);

        retCode = pContext->writeCommand(sx126xOpcodeCalibrate, &data, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandCalibrateImage(sx126x_t* pContext, uint32_t frequency) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t index = 0;
        uint8_t imageCalibrationTable[5][2]  = {
            {0x6B, 0x6F},   //430-440Mhz
            {0x75, 0x81},   //470-510Mhz
            {0xC1, 0xC5},   //779-787Mhz
            {0xD7, 0xDB},   //863-870Mhz
            {0xE1, 0xE9},   //902-928Mhz
        };

        if (frequency > 460000000) {
            index++;
        }
        if (frequency > 770000000) {
            index++;
        }
        if (frequency > 850000000) {
            index++;
        }
        if (frequency > 900000000) {
            index++;
        }

        retCode = pContext->writeCommand(sx126xOpcodeCalibrateImage, imageCalibrationTable[index], 2);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetPaConfig(sx126x_t* pContext, uint8_t paDutyCycle, uint8_t hpMax, uint8_t deviceSel, uint8_t paLut) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[4];
        
        data[0] = paDutyCycle;
        data[1] = hpMax;
        data[2] = deviceSel;
        data[3] = paLut;

        retCode = pContext->writeCommand(sx126xOpcodeSetPaConfig, data, 4);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetRxTxFallbackMode(sx126x_t* pContext, sx126xFallbackMode_t mode) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeCommand(sx126xOpcodeSetRxTxFallbackMode, (uint8_t*)&mode, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetDioIrqParams(sx126x_t* pContext, uint16_t irqMask, uint16_t dio1Mask, uint16_t dio2Mask, uint16_t dio3Mask) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[8];

        data[0] = (uint8_t)((irqMask >> 8) & 0x00FF);
        data[1] = (uint8_t)(irqMask & 0x00FF);
        data[2] = (uint8_t)((dio1Mask >> 8) & 0x00FF);
        data[3] = (uint8_t)(dio1Mask & 0x00FF);
        data[4] = (uint8_t)((dio2Mask >> 8) & 0x00FF);
        data[5] = (uint8_t)(dio2Mask & 0x00FF);
        data[6] = (uint8_t)((dio3Mask >> 8) & 0x00FF);
        data[7] = (uint8_t)(dio3Mask & 0x00FF);

        retCode = pContext->writeCommand(sx126xOpcodeSetDioIrqParams, data, 8);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandGetIrqStatus(sx126x_t* pContext, uint16_t* irq) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && irq != NULL) {
        uint8_t status;
        uint8_t data[2];

        retCode = pContext->readCommand(sx126xOpcodeGetIrqStatus, &status , data, 2);

        if (retCode == sx126xErrorNone) {
            *irq = (data[0] << 8) | data[1];
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandClearIrq(sx126x_t* pContext, uint16_t irq) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[2];

        data[0] = (uint8_t)((irq >> 8) & 0x00FF);
        data[1] = (uint8_t)(irq & 0x00FF);

        retCode = pContext->writeCommand(sx126xOpcodeClearIrqStatus, data, 2);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetDio2RfSwitch(sx126x_t* pContext, uint8_t enable) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeCommand(sx126xOpcodeSetDio2RfSwitch, &enable, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetDio3TcxoCtrl(sx126x_t* pContext, sx126xTcxoVoltage_t tcxoVoltage, uint32_t timeout) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[4];

        data[0] = (uint8_t)tcxoVoltage & 0x07;
        data[1] = (uint8_t)((timeout >> 16) & 0xFF);
        data[2] = (uint8_t)((timeout >> 8) & 0xFF);
        data[3] = (uint8_t)(timeout & 0xFF);

        retCode = pContext->writeCommand(sx126xOpcodeSetDio3TcxoControl, data, 4);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetRfFrequency(sx126x_t* pContext, uint32_t frequency) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint32_t pllSteps = sx126xCommandGetFreqInPllSteps(frequency);
        uint8_t data[4];

        data[0] = (uint8_t)((pllSteps >> 24) & 0xFF);
        data[1] = (uint8_t)((pllSteps >> 16) & 0xFF);
        data[2] = (uint8_t)((pllSteps >> 8) & 0xFF);
        data[3] = (uint8_t)(pllSteps & 0xFF);

        if (retCode == sx126xErrorNone) {
            retCode = pContext->writeCommand(sx126xOpcodeSetRfFrequency, data, 4);
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetPacketType(sx126x_t* pContext, sx126xPacket_t packetType) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeCommand(sx126xOpcodeSetPacketType, (uint8_t*)&packetType, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandGetPacketType(sx126x_t* pContext, sx126xPacket_t* packetType) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && packetType != NULL) {
        uint8_t status;

        retCode = pContext->readCommand(sx126xOpcodeGetPacketType, &status , (uint8_t*)packetType, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetTxParams(sx126x_t* pContext, int8_t power, sx126xRampTime_t rampTime) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[2];

        data[0] = power;
        data[1] = (uint8_t)rampTime;

        retCode = pContext->writeCommand(sx126xOpcodeSetTxParams, data, 2);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetModulationParamsLora(sx126x_t* pContext, sx126xModulationParamsLora_t modulationParams) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[4];

        data[0] = modulationParams.spreadingFactor;
        data[1] = modulationParams.bandwidth;
        data[2] = modulationParams.coderate;
        data[3] = modulationParams.lowDatarateOptimize;

        retCode = pContext->writeCommand(sx126xOpcodeSetModulationParams, data, 4);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetModulationParamsFsk(sx126x_t* pContext, sx126xModulationParamsFsk_t modulationParams) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint32_t temp;
        uint8_t data[8];

        temp = (uint32_t) (32 * sx126xCommandXtalFreq) / modulationParams.bitrate;

        data[0] = (uint8_t)((temp >> 16) & 0xFF);
        data[1] = (uint8_t)((temp >> 8) & 0xFF);
        data[2] = (uint8_t)(temp & 0xFF);
        data[3] = modulationParams.pulseShape;
        data[4] = modulationParams.bandwidth;

        temp = sx126xCommandGetFreqInPllSteps(modulationParams.freqDevision);
        data[5] = (uint8_t)((temp >> 16) & 0xFF);
        data[6] = (uint8_t)((temp >> 8) & 0xFF);
        data[7] = (uint8_t)(temp & 0xFF);

        retCode = pContext->writeCommand(sx126xOpcodeSetModulationParams, data, 8);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetPacketParamsLora(sx126x_t* pContext, sx126xPacketParamsLora_t packetParams) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[6];

        data[0] = (uint8_t)((packetParams.preambleLength >> 8) & 0xFF);
        data[1] = (uint8_t)(packetParams.preambleLength & 0xFF);
        data[2] = (uint8_t)packetParams.headerType;
        data[3] = (uint8_t)packetParams.packetLength;
        data[4] = (uint8_t)packetParams.crcMode;
        data[5] = (uint8_t)packetParams.iqPolarity;

        retCode = pContext->writeCommand(sx126xOpcodeSetPacketParams, data, 6);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetPacketParamsFsk(sx126x_t* pContext, sx126xPacketParamsFsk_t packetParams) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[9];

        data[0] = (uint8_t)((packetParams.preambleLength >> 8) & 0xFF);
        data[1] = (uint8_t)(packetParams.preambleLength & 0xFF);
        data[2] = (uint8_t)packetParams.preambleMinDetect;
        data[3] = (uint8_t)packetParams.syncwordLength;
        data[4] = (uint8_t)packetParams.addressCompare;
        data[5] = (uint8_t)packetParams.headerType;
        data[6] = (uint8_t)packetParams.packetLength;
        data[7] = (uint8_t)packetParams.crcLength;
        data[8] = (uint8_t)packetParams.whitening;

        retCode = pContext->writeCommand(sx126xOpcodeSetPacketParams, data, 9);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetCadParams(sx126x_t* pContext, uint8_t symbolNum, uint8_t detPeak, uint8_t detMin, uint8_t exitMode, uint32_t timeout) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[7];

        data[0] = symbolNum;
        data[1] = detPeak;
        data[2] = detMin;
        data[3] = exitMode;
        data[4] = (uint8_t)((timeout >> 16) & 0xFF);
        data[5] = (uint8_t)((timeout >> 8) & 0xFF);
        data[6] = (uint8_t)(timeout & 0xFF);
        
        retCode = pContext->writeCommand(sx126xOpcodeSetCadParams, data, 7);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetBufferBaseAddress(sx126x_t* pContext, uint8_t txBaseAddress, uint8_t rxBaseAddress) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[2];

        data[0] = txBaseAddress;
        data[1] = rxBaseAddress;

        retCode = pContext->writeCommand(sx126xOpcodeSetBufferBaseAddress, data, 2);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandSetSymbolTimeoutLora(sx126x_t* pContext, uint8_t symbolNumber) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        retCode = pContext->writeCommand(sx126xOpcodeSetLoraSymboNumTimeout, &symbolNumber, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandGetStatus(sx126x_t* pContext, uint8_t* commandStatus, uint8_t* chipMode) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && commandStatus != NULL && chipMode != NULL) {
        uint8_t status;

        retCode = pContext->readCommand(sx126xOpcodeGetStatus, &status ,NULL, 0);

        if (retCode == sx126xErrorNone) {
            *commandStatus = ((status & sx126xStatusMaskCmdStatus) >> sx126xStatusShiftCmdStatus);
            *chipMode = ((status & sx126xStatusMaskChipMode) >> sx126xStatusShiftChipMode);
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandGetRssi(sx126x_t* pContext, int8_t* rssi) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && rssi != NULL) {
        uint8_t status;
        uint8_t data;

        retCode = pContext->readCommand(sx126xOpcodeGetRssiInst, &status, &data, 1);

        if (retCode == sx126xErrorNone) {
            *rssi = -data >> 1;
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandGetRxBufferStatus(sx126x_t* pContext, uint8_t* packetLength, uint8_t* packetStart) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && packetLength != NULL && packetStart != NULL) {
        uint8_t status = 0;
        uint8_t data[2] = {0};

        retCode = pContext->readCommand(sx126xOpcodeGetRxBufferStatus, &status, data, 2);

        if (retCode == sx126xErrorNone) {
            *packetLength = data[0];
            *packetStart = data[1];
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandGetPacketStatusLora(sx126x_t* pContext, sx126xPacketStatusLora_t* packetStatus) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && packetStatus != NULL) {
        uint8_t status;
        uint8_t data[3];

        retCode = pContext->readCommand(sx126xOpcodeGetPacketStatus, &status, data, 3);

        if (retCode == sx126xErrorNone) {
            packetStatus->rssiPeak = -data[0] >> 1;
            packetStatus->snrPeak = (((int8_t)data[1]) + 2) >> 2;
            packetStatus->signalRssiPeak = -data[2] >> 1;
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandGetPacketStatusFsk(sx126x_t* pContext, sx126xPacketStatusFsk_t* packetStatus) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && packetStatus != NULL) {
        uint8_t status;
        uint8_t data[3];

        retCode = pContext->readCommand(sx126xOpcodeGetPacketStatus, &status, data, 3);

        if (retCode == sx126xErrorNone) {
            packetStatus->rxStatus = data[0];
            packetStatus->rssiSync = -data[1] >> 1;
            packetStatus->rssiAvg = -data[2] >> 1;
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandGetDeviceErrors(sx126x_t* pContext, uint16_t* error) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL && error != NULL) {
        uint8_t status;
        uint8_t data[2];

        retCode = pContext->readCommand(sx126xOpcodeGetDeviceErrors, &status, data, 2);

        if (retCode == sx126xErrorNone) {
            *error = (data[0] << 8) | data[1];
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandClearDeviceErrors(sx126x_t* pContext) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[2];

        data[0] = 0;
        data[1] = 0;

        retCode = pContext->writeCommand(sx126xOpcodeClearDeviceErrors, data, 2);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandGetStatsLora(sx126x_t* pContext, uint16_t* received, uint16_t* crcError, uint16_t* headerError) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[6];

        retCode = pContext->writeCommand(sx126xOpcodeGetStats, data, 6);

        if (retCode == sx126xErrorNone) {
            *received = (data[0] << 8) | data[1];
            *crcError = (data[2] << 8) | data[3];
            *headerError = (data[4] << 8) | data[5];
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandGetStatsFsk(sx126x_t* pContext, uint16_t* received, uint16_t* crcError, uint16_t* lengthError) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data[6];

        retCode = pContext->writeCommand(sx126xOpcodeGetStats, data, 6);

        if (retCode == sx126xErrorNone) {
            *received = (data[0] << 8) | data[1];
            *crcError = (data[2] << 8) | data[3];
            *lengthError = (data[4] << 8) | data[5];
        }
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}

int32_t sx126xCommandResetStats(sx126x_t* pContext) {
    int32_t retCode = sx126xErrorNone;

    if (pContext != NULL) {
        uint8_t data = 0;

        retCode = pContext->writeCommand(sx126xOpcodeResetStats, &data, 1);
    } else {
        retCode = sx126xErrorContext;
    }

    return retCode;
}