#include "boardStdio.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usbd_cdc_if.h"

#define boardStdioInputFifoBufferLength 200
uint8_t boardStdioInputFifoBuffer[boardStdioInputFifoBufferLength];
ring_buffer_t boardStdioInputFifoHandle;
// StreamBufferHandle_t boardStdioInputFifoHandle;

#define boardStdioOutputFifoBufferLength 200
uint8_t boardStdioOutputFifoBuffer[boardStdioOutputFifoBufferLength];
ring_buffer_t boardStdioOutputFifoHandle;
// StreamBufferHandle_t boardStdioOutputFifoHandle;

static void boardStdioFlushIn(void) {
  ring_buffer_initialize(&boardStdioInputFifoHandle, boardStdioInputFifoBuffer,
                         boardStdioInputFifoBufferLength);
  // xStreamBufferReset(boardStdioInputFifoHandle);
}

static void boardStdioFlushOut(void) {
  // uint8_t* flushBuffer = NULL;
  uint16_t length = 0;
  // int32_t flushLength =
  // xStreamBufferBytesAvailable(boardStdioOutputFifoHandle);

  if (ring_buffer_count(&boardStdioOutputFifoHandle) > 0) {
    // if (flushLength > 0) {
    uint8_t flushBuffer[10] = {0};
    // flushBuffer = pvPortMalloc(flushLength);

    memset(flushBuffer, 0, 10);

    do {
      // if (flushBuffer != NULL) {
      length = ring_buffer_read(&boardStdioOutputFifoHandle, flushBuffer, 10);
      // xStreamBufferReceive(stdioOutputFifoHandle, flushBuffer, flushLength,
      // portMAX_DELAY);

      CDC_Transmit_FS(flushBuffer, length);

      ring_buffer_remove(&boardStdioOutputFifoHandle, length);

      // vPortFree(flushBuffer);
    } while (length != 0);
    // }
  }
}

void boardStdioPutChar(char ch) {
  ring_buffer_push(&boardStdioOutputFifoHandle, (uint8_t *)&ch, 1);
  // xStreamBufferSend(boardStdioOutputFifoHandle, &ch, 1, portMAX_DELAY);
}

uint32_t boardStdioIsFull(void) {
  return (ring_buffer_length_remaining(&boardStdioOutputFifoHandle) == 0 ? 1
                                                                         : 0);
  // return (xStreamBufferIsFull(boardStdioOutputFifoHandle) == pdTRUE ? 1 : 0);
}

static void boardStdioPrint(char *pText, uint32_t textLength) {
  for (uint32_t i = 0; i < textLength; i++) {
    if (boardStdioIsFull() == 1) {
      boardStdioFlushOut();
    }
    boardStdioPutChar(pText[i]);
  }
}

void boardStdioFlush(void) {
  boardStdioFlushIn();
  boardStdioFlushOut();
}

char boardStdioGetChar(void) {
  uint8_t ch = 0;
  ring_buffer_read(&boardStdioInputFifoHandle, &ch, 1);
  ring_buffer_remove(&boardStdioInputFifoHandle, 1);
  // xStreamBufferReceive(boardStdioInputFifoHandle, &ch, 1, portMAX_DELAY);
  return ch;
}

uint32_t boardStdioIsAvaiable(void) {
  return (ring_buffer_count(&boardStdioInputFifoHandle) > 0 ? 1 : 0);
  // return xStreamBufferBytesAvailable(boardStdioInputFifoHandle);
}

int32_t boardStdioPrintf(const char *format, ...) {
  va_list args;
  va_start(args, format);

  uint8_t *printBuffer = NULL;

  int32_t printLength = vsnprintf(NULL, 0, format, args) + 1;

  printBuffer = malloc(printLength);
  if (printBuffer != NULL) {
    vsnprintf((char *)printBuffer, printLength, format, args);
    boardStdioPrint((char *)printBuffer, printLength - 1);
    boardStdioFlushOut();

    free(printBuffer);
  }

  return printLength;
}

int32_t boardStdioVPrintf(const char *format, va_list args) {
  uint8_t *vPrintBuffer = NULL;

  int32_t vPrintLength = vsnprintf(NULL, 0, format, args) + 1;

  vPrintBuffer = malloc(vPrintLength);

  if (vPrintBuffer != NULL) {
    vsnprintf((char *)vPrintBuffer, vPrintLength, format, args);
    boardStdioPrint((char *)vPrintBuffer, vPrintLength - 1);
    boardStdioFlushOut();

    free(vPrintBuffer);
  }

  return vPrintLength;
}

void boardStdioReset(void) {
  ring_buffer_initialize(&boardStdioInputFifoHandle, boardStdioInputFifoBuffer,
                         boardStdioInputFifoBufferLength);
  // xStreamBufferReset(boardStdioInputFifoHandle);
  ring_buffer_initialize(&boardStdioOutputFifoHandle,
                         boardStdioOutputFifoBuffer,
                         boardStdioOutputFifoBufferLength);
  // xStreamBufferReset(boardStdioOutputFifoHandle);
}

void boardStdioInit(void) {
  ring_buffer_initialize(&boardStdioInputFifoHandle, boardStdioInputFifoBuffer,
                         boardStdioInputFifoBufferLength);
  // boardStdioInputFifoHandle =
  // xStreamBufferCreate(boardStdioInputFifoBufferLength, 1);
  ring_buffer_initialize(&boardStdioOutputFifoHandle,
                         boardStdioOutputFifoBuffer,
                         boardStdioOutputFifoBufferLength);
  // boardStdioOutputFifoHandle =
  // xStreamBufferCreate(boardStdioOutputFifoBufferLength, 1);
}
