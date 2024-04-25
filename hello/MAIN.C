#undef DEBUG
#define _M_IX86
#include "VIDEO.H"
#include "INPUT.H"
#include "UTILS.H"
#include "GAMEOBJS.H"
// #include "LOADBMP.H"
#include "LOGGER.H"
#include "LOADPCX.H"
#include <assert.h>
#include <conio.h>
#include <dos.h>
bool exit_game = false;

volatile uint32_t clockTicks = 0;
void (__interrupt __far *prev_int_1c)();
//https://stanislavs.org/helppc/int_1c.html
//Called by int8, around 18.206 times per second
void __interrupt __far Tick(){
    ++clockTicks;
    _chain_intr( prev_int_1c );
}
int main(void)
{
    //startup
    InitLogger();//The logger writes to file. I need this because i have no debuggers in this environment.
    Log("Beginning startup\n");
    InputSystem inputSystem;
    VideoSystem videoSystem;
    videoSystem.SetClearColor(1);
    Log("Loading assets\n");
    Image img;
    Color palette[255];
    LoadFromFile("masked.pcx", img, palette);
    //stores the palette in the vga
    Log("Setting palette\n");
    videoSystem.SetPalette(palette);
    Log("Set tick interrupt\n");
    prev_int_1c = _dos_getvect( 0x1c );
    _dos_setvect(0x1c, Tick);
    Log("Done\n");
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
        //do draw here
        Log("tick: %d\n", clockTicks);
        videoSystem.Present();
    }
    //restore 0x1c's previous interrupt handler, its good practice to put the DOS state back to what it
    //was before I messed around
    _dos_setvect( 0x1c, prev_int_1c );
    return 0;
}
