#ifndef __input_h
#define __input_h

#include <sys/types.h>

typedef void (*OnKeyHit)(const char key);

#define KEY_NONE 0
#define KEY_ESC 0x00011B
#define KEY_UP 0x0048E0
#define KEY_DOWN 0x0050E0
#define KEY_LEFT 0X004BE0
#define KEY_RIGHT 0X004DE0

class InputSystem{
    private:
        uint16_t mLastKeyHit;
    public:
        InputSystem();
        void EvaluateKeyHit();
        inline const uint16_t LastKeyHit() const { return mLastKeyHit;}
};
#endif