#include "boardShell.h"

#include <stdint.h>
#include <stdlib.h>

#include "nucleo-f756zg.h"

#include "boardStdio.h"
#include "shell.h"

static const char *TAG = "ShellThread";

shellContext_t shell;

#define shellBufferLength 200
uint8_t shellBuffer[shellBufferLength];

shellProgram_t shellPrograms[10];
uint8_t shellProgramIndex = 0;

static int8_t boardShellAddProgram(char *pName,
                                   void (*pFunc)(shellContext_t *pContext,
                                                 int16_t argc, char **argv)) {
  int8_t retCode = 0;

  shellProgram_t *pProgram = &shellPrograms[shellProgramIndex];
  if (shellCreateProgram(pProgram, pName, pFunc) == 0) {
    retCode = shellAddProgram(&shell, pProgram);
    if (retCode == 0) {
      shellProgramIndex++;
    }
  }

  return retCode;
}

void testCommand(shellContext_t *pContext, int16_t argc, char **argv) {
  boardStdioPrintf("test:ok\r\n");
}

int8_t boardShellInit(void) {
  int8_t retCode = 0;

  shellInterface_t iface = {.putChar = boardStdioPutChar,
                            .getChar = boardStdioGetChar,
                            .flush = boardStdioFlush,
                            .print = boardStdioPrintf,
                            .isAvailable = boardStdioIsAvaiable};

  shellInit(&shell, iface, shellBuffer, shellBufferLength, 10);

  boardShellAddProgram("test", testCommand);

  return retCode;
}

void boardShellProcess(void) {

  if (shell.iface.isAvailable() > 0) {
    uint8_t ch = shell.iface.getChar();
    shellProcess(&shell, ch);
  }
}
