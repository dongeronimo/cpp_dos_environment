#include "INPUT.H"
#include <conio.h>
InputSystem::InputSystem()
:mLastKeyHit(INPUT_SYSTEM_NO_KEY)
{
}

void InputSystem::EvaluateKeyHit()
{
    if(kbhit()){
        char key = getch();
        mLastKeyHit = key;
    }else{
        mLastKeyHit = INPUT_SYSTEM_NO_KEY;
    }
}
