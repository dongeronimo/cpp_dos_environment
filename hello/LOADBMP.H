#ifndef __loadbmp_h
#define __loadbmp_h

#define MAX_BITMAP_WIDTH 320
#define MAX_BITMAP_HEIGHT 200
//error codes
#define LOADBMP_SUCCESS 0
#define LOADBMP_CANT_OPEN_FILE 1
#define LOADBMP_INVALID_BITMAP 2
#define LOADBMP_COMPRESSED_FILE 3
#define LOADBMP_ONLY_ACCEPTS_8_OR_4_BIT_BITMAP 5
#define LOADBMP_TOO_LARGE 7

class VideoSystem;

// typedef struct {
//    unsigned char manufacturer; /* = 10 */
//    unsigned char version;
//    unsigned char encoding;
//    unsigned char bitsperpixel;
//    int x;
//    int y;
//    int width;
//    int height;
// } t_pcx_header;
 
typedef struct {
   int width;
   int height;
   unsigned char *picdata;
} t_pic;
 
int LoadBMP(char* filename, VideoSystem* videoSystem);
// t_pic *load_pcx(char *filename);
#endif