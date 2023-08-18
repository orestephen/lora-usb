#ifndef __SX126X_H__
#define __SX126X_H__

#include "sx126xTypes.h"

#define sx126xErrorNone 0
#define sx126xErrorContext -1
#define sx126xErrorDevice -2
#define sx126xErrorBusy -4

struct _sx126xStruct {
    int32_t (*writeCommand)(uint8_t opcode, uint8_t* pData, uint8_t length);
    int32_t (*readCommand)(uint8_t opcode, uint8_t* pStatus, uint8_t* pData, uint8_t length);
    int32_t (*writeRegisters)(uint16_t address, uint8_t* pData, uint16_t length);
    int32_t (*readRegisters)(uint16_t address, uint8_t* pData, uint16_t length);
    int32_t (*writeBuffer)(uint8_t offset, uint8_t* pData, uint8_t length);
    int32_t (*readBuffer)(uint8_t offset, uint8_t* pData, uint16_t length);
	uint8_t calibrated;
	sx126xModulationParams_t modulationParams;
	sx126xPacketParams_t packetParams;
};
typedef struct _sx126xStruct sx126x_t;

// private functions
int32_t sx126xGetPayloadLora(sx126x_t* pContext, uint8_t* pBuffer, uint8_t bufferLength);

int32_t sx126xSetRfFrequency(sx126x_t* pContext, uint32_t frequency);
int32_t sx126xSetSyncword(sx126x_t* pContext, uint8_t syncword);
int32_t sx126xGetTimeOnAirLora(sx126x_t* pContext, uint8_t payloadLength, uint32_t* airTime);
int32_t sx126xGetRandomNumber(sx126x_t* pContext, uint32_t* number);
// int32_t sx126xSetRxDutyCyle(sx126x_t* pContext, uint32_t rxTime, uint32_t sleetTime);
int32_t sx126xSetRxConfigLora(sx126x_t* pContext, uint32_t bandwidth, uint32_t spreadingFactor, uint8_t coderate, uint16_t preambleLength, uint16_t symbolTimeout, uint8_t headerType, uint8_t packetLength, uint8_t crcEnable, uint8_t iqInverted);
// int32_t sx126xSetRxConfigFsk(sx126x_t* pContext);
int32_t sx126xSetTxConfigLora(sx126x_t* pContext, uint32_t bandwidth, uint32_t spreadingFactor, uint8_t coderate, uint16_t preambleLength, uint8_t headerType, uint8_t packetLength, uint8_t crcEnable, uint8_t iqInverted);
int32_t sx1261SetTxParams(sx126x_t* pContext, int8_t power, sx126xRampTime_t rampTime);
int32_t sx1262SetTxParams(sx126x_t* pContext, int8_t power, sx126xRampTime_t rampTime);
// int32_t sx126xSetTxConfigFsk(sx126x_t* pContext);
int32_t sx126xStartTxLora(sx126x_t* pContext, uint8_t* pBuffer, uint8_t bufferLength, uint32_t timeout);
// int32_t sx126xTx(sx126x_t* pContext, uint8_t* pBuffer, uint8_t bufferLength, uint32_t timeout);         // wait for done event
int32_t sx126xStartRxLora(sx126x_t* pContext, uint32_t timeout);
// int32_t sx126xRx(sx126x_t* pContext, uint8_t* pBuffer, uint8_t bufferLength, uint8_t* received, uint32_t timeout);         // wait for done event
// int32_t sx126xStartCad(sx126x_t* pContext);


#endif