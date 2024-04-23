#define DEBUG
#include "VIDEO.H"
#include "INPUT.H"
#include "UTILS.H"
#include "GAMEOBJS.H"
// #include "LOADBMP.H"
#include "LOGGER.H"
#include "LOADPCX.H"
#include <assert.h>

bool exit_game = false;

int main(void)
{
    //startup
    InitLogger();//The logger writes to file. I need this because i have no debuggers in this environment.
    Log("Beginning startup\n");
    InputSystem inputSystem;
    VideoSystem videoSystem;
    Log("Loading assets\n");
    Image img;
    Color palette[256];
    LoadFromFile("br.pcx", img, palette);
    //stores the palette in the vga
    //main game loop
    while(!exit_game){
        inputSystem.EvaluateKeyHit();
        if(inputSystem.LastKeyHit()!=KEY_NONE){
            switch(inputSystem.LastKeyHit()){
                case KEY_ESC:
                exit_game  = true;
                break;
            }
        }
        videoSystem.ClearBuffer();
        //do draw here
        videoSystem.Present();
    }

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
