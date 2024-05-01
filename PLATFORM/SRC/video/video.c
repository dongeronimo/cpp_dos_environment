#include "video/video.h"
#include <bios.h>
#include <stdint.h>
#include <dpmi.h>
#include <stdlib.h>
#include <sys/nearptr.h>
#include <string.h>
#include "utils/logger.h"

uint8_t backbuffer[MODE_013_ARRAY_SIZE];

void video_init_backbuffer_for_mode13() {
	//I use backbuffer, no need for dynamic allocation
}

void video_clear_backbuffer(uint8_t color) {
	memset(backbuffer, color, MODE_013_ARRAY_SIZE);
}

void video_set_palette(color_t *table, uint16_t size) {
	__djgpp_nearptr_enable();
	//TODO: Set the palette
	__djgpp_nearptr_disable();
}
void video_draw_image(const image_t *img,//what to draw
					  int16_t x,         //where to draw
					  int16_t y,         //where to draw
					  bool_t transparent //should I use the transparent code path?
) {
	//TODO: fucked up when i gone from C++ to C
	if ((x < 0 && abs(x) > img->Width) || x >= MODE_013_WIDTH) {
		//Image is fully outside in the horizontal axis - wont draw
		Log("won't draw: outside of screen (horizontal)\n");
		return;
	}
	if ((y < 0 && y < -img->Height) || y >= MODE_013_HEIGHT) {
		//image is fully outside in the vertical axis - wont't draw.
		Log("won't draw: outside of screen (vertical)\n");
		return;
	}
	//calculating the initial and final positions in the backbuffer
	int dstX0 = x;
	if (x < 0)
		dstX0 = 0;
	int dstXf = dstX0 + img->Width;
	if (x + img->Width > MODE_013_WIDTH)
		dstXf = MODE_013_WIDTH;
	int dstY0 = y;
	if (y < 0)
		dstY0 = 0;
	int dstYf = dstY0 + img->Width;
	if (y + img->Height > MODE_013_HEIGHT)
		dstYf = MODE_013_HEIGHT;
	//calculating the initial and final position in the image
	int srcX0 = 0, srcXf = img->Width, srcY0 = 0, srcYf = img->Height;
	if (x < 0) {
		srcX0 = x * -1;
	}
	if (y < 0) {
		srcY0 = y * -1;
	}
	if (x + img->Width > MODE_013_WIDTH) {
		srcXf = img->Width - (x + img->Width - MODE_013_WIDTH);
	}
	if (y + img->Height > MODE_013_HEIGHT) {
		srcYf = img->Height - (y + img->Height - MODE_013_HEIGHT);
	}
	Log("Dest: x[%d,%d],y[%d, %d]\n", dstX0, dstXf, dstY0, dstYf);
	Log("Src: x[%d,%d],y[%d, %d]\n", srcX0, srcXf, srcY0, srcYf);
	size_t line_size = (srcXf - srcX0);
	if (!transparent) {
		uint16_t sY = srcY0;
		for (uint32_t dY = dstY0; dY < dstY0 + (srcYf - srcY0); dY++) {
			uintptr_t dst_pointer_offset = dY * MODE_013_WIDTH + x;
			uintptr_t src_pointer_offset = sY * (srcXf - srcX0) + srcX0;

			memcpy(backbuffer + dst_pointer_offset, img->Scanlines + src_pointer_offset, line_size);
			Log("   dst_pointer_offset=%d, src_pointer_offset=%d, line_size=%d\n",
				dst_pointer_offset, src_pointer_offset, line_size);
			sY++;
		}
	}
	// //now that i have the ranges I can copy from the image to the backbuffer
	// if (!transparent) {
	// 	//if it's not transparent i can just memcpy the scanlines into the backbuffer,
	// 	//minding the ranges calculated above
	// 	uint32_t sY = srcY0;
	// 	uint32_t dIdx;
	// 	for (uint32_t dY = dstY0; dY < dstY0 + (srcYf - srcY0); dY++) {
	// 		dIdx = dY * MODE_013_WIDTH + dstX0;
	// 		// Log("dY=%d, dIdx=%d\n, srcXf-srcX0",dY, dIdx, );
	// 		uint32_t scanline_pos = sY * (srcXf - srcX0) + srcX0;
	// 		memcpy(backbuffer + dIdx, img->Scanlines + scanline_pos, srcXf - srcX0);
	// 		// memcpy(&backbuffer[dIdx], &img->Scanlines[sY][srcX0], srcXf -srcX0 );
	// 		sY++;
	// 	}
	// } else {
	// 	//Can't use memcpy if using transparency because i must compare each pixel and only
	// 	//write it isn't 0x00
	// 	uint32_t sY = srcY0;
	// 	for (uint32_t dY = dstY0; dY < dstY0 + (srcYf - srcY0); dY++) {
	// 		uint32_t sX = srcX0;
	// 		for (uint32_t dX = dstX0; dX < dstX0 + (srcXf - srcX0); dX++) {
	// 			uint32_t dIdx = dY * MODE_013_WIDTH + dX;
	// 			uint8_t srcPixel = img->Scanlines[sY][sX];
	// 			if (srcPixel != 0x00)
	// 				backbuffer[dIdx] = srcPixel;
	// 			sX++;
	// 		}
	// 		sY++;
	// 	}
	// }
}

void video_present() {
	__djgpp_nearptr_enable();
	unsigned char *vram = (unsigned char *) (__djgpp_conventional_base + 0xa0000);
	memcpy(vram, backbuffer, MODE_013_ARRAY_SIZE);
	__djgpp_nearptr_disable();
}

void video_destroy_backbuffer_for_mode13() {
	//I use backbuffer, no need for dynamic allocation
}
