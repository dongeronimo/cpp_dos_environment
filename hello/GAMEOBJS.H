#ifndef __gameobjs_h
#define __gameobjs_h

#include <sys/types.h>

class GameObject {
    private:
        uint32_t mX;
        uint32_t mY;
    public:
        inline uint32_t X() const {return mX;}
        inline uint32_t Y() const {return mY;} 
        const uint32_t mWidth;
        const uint32_t mHeight;
        uint8_t* mImage;
        /// @brief Creates a new Game Object
        /// @param w 
        /// @param h 
        /// @param image The game object will not take ownership of this pointer
        GameObject(uint32_t w, uint32_t h, uint8_t* image);
        inline void Move(uint32_t dx, uint32_t dy){ 
            mX = mX + dx; 
            mY = mY + dy;
        }
        inline void SetPosition(uint16_t x, uint16_t y) { mX =x; mY =y;}
};
#endif