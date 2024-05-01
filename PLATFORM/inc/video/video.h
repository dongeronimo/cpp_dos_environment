#ifndef __video_h
#define __video_h
#include "types.h"
#include "image/image.h"
#include <dpmi.h>

#define MODE_TEXT 0x03
#define MODE_13H 0X13
#define MODE_013_ARRAY_SIZE 64000
#define MODE_013_WIDTH 320
#define MODE_013_HEIGHT 200
///Sets the video mode.
static inline void video_set_mode(uint8_t mode) {
	__dpmi_regs regs = {0};
	regs.x.ax = mode;
	__dpmi_int(0x10, &regs);
}
///Initializes the backbuffer for mode13. Can't draw directly
///to screen to avoid flickering
void video_init_backbuffer_for_mode13();
///Clear the backbuffer with the background color
void video_clear_backbuffer(uint8_t color);

void video_set_palette(color_t *table, uint16_t size);
///Draw the given image on the backbuffer
void video_draw_image(const image_t *img,//what to draw
					  int16_t x,         //where to draw
					  int16_t y,         //where to draw
					  bool_t transparent //should I use the transparent code path?
);
///Copies content from the backbuffer to the gpu
void video_present();
///Destroys the backbuffer
void video_destroy_backbuffer_for_mode13();
#endif