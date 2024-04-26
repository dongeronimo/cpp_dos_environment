#ifndef __utils_h
#define __utils_h
#include <dos.h>
#include <sys/types.h>
///Will be set to something else when SetTick runs. Stores the previous 
///Interrupt handler that handled int 1c
// static void (__interrupt __far *prev_int_1c)() = 0;
/// @brief Wait for the given time. It uses
/// int15h to wait
/// @param milisseconds 
void Wait(const uint32_t milisseconds);
#endif