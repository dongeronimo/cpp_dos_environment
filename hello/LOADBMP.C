#include "LOADBMP.H"
#include <dos.h> 
#include <stdio.h> 
#include <string.h> 
#include <conio.h> 
#include "LOGGER.H"
#include "VIDEO.H"
#include <stdlib.h>
#include <sys\types.h>

typedef uint16_t WORD;
typedef uint32_t DWORD;
// struct BMPHeader
// {
//   unsigned short  bfType;
//   int            bfSize; 
//   int            bfReserved;
//   long            bfOffBits;
//   long            biSize;
//   long            biWidth, biHeight;
//   unsigned short  biPlanes, biBitCount;
//   long            biCompression, f, biXPelsPerMeter, 
//                   biYPelsPerMeter, biClrUsed, biClrImportant;
// } Header;

struct BMPHeader {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} Header;

struct Color {
    uint8_t r,g,b;
};


int LoadBMP(char* filename, VideoSystem* videoSystem) {
    //Baseado em http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
    FILE* BMPFile = NULL;
    unsigned char c, Palette[256][4];
    unsigned int  offset, lines, paddedWidth;
    /* This checks for the file */
    BMPFile = fopen(filename, "rb");
    if (BMPFile == NULL)
    {
        Log("Fail to open bitmap %s.\n", filename);
        return LOADBMP_CANT_OPEN_FILE;
    }
    char signature[2];
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
    uint32_t infoHeaderSize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t colorsUsed;
    Color palette[256];
    #define LOAD(v) fread(&v, sizeof(v), 1, BMPFile)
    LOAD(signature);
    LOAD(fileSize);
    LOAD(reserved);
    fseek(BMPFile, 0x000E, SEEK_SET); //Se não fizer esse seek o leitor se perde
    LOAD(dataOffset);
    LOAD(width);
    LOAD(height);
    LOAD(planes);
    LOAD(bitsPerPixel);
    LOAD(compression);
    fseek(BMPFile, 0X002E, SEEK_SET);//pulo direto pra colors used
    LOAD(colorsUsed);
    fseek(BMPFile, 0x0036, SEEK_SET); //Pulo pro setor de paleta
    for(int i=0; i<colorsUsed; i++){
        uint8_t x;
        LOAD(palette[i].r);
        LOAD(palette[i].g);
        LOAD(palette[i].b);
        LOAD(x);
    }
    // fseek(BMPFile, dataOffset, SEEK_SET); //pulo pros dados
    uint8_t* buffer = (uint8_t*)malloc(fileSize - dataOffset);
    fread(buffer, fileSize - dataOffset, 1, BMPFile);
    #undef LOAD
    Log("Loading bitmap %s \n", filename);
    Log("Signature: %c%c \n",signature[0], signature[1] );
    Log("File Size: %d \n", fileSize);
    Log("Reserved: %d \n", reserved);
    Log("DataOffset: %d \n", dataOffset);
    Log("Info Size: %d \n", infoHeaderSize);
    Log("Width: %d \n", width);
    Log("Heigth: %d \n", height);
    Log("Planes: %d \n", planes);
    Log("Bits per pixel: %d \n", bitsPerPixel);
    Log("Compression: %d \n", compression);
    Log("Colors Used: %d \n", colorsUsed);
    for(int i=0; i<colorsUsed; i++){
        Log("Color %d: %d,%d,%d \n", i, palette[i].r, palette[i].g, palette[i].b);
    }
    uint8_t* bitmap = (uint8_t*)malloc(width * height);
    //It may be either 4 bits per pixel or 8 bits per pixel. I need to expand the 4bit pixels 
    //to 8 bits for the rest of system.
    if(bitsPerPixel == 4){
        //The data from the file is stored in a uint8_t (8 bits). Each 4 bits has a value;
        uint32_t numberOfElements = width * height / 2;
        for(uint32_t i=0; i<numberOfElements; i++){
            // printf("Key = %#08X \n", actualKey);    
            uint8_t element = buffer[i];
            Log("%#8X ", element);
            uint8_t left = element >> 4; //takes the upper bits
            uint8_t right = (element << 4) >> 4; //trick to take only the lower bits, erasing the upper ones
            //now that they were converted from 4 bytes to 8, put in the bitmap
            bitmap[i*2 + 0] = left;
            bitmap[i*2 + 1] = right;
        }
        Log("\n");
    }
    else if(bitsPerPixel == 8){
        uint32_t numberOfElements = width * height;
        for(uint32_t i=0; i<numberOfElements; i++){
            bitmap[i] = buffer[i];
        }
    }else{
        return LOADBMP_ONLY_ACCEPTS_8_OR_4_BIT_BITMAP;
    }

    Log("Bitmap:\n");
    for(uint32_t y=0; y<height; y++){
        for(uint32_t x=0; x<width; x++){
            uint32_t idx = width * y + x;
            uint8_t val =bitmap[idx];
            Log("%#08X ", val);
            
        }
        Log("\n");
    }
    fclose(BMPFile);
    return 0;
}



// t_pic *load_pcx(char *filename)
// {
//    FILE *fp;
//    t_pcx_header pcx;
//    t_pic *pic;
//    int databyte;
//    int count;
//    long l;
    
//    Log("Beginning load pcx\n"); 
//    fp = fopen(filename, "rb");
//    if (fp == NULL)
//    {
//       Log("File error - could not open %s\n", filename);
//       return NULL;
//    }
//    fread(&pcx, sizeof(pcx), 1, fp);
//    if (pcx.manufacturer != 10)
//    {
//       Log("Invalid manufacturer value %d\n", pcx.manufacturer);
//       return NULL;
//    }
//    else if (pcx.encoding != 1)
//    {
//       Log("Invalid encoding value %d\n", pcx.encoding);
//       return NULL;
//    }
//    else if (pcx.bitsperpixel != 8)
//    {
//       Log("Invalid bits per pixel value %d\n", pcx.bitsperpixel);
//       return NULL;
//    }
//    else if (pcx.x < 0 || pcx.x > 319 || pcx.y < 0 || pcx.y > 199 || pcx.width < 1 || pcx.width > 319 || pcx.height < 1 || pcx.height > 199)
//    {
//       Log("Invalid image dimensions x=%d, y=%d, width=%d, height=%d\n", pcx.x, pcx.y, pcx.width, pcx.height);
//       return NULL;
//    }
//    fseek(fp, 128, SEEK_SET);
//    pic = (t_pic *)malloc(sizeof(t_pic));
//    if (pic->picdata == NULL)
//    {
//       Log("Picture object: Memory allocation error\n");
//       return NULL;
//    }
//    pic->width = pcx.width + 1;
//    pic->height = pcx.height + 1;
//    pic->picdata = (unsigned char *)malloc((long)pic->width * pic->height);
//    if (pic->picdata == NULL)
//    {
//       Log("Picture data: Memory allocation error.\n");
//       return NULL;
//    }
//    for (l=0;l<(long)pic->width * pic->height;l++)
//    {
//       databyte = getc(fp);
//       if (databyte == EOF)
//       {
//      Log("Image read error\n");
//      return NULL;
//       }
//       if (databyte & 0xC0)
//       {
//      unsigned char j;
 
//      count = databyte & 0x3F;
//      databyte = getc(fp);
//      printf("%d\n", count);
//      for (j=0;j<count;j++)
//         pic->picdata[l++] = (unsigned char)databyte;
//       }
//       else
//      pic->picdata[l] = (unsigned char)databyte;
//    }
//    fclose(fp);
//    return pic;
// }