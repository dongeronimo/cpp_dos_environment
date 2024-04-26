#ifndef __video_h
#define __video_h
#include "IMAGE.H"
typedef uint8_t byte_t;

const byte_t MODE_TEXT = 0x03;
const byte_t MODE_256_COLOR = 0X13;
const uint32_t MODE_013_ARRAY_SIZE = 64000;
const int16_t MODE_013_WIDTH = 320;
const int16_t MODE_013_HEIGHT = 200;

void set_mode(byte_t mode);
/// @brief Clears the screen with given color.
/// @param color 
void clear_screen(byte_t color);

class GameObject;
struct Color;
class VideoSystem{
private:
    uint8_t mClearColor;
public:
    /// @brief Goes to mode 13h
    VideoSystem();
    /// @brief Goes back to mode 3h
    ~VideoSystem();
    void SetPalette(Color* table);
    void ClearBuffer();
    /// @brief Draw the scenes
    /// @param x 
    /// @param y 

    /// @brief Draw an Image on the backbuffer. If isn't transparent it uses memcpy. If it is 
    /// transparent evaluates each pixel for transparency. So transparent images are potentially 
    /// slower then opaques. Max size of an image being draw should be 320x200 (MODE_013_WIDTH and HEIGHT).
    /// The transparent color is 0x00 in the palette. 
    /// The palette is the palette set using SetPalette.
    /// @param img 
    /// @param x 
    /// @param y 
    /// @param transparent 
    void DrawImage(const Image& img, //what to draw 
        int16_t x, //where to draw
        int16_t y, //where to draw
        bool transparent //should I use the transparent code path?
        );
    /// @brief copies from backbuffer to front buffer - it's necessary to avoid flickering.
    void Present();
    /// @brief Set which color will be used to clear the screen.
    /// @param color 
    inline void SetClearColor(uint8_t color) {mClearColor = color;};
};

#endif