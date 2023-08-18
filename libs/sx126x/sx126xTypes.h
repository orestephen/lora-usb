#ifndef _SX126X_TYPES_H_
#define _SX126X_TYPES_H_

#include <stdint.h>

#define sx126xMaxBufferLength 0xFF

#define sx126xMaxSymbolNumberTimeout 248

#define sx126xMaxRetentionRegisters 4

#define sx126xTimeoutStep 64
#define sx126xTimeoutMax 262143
#define sx126xTimeoutContinuous 0xFFFFFF

#define sx126xCrcSeedIBM 0xFFFF
#define sx126xCrcSeedCCITT 0x1D0F
#define sx126xCrcPolyIBM 0x8005
#define sx126xCrcPolyCCITT 0x1021

#define sx126xStatusMaskChipMode 0x70
#define sx126xStatusMaskCmdStatus 0x0E
#define sx126xStatusShiftChipMode 4
#define sx126xStatusShiftCmdStatus 1

#define sx126xModeStdbyRc 2
#define sx126xModeStdbyXosc 3
#define sx126xModeFs 4
#define sx126xModeRx 5
#define sx126xModeTx 6

#define sx126xCmdStatusNone 0
#define sx126xCmdStatusDataAck 2
#define sx126xCmdStatusCmdTimeout 3
#define sx126xCmdStatusCmdProcError 4
#define sx126xCmdStatusCmdExcError 5
#define sx126xCmdStatusTxDone 6
#define sx126xCmdStatusAllError 7


#define sx126xSleepConfigMaskStart 4
#define sx126xSleepConfigMaskReset 2
#define sx126xSleepConfigMaskRtcTimeout 1
#define sx126xSleepConfigShiftStart 2
#define sx126xSleepConfigShiftReset 1
#define sx126xSleepConfigShiftRtcTimeout 0
typedef enum {
	sx126xSleepConfigStartCold = 0,
	sx126xSleepConfigStartWarm = 1,
} sx126xSleepConfigStart_t;
typedef enum {
	sx126xSleepConfigRtcTimeoutDisabled = 0,
	sx126xSleepConfigRtcTimeoutWake = 1,
} sx126xSleepConfigRtcTimeout_t;


typedef enum {
	sx126xStdbyConfigRc = 0,
	sx126xStdbyConfigXosc = 1,
} sx126xStdbyConfig_t;


typedef enum {
	sx126xStopTimerOnPreambleDisable = 0,
	sx126xStopTimerOnPreambleEnable = 1,
} sx126xStopTimerOnPreamble_t;


typedef enum {
	sx126xRegulatorModeLdo = 0,
	sx126xRegulatorModeDcDc = 1,
} sx126xRegulatorMode_t;


#define sx126xCalibrateMaskRc64k 0x01
#define sx126xCalibrateMaskRc13m 0x02
#define sx126xCalibrateMaskPll 0x04
#define sx126xCalibrateMaskAdcPulse 0x08
#define sx126xCalibrateMaskAdcBulkN 0x10
#define sx126xCalibrateMaskAdcBulkP 0x20
#define sx126xCalibrateMaskImage 0x40

#define sx126xCalibrateShiftRc64k 0
#define sx126xCalibrateShiftRc13m 1
#define sx126xCalibrateShiftPll 2
#define sx126xCalibrateShiftAdcPulse 3
#define sx126xCalibrateShiftAdcBulkN 4
#define sx126xCalibrateShiftAdcBulkP 5
#define sx126xCalibrateShiftImage 6

#define sx126xCalibrateRc64kDisable 0
#define sx126xCalibrateRc64kEnable 1
#define sx126xCalibrateRc13mDisable 0
#define sx126xCalibrateRc13mEnable 1
#define sx126xCalibratePllDisable 0
#define sx126xCalibratePllEnable 1
#define sx126xCalibrateAdcPulseDisable 0
#define sx126xCalibrateAdcPulseEnable 1
#define sx126xCalibrateAdcBulkNDisable 0
#define sx126xCalibrateAdcBulkNEnable 1
#define sx126xCalibrateAdcBulkPDisable 0
#define sx126xCalibrateAdcBulkPEnable 1
#define sx126xCalibrateImageDisable 0
#define sx126xCalibrateImageEnable 1


