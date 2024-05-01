#include "utils\LOGGER.H"
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

FILE *f;
int loggerIsInitialized = 0;
void InitLogger() {
	f = fopen("log.txt", "a+");
	loggerIsInitialized = 1;
}

void Log(const char *str, ...) {
	assert(loggerIsInitialized == 1);
	va_list ptr;
	va_start(ptr, str);
	vfprintf(f, str, ptr);
	va_end(ptr);
	fflush(f);
}
