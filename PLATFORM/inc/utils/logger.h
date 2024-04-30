#ifndef __logger_h
#define __logger_h
#define log_bit_mask "%#04X "
void InitLogger();
void Log(char *str, ...);
#endif