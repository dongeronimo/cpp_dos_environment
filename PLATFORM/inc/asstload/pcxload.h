#ifndef _pcxload_h
#define _pcxload_h
#include "image/image.h"
// #include "types.h"

typedef uint16_t WORD;
typedef uint8_t BYTE;

#define LOAD_PCX_SUCCESS 0
#define LOAD_PCX_INVALID_FORMAT 1
#define LOAD_PCX_INVALID_ENCODING 2
#define LOAD_PCX_INVALID_VERSION 3
#define LOAD_PCX_INVALID_BITS_PER_PIXEL 5
#define LOAD_PCX_INVALID_BIT_PLANES 7
#define LOAD_PCX_NO_PALETTE 11

typedef struct {
	BYTE Identifier;     /* PCX Id Number (Always 0x0A) */
	BYTE Version;        /* Version Number */
	BYTE Encoding;       /* Encoding Format */
	BYTE BitsPerPixel;   /* Bits per Pixel */
	WORD XStart;         /* Left of image */
	WORD YStart;         /* Top of Image */
	WORD XEnd;           /* Right of Image*/
	WORD YEnd;           /* Bottom of image */
	WORD HorzRes;        /* Horizontal Resolution */
	WORD VertRes;        /* Vertical Resolution */
	BYTE Palette[48];    /* 16-Color EGA Palette */
	BYTE Reserved1;      /* Reserved (Always 0) */
	BYTE NumBitPlanes;   /* Number of Bit Planes */
	WORD BytesPerLine;   /* Bytes per Scan-line */
	WORD PaletteType;    /* Palette Type */
	WORD HorzScreenSize; /* Horizontal Screen Size */
	WORD VertScreenSize; /* Vertical Screen Size */
	BYTE Reserved2[54];  /* Reserved (Always 0) */
} pcx_header_t;

uint32_t load_pcx(const char *image,
				  image_t *out_img,
				  color_t *out_palette);

#endif