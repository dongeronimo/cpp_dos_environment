// #undef DEBUG
#define _M_IX86
#include "VIDEO.H"
#include "INPUT.H"
#include "UTILS.H"
// #include "LOADBMP.H"
#include "LOGGER.H"
#include "LOADPCX.H"
#include <conio.h>
#include <dos.h>

bool exit_game = false;
void (__interrupt __far *prev_int_1c)();
volatile uint32_t clockTicks = 0;
// /// @brief Blocks interrupts from firing
// void asm_cli();
// #pragma aux asm_cli = "cli";
// /// @brief allows interrupts again
// void asm_sti();
// #pragma aux asm_sti = "sti";
// //https://stanislavs.org/helppc/int_1c.html
// //Called by int8, around 18.206 times per second
// void __interrupt __far Tick(){
//     ++clockTicks;
//     _chain_intr( prev_int_1c );
// }

// void SetTickFunction(){
//     asm_cli();
//     prev_int_1c = _dos_getvect( 0x1c );//stores previous tick handler. It'll be used at the end of the program
//     _dos_setvect(0x1c, Tick);//sets new tick handler
//     outp(0x40, 0x36);//prepares PIT
//     outp(0x40, 0x8000);//apporx 36 interrupts per second
//     asm_sti();
// }

// void ResetTickFunction(){
//     asm_cli();
//     _dos_setvect(0x1c, prev_int_1c);//sets new tick handler
//     outp(0x40, 0x36);//prepares PIT
//     outp(0x40, 0x0000);//back to the default
//     asm_sti();
// }

int main(void)
{
    //startup
    InitLogger();//The logger writes to file. I need this because i have no debuggers in this environment.
    Log("Beginning startup\n");
    InputSystem inputSystem;
    VideoSystem videoSystem;
    videoSystem.SetClearColor(0x00);
    Log("Loading assets\n");
    Image img;
    Color palette[256];
    uint32_t err = LoadFromFile("hero.pcx", img, palette);
    Log("load result = %d\n", err);
    //stores the palette in the vga
    palette[0].r = 0;
    palette[0].g = 0;
    palette[0].b = 0;
    videoSystem.SetPalette(palette);

    //sets up the game tick
    Log("Set tick interrupt\n");
    // SetTickFunction();
    Log("Done\n");
    Log("Beginning game loop\n");
    // //main game loop
    while(!exit_game){
        inputSystem.EvaluateKeyHit();
        if(inputSystem.LastKeyHit()!=KEY_NONE){
            switch(inputSystem.LastKeyHit()){
                case KEY_ESC:
                    Log("Key Pressed: esc\m");
                    exit_game  = true;
                    break;
                default:
                    Log("Key Pressed = %#08X \n", inputSystem.LastKeyHit());
            }
        }
        videoSystem.ClearBuffer();
        videoSystem.DrawImage(img, 10, 10, false);
        //do draw here
        // Log("tick: %d\n", clockTicks);
        videoSystem.Present();
    }
    // ResetTickFunction();

    return 0;
}
