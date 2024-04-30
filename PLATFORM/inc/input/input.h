#ifndef __input_h
#define __input_h

#include "types.h"

typedef void (*OnKeyHit)(const char key);

typedef uint16_t key_t;
#define KEY_NONE 0
#define KEY_ESC 0x00011B
#define KEY_UP 0x0048E0
#define KEY_DOWN 0x0050E0
#define KEY_LEFT 0X004BE0
#define KEY_RIGHT 0X004DE0
///Reads the keyboard to evaluate if i have a key pressed and store it.
void input_update_read_key();
///Gets the key stored using input_update_read_key. If no key was pressed by the
///time input_update_read_key ran it stores KEY_NONE.
key_t input_read_last_key();


#endif