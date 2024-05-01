// #include "dpmi.h"
#include "image/image.h"
#include "utils/LOGGER.H"
// #include <bios.h>
// #include <dpmi.h>
// #include <sys/nearptr.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define GDB_IMPLEMENTATION
#include "gdbstub.h"

#include "utils/LOGGER.H"
#include "input/input.h"
#include "video/video.h"
#include "asstload/pcxload.h"
// void set_video_mode(int mode) {
// 	__dpmi_regs regs = {0};
// 	regs.x.ax = mode;
// 	__dpmi_int(0x10, &regs);
// }

int main(void) {
	gdb_start();
	InitLogger();//turns on the logger
	Log("Hello...\n");
	// Go mode 0x13!
	video_set_mode(0x13);
	video_init_backbuffer_for_mode13();
	// load assets
	image_t test_img = {};
	color_t palette[256];
	load_pcx("assets/masked.pcx", &test_img, (color_t *) &palette);
	video_set_palette(palette, 256);
	key_t key = KEY_NONE;
	uint8_t background = 0x02;
	while (key != KEY_ESC) {
		input_update_read_key();    //read the keyboard
		key = input_read_last_key();// get the key
		video_clear_backbuffer(background);
		//TODO: draw something here
		video_draw_image(&test_img, 10, 10, true);
		video_present();
		// Set a GDB checkpoint, needed to receive interrupt commands
		// from the debugger. You should do this in all your game loops.
		gdb_checkpoint();
	}
	video_destroy_backbuffer_for_mode13();
	// Return to text mode
	video_set_mode(MODE_TEXT);
	// set_video_mode(0x3);

	// Read an asset file and print its content
	FILE *file = fopen("assets/test.txt", "r");
	fseek(file, 0, SEEK_END);
	long int num_bytes = ftell(file);
	fseek(file, 0, SEEK_SET);
	unsigned char *file_content = (unsigned char *) malloc(num_bytes + 1);
	fread(file_content, 1, num_bytes, file);
	file_content[num_bytes] = 0;
	printf("%s\n", file_content);
	Log("Goodbye\n");
	return 0;
}