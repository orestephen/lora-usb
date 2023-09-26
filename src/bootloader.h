#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__

#ifdef __cplusplus
extern "C" {
#endif

void bootloadSet(void);
void bootloadReset(void);
void bootloadCheck(void);

#ifdef __cplusplus
}
#endif

#endif
