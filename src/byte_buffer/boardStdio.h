#ifndef __BOARD_STDIO_H__
#define __BOARD_STDIO_H__

#include <stdarg.h>
#include <stdint.h>

#include "ring_buffer.h"

extern ring_buffer_t boardStdioInputFifoHandle;

uint32_t boardStdioIsAvaiable(void);
uint32_t boardStdioIsFull(void);
char boardStdioGetChar(void);
void boardStdioPutChar(char ch);
void boardStdioFlush(void);
// void boardStdioFlushIn(void);
// void boardStdioFlushOut(void);
int32_t boardStdioPrintf(const char *format, ...);
int32_t boardStdioVPrintf(const char *format, va_list args);
void boardStdioReset(void);
void boardStdioInit(void);

#endif