typedef enum {
	sx126xFallbackModeRc = 0x20,
	sx126xFallbackModeXosc = 0x30,
	sx126xFallbackModeFs = 0x40,
} sx126xFallbackMode_t;


#define sx126xIrqShiftTxDone 0
#define sx126xIrqShiftRxDone 1
#define sx126xIrqShiftPreambleDetected 2
#define sx126xIrqShiftSyncWordValid 3
#define sx126xIrqShiftHeaderValid 4
#define sx126xIrqShiftHeaderError 5
#define sx126xIrqShiftCrcError 6
#define sx126xIrqShiftCadDone 7
#define sx126xIrqShiftCadDetected 8
#define sx126xIrqShiftTimeout 9
// #define sx126xIrqShiftFhssHop 14

#define sx126xIrqMaskNone sx126xIrqShiftTxDone
#define sx126xIrqMaskTxDone (1 << sx126xIrqShiftTxDone)
#define sx126xIrqMaskRxDone (1 << sx126xIrqShiftRxDone)
#define sx126xIrqMaskPreambleDetected (1 << sx126xIrqShiftPreambleDetected)
#define sx126xIrqMaskSyncWordValid (1 << sx126xIrqShiftSyncWordValid)
#define sx126xIrqMaskHeaderValid (1 << sx126xIrqShiftHeaderValid)
#define sx126xIrqMaskHeaderError (1 << sx126xIrqShiftHeaderError)
#define sx126xIrqMaskCrcError (1 << sx126xIrqShiftCrcError)
#define sx126xIrqMaskCadDone (1 << sx126xIrqShiftCadDone)
#define sx126xIrqMaskCadDetected (1 << sx126xIrqShiftCadDetected)
#define sx126xIrqMaskTimeout (1 << sx126xIrqShiftTimeout)
// #define sx126xIrqMaskFhssHop (1 << sx126xIrqShiftFhssHop)
#define sx126xIrqMaskAll 0xFFFF


typedef enum {
	sx126xTcxoVoltage1V6,
	sx126xTcxoVoltage1V7,
	sx126xTcxoVoltage1V8,
	sx126xTcxoVoltage2V2,
	sx126xTcxoVoltage2V4,
	sx126xTcxoVoltage2V7,
	sx126xTcxoVoltage3V0,
	sx126xTcxoVoltage3V3,
} sx126xTcxoVoltage_t;


typedef enum {
	sx126xPacketFsk = 0,
	sx126xPacketLora = 1,
	// sx126xPacketFhss = 3,
} sx126xPacket_t;


typedef enum {
	sx126xRampTime10us,
	sx126xRampTime20us,
	sx126xRampTime40us,
	sx126xRampTime80us,
	sx126xRampTime200us,
	sx126xRampTime800us,
	sx126xRampTime1700us,
	sx126xRampTime3400us,
} sx126xRampTime_t;


typedef enum {
	sx126xFskPulseShapeOff = 0x00,
	sx126xFskPulseShapeBT03 = 0x08,
	sx126xFskPulseShapeBT05 = 0x09,
	sx126xFskPulseShapeBT07 = 0x0A,
	sx126xFskPulseShapeBT1 = 0x0B,
} sx126xFskPulseShape_t;

typedef enum {
	sx126xFskBW4800 = 0x1F,
	sx126xFskBW5800 = 0x17,
	sx126xFskBW7300 = 0x0F,
	sx126xFskBW9700 = 0x1E,
	sx126xFskBW11700 = 0x16,
	sx126xFskBW14600 = 0x0E,
	sx126xFskBW19500 = 0x1D,
	sx126xFskBW23400 = 0x15,
	sx126xFskBW29300 = 0x0D,
	sx126xFskBW39000 = 0x1C,
	sx126xFskBW46900 = 0x14,
	sx126xFskBW58600 = 0x0C,
	sx126xFskBW78200 = 0x1B,
	sx126xFskBW93800 = 0x13,
	sx126xFskBW117300 = 0x0B,
	sx126xFskBW156200 = 0x1A,
	sx126xFskBW187200 = 0x12,
	sx126xFskBW234300 = 0x0A,
	sx126xFskBW312000 = 0x19,
	sx126xFskBW373600 = 0x11,
	sx126xFskBW467000 = 0x09,
} sx126xFskBW_t;


