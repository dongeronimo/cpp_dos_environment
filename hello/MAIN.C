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
    set_mode(MODE_256_COLOR);
    bool isRunning = true;
    while(isRunning){
        inputSystem.EvaluateKeyHit();
        if(inputSystem.LastKeyHit()!=INPUT_SYSTEM_NO_KEY){
            switch(inputSystem.LastKeyHit()){
            case INPUT_SYSTEM_ESC:
                isRunning = false;
                break;
            default:
                printf("key pressed: %c = %d \n", inputSystem.LastKeyHit(), 
                inputSystem.LastKeyHit());        

            }
        }
    }
    set_mode(MODE_TEXT);
    // set_mode(MODE_256_COLOR);
    // //... The game here
    // while(!exit_game){
    //     inputSystem.EvaluateKeyHit();
    //     switch(inputSystem.LastKeyHit()){
    //         case INPUT_SYSTEM_ESC:
    //             return 0;
    //         default:            
    //             printf("key %s\n", inputSystem.LastKeyHit());
    //     } 
    // }
    // //finishing the game, must return the mode to the defaul
    // set_mode(MODE_TEXT);
    return 0;
}
