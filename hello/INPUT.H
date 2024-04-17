#ifndef __input_h
#define __input_h
typedef void (*OnKeyHit)(const char key);
#define INPUT_SYSTEM_NO_KEY 0
#define INPUT_SYSTEM_ESC 27
class InputSystem{
    private:
        char mLastKeyHit;
    public:
        InputSystem();
        void EvaluateKeyHit();
        inline const char LastKeyHit() const { return mLastKeyHit;}
};
#endif