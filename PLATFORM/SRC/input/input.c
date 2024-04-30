#include "input/input.h"
#include <bios.h>
key_t last_key = KEY_NONE;

void input_update_read_key() {
	uint16_t hasKey = _bios_keybrd(_KEYBRD_READY);
	if (hasKey != 0) {
		uint16_t actualKey = _bios_keybrd(_NKEYBRD_READ);
		last_key = actualKey;
	} else {
		last_key = KEY_NONE;
	}
}

uint16_t input_read_last_key() {
	return last_key;
}
