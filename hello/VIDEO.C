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

void VideoSystem::SetPalette(Color *table)
{
    for(uint8_t i=0; i<255; i++){
        outp(0x03c8, i);
        outp(0x03c9, table[i].r);
        outp(0x03c9, table[i].g);
        outp(0x03c9, table[i].b);
    }
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
    Log("Dest: x[%d,%d],y[%d, %d]\n", dstX0, dstXf, dstY0, dstYf);
    Log("Src: x[%d,%d],y[%d, %d]\n", srcX0, srcXf, srcY0, srcYf);
    //now that i have the ranges I can copy from the image to the backbuffer
    uint32_t sY=srcY0;
    for(uint32_t dY=dstY0; dY<dstY0+(srcYf-srcY0); dY++){
        uint32_t sX=srcX0;
        for(uint32_t dX=dstX0; dX<dstX0+(srcXf-srcX0); dX++){
            uint32_t dIdx = dY * MODE_013_WIDTH + dX;
            backbuffer[dIdx] = img.Scanlines[sY][sX];
            sX++;
        }
        sY++;
    }

    //now that i know that i have to draw the image, I have to calculate
    //the x and y range in the origin (in the image) and in the 
    //destination (in the backbuffer)
    // int16_t srcX0 = 0;
    // if(x < 0){
    //     srcX0 = img.Width - (img.Width + x);
    // }
    // int16_t srcY0 = 0;
    // if(y < 0){
    //     srcY0 = img.Height -(img.Height + y);
    // }
    // int16_t srcXf = img.Width;
    // if(x >= MODE_013_WIDTH - img.Width){
    //     srcXf = img.Width - (x + img.Width - MODE_013_WIDTH);
    // }
    // int16_t srcYf = img.Height;
    // if(x >= MODE_013_HEIGHT - img.Height){
    //     srcYf = img.Height - (y + img.Height - MODE_013_HEIGHT);
    // }
    // Log("src x0=%d xf=%d y0=%d yf=%d\n", srcX0, srcXf, srcY0, srcYf);
    // int16_t destX0 = x;
    // if(x<0){
    //     destX0 = 0;
    // }
    // int16_t destY0 = y;
    // if(y<0){
    //     destY0 = 0;
    // }
    // int16_t destXf = x + img.Width;
    // if(destXf > MODE_013_WIDTH){
    //     destXf = MODE_013_WIDTH;
    // }
    // int16_t destYf = y + img.Height;
    // if(destYf > MODE_013_HEIGHT){
    //     destYf = MODE_013_HEIGHT;
    // }
    // int destY = destY0;
    // for(int srcy = srcY0; srcy<srcYf; srcy++){
    //     int destX = destX0;
    //     for(int srcx=srcX0; srcx<srcXf; srcx++){
    //         int indexInDest = destY * MODE_013_WIDTH + destX;
    //         int srcLn = srcy - srcY0;
    //         int srcCol = srcx - srcX0;
    //         uint8_t srcPixel =  img.Scanlines[srcLn][srcCol];
    //         if(srcPixel != 0x00);
    //             backbuffer[indexInDest] = img.Scanlines[srcLn][srcCol];
    //         destX++;
    //     }
    //     destY++;
    // }
}

void VideoSystem::Present()
{
    memcpy(VGA, backbuffer, MODE_013_ARRAY_SIZE);
}
