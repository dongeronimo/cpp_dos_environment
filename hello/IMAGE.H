#ifndef __image_h
#define __image_h
#include <sys\types.h>
struct Image {
    uint16_t Width;
    uint16_t Height;
    uint8_t** Scanlines;
};


#endif