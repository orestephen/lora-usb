#ifndef _shell_H_
#define _shell_H_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern const char* shellVersion;

struct _shellProgramStruct;
struct _shellContextStruct;

typedef struct _shellProgramStruct {
    char* pName;
    void (*pCommand)(struct _shellContextStruct* pContext, int16_t argc, char** argv);
    // void (*autocomplete)(struct _shellContextStruct* pContext);
    struct _shellProgramStruct* pNext;
} shellProgram_t;

typedef struct _shellInterfaceStruct {
    void (*putChar)(char ch);
    char (*getChar)(void);
    void (*flush)(void);
    uint32_t (*isAvailable)(void);
    int32_t(*print)(const char* format, ...);
} shellInterface_t;

typedef struct _shellContextStruct {
    char* pName;
    uint8_t* pBuffer;
    uint16_t bufferLength;
    uint16_t bufferOffset;
    uint8_t state;
    uint16_t cursorPosition;
    uint8_t argMax;
    shellProgram_t* pTable;
    shellInterface_t iface;
    void (*promptCallback)(void);
} shellContext_t;

int8_t shellProcess(shellContext_t* pContext, char ch);
int8_t shellCreateProgram(shellProgram_t* pProgram, char* pName, void (*pCommand)(shellContext_t* pContext, int16_t argc, char** argv));
int8_t shellAddProgram(shellContext_t* pContext, shellProgram_t* pProgram);
void shellParser(shellContext_t* pContext, uint8_t* cmd);
int8_t shellInit(shellContext_t* pContext, shellInterface_t iface, uint8_t* pBuffer, uint16_t bufferLength, uint8_t argMax);

#endif /*_shell_H_*/