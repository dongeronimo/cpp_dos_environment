#ifndef __image_h
#define __image_h
#include "types.h"
/// @brief Defines an image, with a given width, height and it's pixels in a array
/// scanlines. Images are loaded using loadpcx.h.
struct Image {
	uint16_t Width;
	uint16_t Height;
	uint8_t **Scanlines;
};


#endif