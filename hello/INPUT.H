#ifndef __input_h
#define __input_h

#include <sys/types.h>

typedef void (*OnKeyHit)(const char key);

#define KEY_NONE 0
#define KEY_ESC 0x00011B

class InputSystem{
    private:
        uint16_t mLastKeyHit;
    public:
        InputSystem();
        void EvaluateKeyHit();
        inline const uint16_t LastKeyHit() const { return mLastKeyHit;}
};
#endif