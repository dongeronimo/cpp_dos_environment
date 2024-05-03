#define GDB_IMPLEMENTATION
#include "gdbstub.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "image/image.h"
#include "utils/LOGGER.H"
#include "input/input.h"
#include "video/video.h"
#include "asstload/pcxload.h"
#include "asstload/assetld.h"


int main(void) {
	gdb_start();
	InitLogger();//turns on the logger
	Log("Hello...\n");
	// Go mode 0x13!
	video_set_mode(0x13);
	video_init_backbuffer_for_mode13();
	//loads the elf character sheet
	character_sheet_desc_t *p_elf_asset = load_asset("assets/elf.ass");
	//loads the image based on the character sheet
	image_t elf_sheet = {};
	color_t palette[256];
	load_pcx(p_elf_asset->filename, &elf_sheet, (color_t *) &palette);
	uint16_t elf_current_animation = 0;
	uint16_t elf_current_sprite = 0;


	video_set_palette(palette, 256);

	key_t key = KEY_NONE;
	uint8_t background = 0x02;
	while (key != KEY_ESC) {
		input_update_read_key();    //read the keyboard
		key = input_read_last_key();// get the key
		video_clear_backbuffer(background);
		sprite_desc_t current_sprite = p_elf_asset->sprite_list[p_elf_asset->animation_list[elf_current_animation].sprites_ids[elf_current_sprite]];
		video_draw_sprite(&elf_sheet, 52, 25, &current_sprite);
		// video_draw_image(&test_img, 10, 10, true);
		video_present();
		// Set a GDB checkpoint, needed to receive interrupt commands
		// from the debugger. You should do this in all your game loops.
		gdb_checkpoint();
	}
	video_destroy_backbuffer_for_mode13();
	// Return to text mode
	video_set_mode(MODE_TEXT);

	Log("Goodbye\n");
	return 0;
}