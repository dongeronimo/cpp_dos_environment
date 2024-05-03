///Writes elf spritesheet. Output will be at build/assets. Remember to copy
///it to the game assets folder.
#include <stdint.h>
#include <stdlib.h>
#include "utils/LOGGER.H"
#include "utils/logger.h"
#define GDB_IMPLEMENTATION
#include "../gdbstub.h"

#include "asstload/assetld.h"
#include <string.h>

int main(int argc, char **argv) {
	gdb_start();
	InitLogger();
	//define os dados
	char sheetFile[] = "assets/elf.pcx";
	uint16_t sprite_size = 1;
	sprite_desc_t *sprites = calloc(sprite_size, sizeof(sprite_desc_t));
	sprites[0].id = 0;
	sprites[0].x0 = 21;
	sprites[0].y0 = 26;
	sprites[0].x1 = 59;
	sprites[0].y1 = 96;

	uint16_t animation_table_size = 1;
	animation_desc_t *animations = calloc(animation_table_size, sizeof(animation_desc_t));
	animations[0].id = 100;
	animations[0].length = 1;
	animations[0].looping = LOOPING_ANIMATION;
	animations[0].sprites_ids[0] = 0;
	//preenche a struct
	character_sheet_desc_t sheet;
	memcpy(sheet.filename, sheetFile, sizeof(sheetFile));
	sheet.sprite_list_size = sprite_size;
	sheet.sprite_list = calloc(sprite_size, sizeof(sprite_desc_t));
	memcpy(sheet.sprite_list, sprites, sizeof(sprite_desc_t) * sprite_size);
	sheet.animations_list_size = animation_table_size;
	sheet.animation_list = calloc(animation_table_size, sizeof(animation_desc_t));
	memcpy(sheet.animation_list, animations, sizeof(animation_desc_t) * animation_table_size);
	//grava:
	write_asset("assets/elf.ass", &sheet);
	//lê pra comparar pra debug
	character_sheet_desc_t *saved = load_asset("assets/elf.ass");
	Log("filename:%s\n", saved->filename);
	Log("sprite_list_size:%d\n", saved->sprite_list_size);
	for (uint16_t i = 0; i < saved->sprite_list_size; i++) {
		Log("  id:%d, x0:%d, y0:%d, x1:%d, y1:%d\n", saved->sprite_list[i].id, saved->sprite_list[i].x0, saved->sprite_list[i].y0,
			saved->sprite_list[i].x1, saved->sprite_list[i].y1);
	}
	Log("animation_list_size:%d\n", saved->animations_list_size);
	for (uint16_t i = 0; i < saved->animations_list_size; i++) {
		animation_desc_t curr = saved->animation_list[i];
		Log("  id:%d, length:%d, looping:%d, sprites:", curr.id, curr.length, curr.looping);
		for (uint16_t j = 0; j < curr.length; j++) {
			Log("%d, ", curr.sprites_ids[i]);
		}
		Log("\n");
	}
	return 0;
}