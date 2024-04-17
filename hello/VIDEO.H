#ifndef __video_h
#define __video_h

typedef unsigned int byte_t;

const byte_t MODE_TEXT = 0x03;
const byte_t MODE_256_COLOR = 0X13;



void set_mode(byte_t mode);

#endif