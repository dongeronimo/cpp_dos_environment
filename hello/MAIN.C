
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
    InitLogger();
    Log("Begin\n");
    Image img;
    Color palette[256];
    uint16_t result = LoadPCX("face2.pcx", img, palette);
    Log("---Final image---\n");
    for (int y = 0; y < img.Height; y++) {
        for (int x = 0; x < img.Width; x++) {
            Log(log_bit_mask, img.Scanlines[y][x]);
        }
        Log("\n");
    }
    Log("---Palette---\n");
    for (int i = 0; i < 256; i++) {
        Log("ID:%#04X R:%d G:%d B:%d \n",i, palette[i].r, palette[i].g, palette[i].b);
    }
    // Image* img = load_pcx("pcx_test.pcx");
    // for(int i=0; i<img->width * img->height; i++){
    //     if(i%img->width == 0){
    //         Log("\n");
    //     }
    //     Log("%#08X ", img->pixels[i]);
    // }
    // VideoSystem videoSystem;
    // t_pic* pic = load_pcx("test2.pcx");
    // int result = LoadBMP("A.bmp", &videoSystem);
    
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