typedef enum {
    sx126xLoraSF5 = 0x05,
    sx126xLoraSF6 = 0x06,
    sx126xLoraSF7 = 0x07,
    sx126xLoraSF8 = 0x08,
    sx126xLoraSF9 = 0x09,
    sx126xLoraSF10 = 0x0A,
    sx126xLoraSF11 = 0x0B,
    sx126xLoraSF12 = 0x0C,
} sx126xLoraSF_t;
typedef enum {
	sx126xLoraBW007 = 0x00,
	sx126xLoraBW010 = 0x08,
	sx126xLoraBW015 = 0x01,
	sx126xLoraBW020 = 0x09,
	sx126xLoraBW031 = 0x02,
	sx126xLoraBW041 = 0x0A,
	sx126xLoraBW062 = 0x03,
	sx126xLoraBW125 = 0x04,
	sx126xLoraBW250 = 0x05,
	sx126xLoraBW500 = 0x06,
} sx126xLoraBW_t;
typedef enum {
    sx126xLoraCR45 = 0x01,
    sx126xLoraCR46 = 0x02,
    sx126xLoraCR47 = 0x03,
    sx126xLoraCR48 = 0x04,
} sx126xLoraCR_t;
typedef enum {
	sx126xLoraLowDataRateOptimizeOff,
	sx126xLoraLowDataRateOptimizeOn,
} sx126xLoraLowDataRateOptimize_t;


struct _sx126xModulationParamsFskStruct {
	sx126xFskBW_t bandwidth;
	sx126xFskPulseShape_t pulseShape;
	uint32_t bitrate;
	uint32_t freqDevision;
};
typedef struct _sx126xModulationParamsFskStruct sx126xModulationParamsFsk_t;

struct _sx126xModulationParamsLoraStruct {
	sx126xLoraBW_t bandwidth;
	sx126xLoraSF_t spreadingFactor;
	sx126xLoraCR_t coderate;
	sx126xLoraLowDataRateOptimize_t lowDatarateOptimize;
};
typedef struct _sx126xModulationParamsLoraStruct sx126xModulationParamsLora_t;

struct _sx126xModulationParamsStruct {
	sx126xPacket_t packetType;
	union {
		sx126xModulationParamsFsk_t fsk;
		sx126xModulationParamsLora_t lora;
	} params;
};
typedef struct _sx126xModulationParamsStruct sx126xModulationParams_t;


typedef enum {
    sx126xFskPreambleDetectionOff = 0x00,
    sx126xFskPreambleDetection08Bits = 0x04,
    sx126xFskPreambleDetection16Bits = 0x05,
    sx126xFskPreambleDetection24Bits = 0x06,
    sx126xFskPreambleDetection32Bits = 0x07,
} sx126xFskPreambleDetection_t;
typedef enum {
	sx126xFskAddressCompareDisable = 0,
	sx126xFskAddressCompareNode = 1,
	sx126xFskAddressCompareNodeBroadCast = 2,
} sx126xFskAddressCompare_t;
typedef enum {
	sx126xFskHeaderTypeFixed = 0,
	sx126xFskHeaderTypeVariable = 1,
} sx126xFskHeaderType_t;
typedef enum {
	sx126xFskCrcOff = 0x01,
	sx126xFskCrc1Byte = 0x00,
	sx126xFskCrc2Byte = 0x02,
	sx126xFskCrc1ByteInvert = 0x04,
	sx126xFskCrc2ByteInvert = 0x06,
	sx126xFskCrc2ByteIBM = 0xF1,
	sx126xFskCrc2ByteCCIT = 0xF2,
} sx126xFskCrc_t;
typedef enum {
	sx126xFskWhiteningDisable = 0,
	sx126xFskWhiteningEnable = 1,
} sx126xFskWhitening_t;


