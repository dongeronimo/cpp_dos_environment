#ifndef __image_h
#define __image_h
#include "types.h"
#include <stdint.h>
/// @brief Defines an image, with a given width, height and it's pixels in a array
/// scanlines. Images are loaded using loadpcx.h.
typedef struct image_t {
	uint16_t Width;
	uint16_t Height;
	uint8_t *Scanlines;
} image_t;
/// The color triplet. Remember that the color is between 0-255 and that while I
/// store it as a 8 bits value it is actually a 6 bit value in vga.
typedef struct color_t {
	uint8_t r, g, b;
} color_t;

inline static uint8_t get_pixel(const image_t *img, uint16_t x, uint16_t y) {
	return img->Scanlines[y * img->Width + x];
}


#endif