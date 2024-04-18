#include "LOADBMP.H"
#include <dos.h> 
#include <stdio.h> 
#include <string.h> 
#include <conio.h> 

struct BMPHeader
{
  unsigned short  bfType;
  long            bfSize, bfReserved, bfOffBits, biSize, biWidth, biHeight;
  unsigned short  biPlanes, biBitCount;
  long            biCompression, biSizeImage, biXPelsPerMeter, 
                  biYPelsPerMeter, biClrUsed, biClrImportant;
} Header;

int LoadBMP(char* filename) {
    FILE* BMPFile = NULL;
    unsigned char c, Palette[256][4];
    unsigned int  offset, lines, paddedWidth;
    /* This checks for the file */
    BMPFile = fopen(filename, "rb");
    if (BMPFile == NULL)
    {
        return LOADBMP_CANT_OPEN_FILE;
    }
    return 0;
}