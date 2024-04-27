#define _M_IX86
#include "video.h"
#include <dos.h>
#include <i86.h>
#include <stdio.h>
#include <string.h>
#include "LOADPCX.H"
#include "GAMEOBJS.H"
#include <conio.h>
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
    Log("Set video mode to 13h\n");
    set_mode(MODE_256_COLOR);
}

VideoSystem::~VideoSystem()
{
    set_mode(MODE_TEXT);
}
/// @brief VGA uses 6 bits per color channel.
/// @param _8bits 
/// @return 
inline uint8_t from8BitsTo6Bits(uint8_t _8bits){
    float fx = ((float)_8bits) / 255.0f * 63.0f; 
    return (uint8_t)fx;
}

void VideoSystem::SetPalette(Color *table)
{
    for(int i=0; i<256; i++){
        outp(0x03c8, i);
        outp(0x03c9, from8BitsTo6Bits(table[i].r));
        outp(0x03c9, from8BitsTo6Bits(table[i].g));
        outp(0x03c9, from8BitsTo6Bits(table[i].b));
    }
}

void VideoSystem::ClearBuffer()
{
    clear_screen(mClearColor);
}


void VideoSystem::DrawImage(const Image& img, //what to draw 
        int16_t x, //where to draw
        int16_t y, //where to draw
        bool transparent //should I use the transparent code path?
        ){
    if((x < 0 && abs(x) > img.Width) || x >= MODE_013_WIDTH){
        //Image is fully outside in the horizontal axis - wont draw
        return;
    }
    if((y<0 && y < - img.Height) || y >= MODE_013_HEIGHT){
        //image is fully outside in the vertical axis - wont't draw.
        return;
    }
    //calculating the initial and final positions in the backbuffer
    int dstX0 = x;
    if(x<0) 
        dstX0 = 0;
    int dstXf = dstX0 + img.Width;
    if(x+img.Width > MODE_013_WIDTH)
        dstXf = MODE_013_WIDTH;
    int dstY0 = y;
    if(y<0)
        dstY0 = 0;
    int dstYf = dstY0 + img.Width;
    if(y + img.Height > MODE_013_HEIGHT)
        dstYf =  MODE_013_HEIGHT;
    //calculating the initial and final position in the image
    int srcX0=0 , srcXf=img.Width, srcY0=0, srcYf=img.Height;
    if(x < 0){
        srcX0 = x * -1;
    }
    if(y < 0){
        srcY0 = y * -1;
    }
    if(x+img.Width > MODE_013_WIDTH){
        srcXf = img.Width - (x+img.Width - MODE_013_WIDTH);
    }
    if(y+img.Height > MODE_013_HEIGHT){
        srcYf = img.Height - (y+img.Height - MODE_013_HEIGHT);
    }
    // Log("Dest: x[%d,%d],y[%d, %d]\n", dstX0, dstXf, dstY0, dstYf);
    // Log("Src: x[%d,%d],y[%d, %d]\n", srcX0, srcXf, srcY0, srcYf);
    //now that i have the ranges I can copy from the image to the backbuffer
    if(!transparent){
        //if it's not transparent i can just memcpy the scanlines into the backbuffer,
        //minding the ranges calculated above
        uint32_t sY=srcY0;
        uint32_t dIdx;
        for(uint32_t dY = dstY0; dY<dstY0+(srcYf-srcY0); dY++){
            dIdx = dY * MODE_013_WIDTH + dstX0;
            // Log("dY=%d, dIdx=%d\n, srcXf-srcX0",dY, dIdx, );
            memcpy(&backbuffer[dIdx], &img.Scanlines[sY][srcX0], srcXf -srcX0 );
            sY++;
        }  
    }else{
        //Can't use memcpy if using transparency because i must compare each pixel and only
        //write it isn't 0x00
        uint32_t sY=srcY0;
        for(uint32_t dY=dstY0; dY<dstY0+(srcYf-srcY0); dY++){
            uint32_t sX=srcX0;
            for(uint32_t dX=dstX0; dX<dstX0+(srcXf-srcX0); dX++){
                uint32_t dIdx = dY * MODE_013_WIDTH + dX;
                uint8_t srcPixel = img.Scanlines[sY][sX];
                if(srcPixel != 0x00)
                    backbuffer[dIdx] = srcPixel; 
                sX++;
            }
            sY++;
        }
    }
    
}

void VideoSystem::Present()
{
    memcpy(VGA, backbuffer, MODE_013_ARRAY_SIZE);
}
