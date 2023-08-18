#ifndef __SX126X_COMMAND_H__
#define __SX126X_COMMAND_H__

#include "sx126x.h"
#include "sx126xTypes.h"


#define sx126xOpcodeSetSleep 0x84
#define sx126xOpcodeSetStandby 0x80
#define sx126xOpcodeSetFs 0x81
#define sx126xOpcodeSetTx 0x83
#define sx126xOpcodeSetRx 0x82
#define sx126xOpcodeStopTimerOnPreamble 0x9F
#define sx126xOpcodeSetRxDutyCycle 0x94
#define sx126xOpcodeSetCad 0xC5
#define sx126xOpcodeSetTxContinuousWave 0xD1
#define sx126xOpcodeSetTxInfinitePreamble 0xD2
#define sx126xOpcodeSetRegulatorMode 0x96
#define sx126xOpcodeCalibrate 0x89
#define sx126xOpcodeCalibrateImage 0x98
#define sx126xOpcodeSetPaConfig 0x95
#define sx126xOpcodeSetRxTxFallbackMode 0x93
#define sx126xOpcodeWriteRegister 0x0D
#define sx126xOpcodeReadRegister 0x1D
#define sx126xOpcodeWriteBuffer 0x0E
#define sx126xOpcodeReadBuffer 0x1E
#define sx126xOpcodeSetDioIrqParams 0x08
#define sx126xOpcodeGetIrqStatus 0x12
#define sx126xOpcodeClearIrqStatus 0x02
#define sx126xOpcodeSetDio2RfSwitch 0x9D
#define sx126xOpcodeSetDio3TcxoControl 0x97
#define sx126xOpcodeSetRfFrequency 0x86
#define sx126xOpcodeSetPacketType 0x8A
#define sx126xOpcodeGetPacketType 0x11
#define sx126xOpcodeSetTxParams 0x8E
#define sx126xOpcodeSetModulationParams 0x8B
#define sx126xOpcodeSetPacketParams 0x8C
#define sx126xOpcodeSetCadParams 0x88
#define sx126xOpcodeSetBufferBaseAddress 0x8F
#define sx126xOpcodeSetLoraSymboNumTimeout 0xA0
#define sx126xOpcodeGetStatus 0xC0
#define sx126xOpcodeGetRssiInst 0x15
#define sx126xOpcodeGetRxBufferStatus 0x13
#define sx126xOpcodeGetPacketStatus 0x14
#define sx126xOpcodeGetDeviceErrors 0x17
#define sx126xOpcodeClearDeviceErrors 0x07
#define sx126xOpcodeGetStats 0x10
#define sx126xOpcodeResetStats 0x00

