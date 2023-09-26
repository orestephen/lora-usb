#include "shell.h"

#include "shellVt100.h"

#define stateNormal 0
#define stateEsc 1
#define stateEscSeq 2

#define LF 0x0A
#define CR 0x0D
#define TAB 0x09
#define SPACE 0x20
#define SPACE_STR " "
#define MIN 0x20
#define MAX 0x7E

#define cursorUp 1
#define cursorDown 2
#define cursorRight 3
#define cursorLeft 4

const char *shellVersion = "0.01.001";

int8_t shellCreateProgram(shellProgram_t *pProgram, char *pName,
                          void (*pCommand)(shellContext_t *pContext,
                                           int16_t argc, char **argv)) {
  int8_t retCode = 0;

  if (pProgram != NULL) {
    pProgram->pName = pName;
    pProgram->pCommand = pCommand;
    pProgram->pNext = NULL;
  } else {
    retCode = -1;
  }

  return retCode;
}

int8_t shellAddProgram(shellContext_t *pContext, shellProgram_t *pProgram) {
  int8_t retCode = 0;

  if (pContext != NULL) {

    if (pContext->pTable != NULL) {

      shellProgram_t *pTable = pContext->pTable;

      while (pTable->pNext != NULL) {
        pTable = pTable->pNext;
      }

      pTable->pNext = pProgram;

    } else {
      pContext->pTable = pProgram;
    }
  } else {
    retCode = -1;
  }

  return retCode;
}

// static uint32_t shellGetCursor(shellContext_t* pContext) {

// }

// static void shellUpdateCursor(shellContext_t* pContext, uint32_t direction) {
//     switch (direction) {
//         case cursorUp:
//             break;
//         case cursorDown:
//             break;
//         case cursorRight:
//             break;
//         case cursorLeft:
//             break;
//         default:
//             break;
//     }
// }

#ifdef SHELL_PROMT_ENABLE
static void shellPrintPrompt(shellContext_t *pContext) {
  if (pContext != NULL) {
    pContext->promptCallback();
  }
}
#endif

static void shellInsert(shellContext_t *pContext, uint8_t data) {
  if (pContext->bufferOffset < (pContext->bufferLength - 1)) {
    // buffer is not full

    // echo back
    pContext->iface.putChar(data);
    pContext->iface.flush();

    // store in buffer
    pContext->pBuffer[pContext->bufferOffset++] = data;

    // update cursor
    // pContext->iface.putChar(SHELL_VT100_ASCII_ESC);
    // pContext->iface.print("%c[%d;%dH", SHELL_VT100_ASCII_ESC, 1,
    // (uint8_t)pContext->bufferOffset); pContext->iface.putChar('[');
    // pContext->iface.putChar(1);
    // pContext->iface.putChar(';');
    // pContext->iface.putChar((uint8_t)pContext->bufferOffset);
    // pContext->iface.putChar('H');
    // pContext->iface.flush();
  } else {
    // buffer full, do nothing
  }
}

static void shellBackspace(shellContext_t *pContext) {
  if (pContext->bufferOffset > 0) {
    // buffer is not empty

    // remove from shell
    pContext->iface.putChar(SHELL_VT100_ASCII_BSPACE);
    pContext->iface.putChar(SPACE);
    pContext->iface.putChar(SHELL_VT100_ASCII_BSPACE);
    pContext->iface.flush();

    // removed from buffer
    pContext->bufferOffset--;
  } else {
    // buffer empty
  }
}

// static void shellDelete(shellContext_t* pContext) {

// }

void shellParser(shellContext_t *pContext, uint8_t *pCommand) {
  if (pContext != NULL) {
    int8_t retCode = -1;
    uint8_t argc = 0;
    char *argv[pContext->argMax];
    shellProgram_t *pProgram;

    argv[argc] = strtok((char *)pCommand, (char *)&SPACE_STR);

    do {
      argv[++argc] = strtok(NULL, (char *)&SPACE_STR);
    } while (argc < pContext->argMax && argv[argc] != NULL);

    for (pProgram = pContext->pTable; pProgram != NULL;
         pProgram = pProgram->pNext) {
      if (!strcmp(argv[0], pProgram->pName)) {
        pProgram->pCommand(pContext, argc, argv);
        retCode = 0;
      }
    }

    if (retCode != 0) {
      uint32_t commandLength = strlen(argv[0]);
      pContext->iface.print("%*s: command not found\r\n", commandLength,
                            argv[0]);
    }
  }
}

static void shellNewline(shellContext_t *pContext) {
  if (pContext->bufferOffset > 0) {
    // buffer contains something

    pContext->iface.putChar(CR);
    pContext->iface.putChar(LF);
    pContext->iface.flush();

    pContext->pBuffer[pContext->bufferOffset] = 0;
    shellParser(pContext, pContext->pBuffer);
  } else {
    // buffer empty
  }

  // reseting buffer.
  pContext->bufferOffset = 0;
  pContext->cursorPosition = 0;

#ifdef SHELL_PROMT_ENABLE
  shellPrintPrompt(pContext);
#endif
}

int8_t shellProcess(shellContext_t *pContext, char ch) {
  int8_t retCode = 0;

  if (pContext != NULL) {
    switch (pContext->state) {
    case stateNormal:
      switch (ch) {
      case SHELL_VT100_ASCII_ESC:
        pContext->state = stateEsc;
        break;
      case TAB:
        // todo autocomplete
        break;
      case SHELL_VT100_ASCII_BSPACE:
        shellBackspace(pContext);
        break;
      case SHELL_VT100_ASCII_DEL:
        break;
      default:
        if (ch == CR) {
          shellNewline(pContext);
        } else if (ch >= MIN && ch <= MAX) {
          shellInsert(pContext, (uint8_t)ch);
        } else {
          char string[7];
          int32_t retCode = snprintf(string, 7, "\\x%02X", ch);
          for (uint8_t i = 0; i < retCode; i++) {
            pContext->pBuffer[pContext->bufferOffset++] = string[i];
            pContext->iface.putChar(string[i]);
          }
          pContext->iface.flush();
        }
        break;
      }
      break;
    case stateEsc:
      // if (ch == '[') {
      //     pContext->state = stateEscSeq;
      // } else {
      //     pContext->state = stateNormal;
      // }
      break;
    case stateEscSeq:

      break;
    default:
      break;
    }
  } else {
    retCode = -1;
  }

  return retCode;
}

int8_t shellInit(shellContext_t *pContext, shellInterface_t iface,
                 uint8_t *pBuffer, uint16_t bufferLength, uint8_t argMax) {
  int8_t retCode = 0;

  if (pContext != NULL) {
    pContext->pTable = NULL;
    pContext->pBuffer = pBuffer;
    pContext->bufferLength = bufferLength;
    pContext->argMax = argMax;

    pContext->iface = iface;

#ifdef SHELL_PROMT_ENABLE
    shellPrintPrompt(pContext);
#endif
  } else {
    retCode = -1;
  }

  return retCode;
}
