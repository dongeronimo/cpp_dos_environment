#ifndef __video_h
#define __video_h
#include <sys/types.h>
typedef unsigned int byte_t;

const byte_t MODE_TEXT = 0x03;
const byte_t MODE_256_COLOR = 0X13;
const uint32_t MODE_013_ARRAY_SIZE = 64000;
const uint32_t MODE_013_WIDTH = 320;
const uint32_t MODE_013_HEIGHT = 200;

void set_mode(byte_t mode);
/// @brief Clears the screen with given color.
/// @param color 
void clear_screen(byte_t color);

class VideoSystem{
private:
    uint8_t mClearColor;
public:
    VideoSystem();
    ~VideoSystem();
    void Draw();
    inline void SetClearColor(uint8_t color) {mClearColor = color;};
};

#endif