typedef enum {
	sx126xLoraHeaderTypeVariable = 0x00,
	sx126xLoraHeaderTypeFixed = 0x01,
} sx126xLoraHeaderType_t;
typedef enum {
	sx126xLoraCrcOff = 0x00,
	sx126xLoraCrcOn = 0x01,
} sx126xLoraCrc_t;
typedef enum {
	sx126xLoraIqPolarityStandard = 0x00,
	sx126xLoraIqPolarityInverted = 0x01,
} sx126xLoraIqPolarity_t;


struct _sx126xPacketParamsFskStruct {
	uint16_t preambleLength;
	sx126xFskPreambleDetection_t preambleMinDetect;
	uint8_t syncwordLength;
	sx126xFskAddressCompare_t addressCompare;
	sx126xFskHeaderType_t headerType;
	uint8_t packetLength;
	sx126xFskCrc_t crcLength;
	sx126xFskWhitening_t whitening;
};
typedef struct _sx126xPacketParamsFskStruct sx126xPacketParamsFsk_t;

struct _sx126xPacketParamsLoraStruct {
	uint16_t preambleLength;
	sx126xLoraHeaderType_t headerType;
	uint8_t packetLength;
	sx126xLoraCrc_t crcMode;
	sx126xLoraIqPolarity_t iqPolarity;
};
typedef struct _sx126xPacketParamsLoraStruct sx126xPacketParamsLora_t;

struct _sx126xPacketParamsStruct {
	sx126xPacket_t packetType;
	union {
		sx126xPacketParamsFsk_t fsk;
		sx126xPacketParamsLora_t lora;
	} params;
};
typedef struct _sx126xPacketParamsStruct sx126xPacketParams_t;


#define sx126xCadSymbolNum1 0
#define sx126xCadSymbolNum2 1
#define sx126xCadSymbolNum4 2
#define sx126xCadSymbolNum8 3
#define sx126xCadSymbolNum16 4
#define sx126xCadExitModeOnly 0
#define sx126xCadExitModeRx 1


typedef enum {
	sx126xFskRxStatusMaskPacketSent = 0x01,
	sx126xFskRxStatusMaskPacketReceived = 0x02,
	sx126xFskRxStatusMaskAbortError = 0x04,
	sx126xFskRxStatusMaskLengthError = 0x08,
	sx126xFskRxStatusMaskCrcError = 0x10,
	sx126xFskRxStatusMaskAddressError = 0x020,
	sx126xFskRxStatusMaskSyncError = 0x40,
	sx126xFskRxStatusMaskPreambleError = 0x80,
} sx126xFskRxStatusMask_t;


#define sx126xOpErrorMaskRc64kCalError 0x001
#define sx126xOpErrorMaskRc13mCalError 0x002
#define sx126xOpErrorMaskPllCalError 0x004
#define sx126xOpErrorMaskAdcCalError 0x008
#define sx126xOpErrorMaskImageCalError 0x010
#define sx126xOpErrorMaskXoscStartError 0x020
#define sx126xOpErrorMaskPllLockError 0x040
#define sx126xOpErrorMaskPaRampError 0x100

#define sx126xOpErrorShiftRc64kCalError 0
#define sx126xOpErrorShiftRc13mCalError 1
#define sx126xOpErrorShiftPllCalError 2
#define sx126xOpErrorShiftAdcCalError 3
#define sx126xOpErrorShiftImageCalError 4
#define sx126xOpErrorShiftXoscStartError 5
#define sx126xOpErrorShiftPllLockError 6
#define sx126xOpErrorShiftPaRampError 8


struct _sx126xPacketStatusFskStruct {
	sx126xFskRxStatusMask_t rxStatus;
	int8_t rssiAvg;
	int8_t rssiSync;
};
typedef struct _sx126xPacketStatusFskStruct sx126xPacketStatusFsk_t;

struct _sx126xPacketStatusLoraStruct {
	int8_t rssiPeak;
	int8_t snrPeak;
	int8_t signalRssiPeak;
};
typedef struct _sx126xPacketStatusLoraStruct sx126xPacketStatusLora_t;

struct _sx126xPacketStatusStruct {
	sx126xPacket_t packetType;
	union {
		sx126xPacketStatusFsk_t fsk;
		sx126xPacketStatusLora_t lora;
	} params;
};
typedef struct _sx126xPacketStatusStruct sx126xPacketStatus_t;


#endif