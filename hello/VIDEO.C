#include "video.h"
#include <dos.h>
#include <i86.h>
#include <stdio.h>
#include <string.h>
#include "GAMEOBJS.H"
byte_t *VGA = (byte_t*)0xA0000L;

byte_t backbuffer[MODE_013_ARRAY_SIZE];

void set_mode(byte_t mode) {
    union REGS regs;
    regs.h.ah = 0x00;
    regs.h.al = mode;
    int386(0x10, &regs, &regs);
}

void clear_screen(byte_t color)
{
    memset(backbuffer, color, MODE_013_ARRAY_SIZE);
}

VideoSystem::VideoSystem()
{
    set_mode(MODE_256_COLOR);
}

VideoSystem::~VideoSystem()
{
    set_mode(MODE_TEXT);
}
void VideoSystem::SetDAC(uint8_t DAC, uint8_t r, uint8_t g, uint8_t b)
{
}
void VideoSystem::ClearBuffer()
{
    clear_screen(mClearColor);
}
void VideoSystem::Draw(const GameObject& obj){
    // uint16_t offsetInVideoMemory = MODE_013_WIDTH * obj.Y() + obj.X();
    // for(int x = 0; x<obj.mWidth; x++){
    //     for(int y = 0; y<obj.mHeight;y++){
    //         uint16_t offsetInVideoMemory = MODE_013_WIDTH * y + x;
    //         backbuffer[offsetInVideoMemory] = 5;
    //     }
    // }
    
/////    desenha mas tá errado na tela - ptos ao invés de contínuo    
    for(int i=0; i<obj.mWidth * obj.mHeight; i++){
        int imgX = i % obj.mWidth;
        int imgY = i / obj.mWidth;
        int positionInBuffer = MODE_013_WIDTH * (obj.Y() + imgY) + (obj.X() + imgX);
        if(obj.mImage[i] != 0)
            backbuffer[positionInBuffer] = obj.mImage[i];
    }
    Present();
}

void VideoSystem::Present()
{
    memcpy(VGA, backbuffer, MODE_013_ARRAY_SIZE);
}
