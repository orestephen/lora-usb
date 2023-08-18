#ifndef __SX126X_RADIO_H__
#define __SX126X_RADIO_H__

#include "sx126x.h"

// #define sx126xRegisterFhssHoppingEnable 0x0285
// #define sx126xRegisterFhss
#define sx126xRegisterRetentionList 0x029F
#define sx126xRegisterDioxOutputEnable 0x0580
#define sx126xRegisterDioxInputEnable 0x0583
#define sx126xRegisterDioxPullupControl 0x0584
#define sx126xRegisterDioxPulldownControl 0x0585
#define sx126xRegisterFskWhiteningSeed 0x06B8
#define sx126xRegisterFskCrcSeed 0x06BC
#define sx126xRegisterFskCrcPolynomial 0x06BE
#define sx126xRegisterFskSyncWord 0x06C0
#define sx126xRegisterFskNodeAddress 0x06CD
#define sx126xRegisterFskBroadcastAddress 0x06CE
#define sx126xRegisterLoraPacketParams 0x0704
#define sx126xRegisterLoraPayloadLength 0x0702
#define sx126xRegisterLoraSyncTimeout 0x0706
#define sx126xRegisterIqPolarity 0x0736
#define sx126xRegisterLoraSyncWord 0x0740
#define sx126xRegisterRandomNumber 0x0819
#define sx126xRegisterTxModulation 0x0889
#define sx126xRegisterRxGain 0x08AC
#define sx126xRegisterTxClampConfig 0x08D8
#define sx126xRegisterAnaLna 0x08E2
#define sx126xRegisterAnaMixer 0x08E5
#define sx126xRegisterOcpConfig 0x08E7
#define sx126xRegisterRtcControl 0x0902
#define sx126xRegisterXtaTrim 0x0911
#define sx126xRegisterXtbTrim 0x0912
#define sx126xRegisterDioOutVolts 0x0920
#define sx126xRegisterEventMask 0x0944

int32_t sx126xRegisterSetLoraSyncTimeout(sx126x_t* pContext, uint8_t timeout);
int32_t sx126xRegisterGetRetentionAddress(sx126x_t* pContext, uint8_t slot, uint16_t* pAddress);
int32_t sx126xRegisterSetRetentionAddress(sx126x_t* pContext, uint8_t slot, uint16_t address);
int32_t sx126xRegisterSetRetentionCount(sx126x_t* pContext, uint8_t count);
int32_t sx126xRegisterSetSyncwordLora(sx126x_t* pContext, uint16_t syncword);
int32_t sx126xRegisterSetSyncwordFsk(sx126x_t* pContext, uint8_t* pSyncword, uint8_t syncwordLength);
int32_t sx126xRegisterSetCrcSeedFsk(sx126x_t* pContext, uint16_t seed);
int32_t sx126xRegisterSetCrcPolynomialFsk(sx126x_t* pContext, uint16_t polynomial);
int32_t sx126xRegisterSetWhiteningSeedFsk(sx126x_t* pContext, uint16_t seed);
int32_t sx126xRegisterGetTxModulation(sx126x_t* pContext, uint8_t* pModulation);
int32_t sx126xRegisterSetTxModulation(sx126x_t* pContext, uint8_t modulation);
int32_t sx126xRegisterGetTxClampConfig(sx126x_t* pContext, uint8_t* pClampConfig);
int32_t sx126xRegisterSetTxClampConfig(sx126x_t* pContext, uint8_t clampConfig);
int32_t sx126xRegisterSetRtcControl(sx126x_t* pContext, uint8_t control);
int32_t sx126xRegisterGetEventMask(sx126x_t* pContext, uint8_t* pMask);
int32_t sx126xRegisterSetEventMask(sx126x_t* pContext, uint8_t mask);
int32_t sx126xRegisterGetIqPolarity(sx126x_t* pContext, uint8_t* pPolarity);
int32_t sx126xRegisterSetIqPolarity(sx126x_t* pContext, uint8_t polarity);

#endif