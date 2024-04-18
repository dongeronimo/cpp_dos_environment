//includes
#include <conio.h>
#include <dos.h>
#include <i86.h>
#include <stdio.h>
#include "VIDEO.H"
#include "INPUT.H"
#include "UTILS.H"
bool exit_game = false;

int main(void)
{
    InputSystem inputSystem;
    VideoSystem videoSystem;
    videoSystem.SetClearColor(3);
    bool isRunning = true;
    while(isRunning){
        inputSystem.EvaluateKeyHit();
        if(inputSystem.LastKeyHit()!=KEY_NONE){
            switch(inputSystem.LastKeyHit()){
            case KEY_ESC:
                isRunning = false;
                break;
            // default:
            //     // printf("key pressed: %c = %d \n", inputSystem.LastKeyHit(), 
            //     // inputSystem.LastKeyHit());        
            }
        }
        videoSystem.Draw();
    }
    return 0;
}
