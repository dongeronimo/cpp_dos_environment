#ifndef __utils_h
#define __utils_h

#include <sys/types.h>
/// @brief Wait for the given time. It uses
/// int15h to wait
/// @param milisseconds 
void Wait(const uint32_t milisseconds);

#endif