#include "LOGGER.H"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

FILE* f;

void InitLogger()
{
    f = fopen("log.txt", "a+");
}

void Print(char *str, ...)
{
    va_list ptr;
    va_start(ptr, str);
    vfprintf(f, str, ptr);
    // fprintf(f, str, ptr);
    va_end(ptr);
}
