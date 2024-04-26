#include "UTILS.H"
#include <limits.h>
#include <conio.h>
#include <i86.h>

void Wait(const uint32_t milisseconds)
{
    uint32_t microsseconds = milisseconds * 1000;
    uint16_t dx = microsseconds % USHRT_MAX;
    uint16_t cx = microsseconds / USHRT_MAX;
    union REGS regs;
    regs.h.al = 0;      //al tem que ser zero
    regs.h.ah = 0x86;   //ah tem que ser 0x86
    regs.w.cx = 0;      //cx é um short e é a parte superior do valor em microsegundos
    regs.w.dx = 30000;      //dx é um short e é a parte inferior do valor em microsegundos
    int386(0x15, &regs, &regs);
}
