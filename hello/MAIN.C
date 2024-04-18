//includes
// #include <conio.h>
// #include <dos.h>
// #include <i86.h>
// #include <stdio.h>
#include "VIDEO.H"
#include "INPUT.H"
#include "UTILS.H"
#include "GAMEOBJS.H"
#include "LOADBMP.H"
#include "LOGGER.H"

bool exit_game = false;

int main(void)
{
    InitLogger();
    Print("foobar? %d, %s", 10, "foo?");
    int result = LoadBMP("soldier.bmp");
    // InputSystem inputSystem;
    // VideoSystem videoSystem;
    // videoSystem.SetClearColor(1);
    // uint8_t  sprite[] = {4, 4, 4, 4, 4,4,
    //                            4,12,12,12,12,4,
    //                            4,12, 0, 0,12,4,
    //                            4,12, 0, 0,12,4,
    //                            4,12,12,12,12,4,
    //                            4, 4, 4, 4, 4,4};
    // GameObject helloWorld(6, 6 , sprite);
    // bool isRunning = true;
    // while(isRunning){
    //     inputSystem.EvaluateKeyHit();
    //     if(inputSystem.LastKeyHit()!=KEY_NONE){
    //         switch(inputSystem.LastKeyHit()){
    //         case KEY_ESC:
    //             isRunning = false;
    //             break;
    //         case KEY_UP:
    //             if(helloWorld.Y() > 0)
    //                 helloWorld.Move(0, -1);
    //             break;
    //         case KEY_DOWN:
    //             if(helloWorld.Y() < MODE_013_HEIGHT - helloWorld.mHeight)
    //                 helloWorld.Move(0, 1);
    //             break;
    //         case KEY_LEFT:
    //             if(helloWorld.X() > 0)
    //                 helloWorld.Move(-1, 0);
    //             break;
    //         case KEY_RIGHT:
    //             if(helloWorld.X() < MODE_013_WIDTH - helloWorld.mWidth)
    //                 helloWorld.Move(1, 0);
    //             break;      
    //         }
    //     }
    //     videoSystem.ClearScreen();
    //     videoSystem.Draw(helloWorld);
    //     //...
    //     videoSystem.Present();
    //     // GameObject objs[] = {helloWorld};
    //     // videoSystem.Draw(objs, 1);
    //     // Wait(10);
    // }
    return 0;
}
