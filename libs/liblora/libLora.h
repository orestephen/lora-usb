#ifndef __LIB_LORA_H__
#define __LIB_LORA_H__

#include <stdint.h>

#define libLoraErrorNone 0

struct _libLoraNodeCallbacksStruct {
    void (*txDone)(void);
    void (*rxDone)(uint8_t* payload, uint8_t size, int8_t rssi, int8_t snr);
    void (*timeout)(void);
    void (*rxError)(void);
    void (*cadDone)(uint8_t channelActivityDetected);
};
typedef struct _libLoraNodeCallbacksStruct libLoraNodeCallbacks_t;


struct _libLoraNodeContextStruct {
    int32_t (*init)(void);
    int32_t (*reset)(void);
    int32_t (*wakeup)(void);
    int32_t (*sleep)(void);
    int32_t (*standby)(void);
    int32_t (*configRx)(uint32_t bandwidth, uint32_t datarate, uint8_t coderate, uint32_t bandwidthAfc, uint16_t preambleLength, uint16_t symbTimeout, uint8_t headerType, uint8_t payloadLength, uint8_t crcEnable, uint8_t freqHopOn, uint8_t hopPeriod, uint8_t iqInverted);
    int32_t (*configTx)(int8_t power, uint32_t fdev, uint32_t bandwidth, uint32_t datarate, uint8_t coderate, uint16_t preambleLength, uint8_t headerType, uint8_t crcEnable, uint8_t freqHopOn, uint8_t hopPeriod, uint8_t iqInverted);
    int32_t (*setChannel)(uint32_t frequency);
    int32_t (*setSyncword)(uint8_t syncword);
    int32_t (*startRx)(uint32_t timeout);
    int32_t (*startTx)(uint8_t* pBuffer, uint8_t bufferLength, uint32_t timeout);
    int32_t (*rx)(uint8_t* pBuffer, uint8_t bufferLength, uint8_t* pRecieved, uint32_t timeout);
    int32_t (*tx)(uint8_t* pBuffer, uint8_t bufferLength, uint32_t timeout);
    int32_t (*startCad)(uint8_t symbolNumber, uint8_t detectPeak, uint8_t detectMin, uint8_t exitMode, uint32_t timeout);
    int32_t (*getTimeOnAir)(uint8_t packetLength, uint32_t* airTime);
    int32_t (*getRandomNumber)(uint32_t* number);
    int32_t (*getRssi)(int16_t* rRssi);
    int32_t (*startCw)(uint32_t frequency, int8_t power);
    int32_t (*startModulatedCw)(uint32_t frequency, int8_t power);
    int32_t (*irqProcess)(void);
};
typedef struct _libLoraNodeContextStruct libLoraNodeContext_t;

#endif