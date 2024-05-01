#include "asstload/pcxload.h"
// #include "utils/logger.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t load_pcx(const char *image, image_t *out_img,
				  color_t *out_palette) {
	uint32_t headerStructSize = sizeof(pcx_header_t);
	//It MUST be 128. Due to alignment issues it can be bigger or smaller,
	// If so, i have to add/remove padding
	assert(headerStructSize == 128);
	FILE *f = NULL;
	f = fopen(image, "rb");
	assert(f != NULL);
	pcx_header_t header;
	memset(&header, 0, sizeof(pcx_header_t));
	fread(&header, sizeof(pcx_header_t), 1, f);
	uint32_t posAfterReadingHeader = ftell(f);
	// Log("pos after read = %d\n", posAfterReadingHeader);
	//I MUST be at 128 after reading the header to read the scanlines.
	assert(posAfterReadingHeader == 128);
	//validações
	if (header.Identifier != 0x0a) {
		fclose(f);
		return LOAD_PCX_INVALID_FORMAT;
	}
	if (header.Encoding != 1) {
		fclose(f);
		return LOAD_PCX_INVALID_ENCODING;
	}
	if (header.Version != 5) {
		fclose(f);
		return LOAD_PCX_INVALID_VERSION;
	}
	if (header.BitsPerPixel != 8) {
		fclose(f);
		return LOAD_PCX_INVALID_BITS_PER_PIXEL;
	}
	if (header.NumBitPlanes != 1) {
		fclose(f);
		return LOAD_PCX_INVALID_BIT_PLANES;
	}
	uint16_t ImageWidth = header.XEnd - header.XStart + 1;
	uint16_t ImageHeight = header.YEnd - header.YStart + 1;
	uint16_t ScanlineLength = header.NumBitPlanes * header.BytesPerLine;
	// uint16_t LinePaddingSize = ((header.BytesPerLine * header.NumBitPlanes) *
	//     (8 / header.BitsPerPixel)) - ((header.XEnd - header.XStart) + 1);

	uint8_t *ScanlineBuffer = (uint8_t *) malloc(ScanlineLength);//new uint8_t[ScanlineLength];
	memset(ScanlineBuffer, 0xFF, ScanlineLength);
	uint32_t index = 0;
	uint8_t runcount = 0;
	uint8_t runvalue = 0;
	uint32_t scanlineCursor = 0;
	//prepara a struct
	out_img->Width = ImageWidth;
	out_img->Height = ImageHeight;
	out_img->Scanlines = calloc(ImageHeight * ImageWidth, sizeof(uint8_t));//(uint8_t **) malloc(ImageHeight);
	// for (int i = 0; i < ImageHeight; i++) {
	// 	out_img->Scanlines[i] = (uint8_t *) malloc(ScanlineLength);
	// }
	//lê a scanline
	while (index < ImageHeight * ImageWidth) {
		scanlineCursor = 0;
		runcount = 0;
		runvalue = 0;
		while (scanlineCursor < ScanlineLength) {
			//lê o byte e avalia se é indicador de uma run-length de pixels
			//ou se é um pixel isolado
			uint8_t byte = getc(f);
			if ((byte & 0xC0) == 0xC0) {
				runcount = byte & 0x3F;//pega a runcount
				runvalue = getc(f);    //proximo byte é o valor dos pixels dessa runcount
			} else {
				runcount = 1;
				runvalue = byte;
			}
			//aplica a run-length à scanline.
			memset(ScanlineBuffer + scanlineCursor, runvalue, runcount);
			scanlineCursor += runcount;//incrementa o cursor
		};
		memcpy(out_img->Scanlines + (index / ScanlineLength) * ScanlineLength, ScanlineBuffer, ScanlineLength);
		index += ScanlineLength;
	}
	free(ScanlineBuffer);
	uint16_t code = LOAD_PCX_SUCCESS;
	if (out_palette != NULL) {
		uint8_t paletteMark;
		fread(&paletteMark, sizeof(uint8_t), 1, f);
		if (paletteMark == 12) {                            //tem paleta, lê o resto do arquivo
			fread(out_palette, sizeof(color_t) * 256, 1, f);// to assumindo q a paleta já está alocada
		} else {
			code = LOAD_PCX_NO_PALETTE;
		}
	}
	fclose(f);
	return code;
}