int32_t sx126xCommandSetSleep(sx126x_t* pContext, sx126xSleepConfigStart_t start, sx126xSleepConfigRtcTimeout_t rtc);
int32_t sx126xCommandSetStandby(sx126x_t* pContext, sx126xStdbyConfig_t config);
int32_t sx126xCommandSetFs(sx126x_t* pContext);
int32_t sx126xCommandSetTx(sx126x_t* pContext, uint32_t timeout);
int32_t sx126xCommandSetRx(sx126x_t* pContext, uint32_t timeout);
int32_t sx126xCommandSetStopRxTimerOnPreamble(sx126x_t* pContext, sx126xStopTimerOnPreamble_t enable);
int32_t sx126xCommandSetRxDutyCycle(sx126x_t* pContext, uint32_t rxTime, uint32_t sleepTime);
int32_t sx126xCommandSetCad(sx126x_t* pContext);
int32_t sx126xCommandSetTxContinuousWave(sx126x_t* pContext);
int32_t sx126xCommandSetTxContinuousPreamble(sx126x_t* pContext);
int32_t sx126xCommandSetRegulatorMode(sx126x_t* pContext, sx126xRegulatorMode_t mode);
int32_t sx126xCommandCalibrate(sx126x_t* pContext, uint8_t rc64k, uint8_t rc13m, uint8_t pll, uint8_t adcPulse, uint8_t adcBulkN, uint8_t adcBulkP, uint8_t image);
int32_t sx126xCommandCalibrateImage(sx126x_t* pContext, uint32_t frequency);
int32_t sx126xCommandSetPaConfig(sx126x_t* pContext, uint8_t paDutyCycle, uint8_t hpMax, uint8_t deviceSel, uint8_t paLut);
int32_t sx126xCommandSetRxTxFallbackMode(sx126x_t* pContext, sx126xFallbackMode_t mode);
int32_t sx126xCommandSetDioIrqParams(sx126x_t* pContext, uint16_t irqMask, uint16_t dio1Mask, uint16_t dio2Mask, uint16_t dio3Mask);
int32_t sx126xCommandGetIrqStatus(sx126x_t* pContext, uint16_t* irq);
int32_t sx126xCommandClearIrq(sx126x_t* pContext, uint16_t irq);
int32_t sx126xCommandSetDio2RfSwitch(sx126x_t* pContext, uint8_t enable);
int32_t sx126xCommandSetDio3TcxoCtrl(sx126x_t* pContext, sx126xTcxoVoltage_t tcxoVoltage, uint32_t timeout);
int32_t sx126xCommandSetRfFrequency(sx126x_t* pContext, uint32_t frequency);
int32_t sx126xCommandSetPacketType(sx126x_t* pContext, sx126xPacket_t packetType);
int32_t sx126xCommandGetPacketType(sx126x_t* pContext, sx126xPacket_t* packetType);
int32_t sx126xCommandSetTxParams(sx126x_t* pContext, int8_t power, sx126xRampTime_t rampTime);
int32_t sx126xCommandSetModulationParamsLora(sx126x_t* pContext, sx126xModulationParamsLora_t modulationParams);
int32_t sx126xCommandSetModulationParamsFsk(sx126x_t* pContext, sx126xModulationParamsFsk_t modulationParams);
int32_t sx126xCommandSetPacketParamsLora(sx126x_t* pContext, sx126xPacketParamsLora_t packetParams);
int32_t sx126xCommandSetPacketParamsFsk(sx126x_t* pContext, sx126xPacketParamsFsk_t packetParams);
int32_t sx126xCommandSetCadParams(sx126x_t* pContext, uint8_t symbolNum, uint8_t detPeak, uint8_t detMin, uint8_t exitMode, uint32_t timeout);
int32_t sx126xCommandSetBufferBaseAddress(sx126x_t* pContext, uint8_t txBaseAddress, uint8_t rxBaseAddress);
int32_t sx126xCommandSetSymbolTimeoutLora(sx126x_t* pContext, uint8_t symbolNumber);
int32_t sx126xCommandGetStatus(sx126x_t* pContext, uint8_t* commandStatus, uint8_t* chipMode);
int32_t sx126xCommandGetRssi(sx126x_t* pContext, int8_t* rssi);
int32_t sx126xCommandGetRxBufferStatus(sx126x_t* pContext, uint8_t* packetLength, uint8_t* packetStart);
int32_t sx126xCommandGetPacketStatusLora(sx126x_t* pContext, sx126xPacketStatusLora_t* packetStatus);
int32_t sx126xCommandGetPacketStatusFsk(sx126x_t* pContext, sx126xPacketStatusFsk_t* packetStatus);
int32_t sx126xCommandGetDeviceErrors(sx126x_t* pContext, uint16_t* error);
int32_t sx126xCommandClearDeviceErrors(sx126x_t* pContext);
int32_t sx126xCommandGetStatsLora(sx126x_t* pContext, uint16_t* received, uint16_t* crcError, uint16_t* headerError);
int32_t sx126xCommandGetStatsFsks(sx126x_t* pContext, uint16_t* received, uint16_t* crcError, uint16_t* lengthError);
int32_t sx126xCommandResetStats(sx126x_t* pContext);

#endif