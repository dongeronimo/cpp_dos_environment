#include "INPUT.H"
#include <conio.h>
#include <bios.h>
#include <dos.h>
#include <i86.h>
#include <stdio.h>

InputSystem::InputSystem()
    :mLastKeyHit(KEY_NONE)
{
}

void InputSystem::EvaluateKeyHit()
{
    uint16_t hasKey = _bios_keybrd(_NKEYBRD_READY);
    if(hasKey != 0){
        uint16_t actualKey = _bios_keybrd(_NKEYBRD_READ);
        mLastKeyHit = actualKey;
        // printf("Key = %#08X \n", actualKey);    
    }else{
        mLastKeyHit = KEY_NONE;
    }
}
