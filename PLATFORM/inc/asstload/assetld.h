#ifndef __assetld_h
#define __assetld_h
#include "stdlib.h"
#include <stdint.h>
#include "image/image.h"

#define SHEET_FILENAME_SIZE 32
#define ANIMATION_SPRITES_SIZE 64
#define LOOPING_ANIMATION 1
#define ONE_SHOT_ANIMATION 0

typedef struct sprite_desc_t {
	uint16_t id;
	uint16_t x0;
	uint16_t y0;
	uint16_t x1;
	uint16_t y1;
} sprite_desc_t;

typedef struct animation_desc_t {
	uint16_t id;
	uint16_t length;                             // how many frames
	uint8_t looping;                             // is it a looping or not
	uint16_t sprites_ids[ANIMATION_SPRITES_SIZE];//The table of sprites ids,

} animation_desc_t;

typedef struct character_sheet_desc_t {
	//the image file for this sheet. All sprites of a character must belong to the
	//same sheet.
	char filename[SHEET_FILENAME_SIZE];
	//How many sprites?
	uint16_t sprite_list_size;
	//The size will be sprite_list_size * sizeof(sprite_desc_t)
	sprite_desc_t *sprite_list;
	//how many animations?
	uint16_t animations_list_size;
	animation_desc_t *animation_list;

} character_sheet_desc_t;

void write_asset(const char *path, character_sheet_desc_t *data);
character_sheet_desc_t *load_asset(const char *path);
#endif