#include "video.h"
#include <dos.h>
#include <i86.h>

byte_t *VGA = (byte_t*)0xA0000L;

void set_mode(byte_t mode) {
    union REGS regs;
    regs.h.ah = 0x00;
    regs.h.al = mode;
    int386(0x10, &regs, &regs);
}