#include "video.h"
#include <dos.h>
#include <i86.h>
#include <string.h>

byte_t *VGA = (byte_t*)0xA0000L;

void set_mode(byte_t mode) {
    union REGS regs;
    regs.h.ah = 0x00;
    regs.h.al = mode;
    int386(0x10, &regs, &regs);
}

void clear_screen(byte_t color)
{
    memset(VGA, color, MODE_013_ARRAY_SIZE);
}

VideoSystem::VideoSystem()
{
    set_mode(MODE_256_COLOR);
}

VideoSystem::~VideoSystem()
{
    set_mode(MODE_TEXT);
}

void VideoSystem::Draw(){
    clear_screen(mClearColor);
}
