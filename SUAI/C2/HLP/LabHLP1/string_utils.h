#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdlib.h>

extern uint len(char* str);
extern char* append(char* str, char sym);
extern int contains(char* str, char ch);
extern char* ncpy(char* dest, char* src, int n);
extern char* rm(char* str, int start, int end);
#endif // STRING_UTILS_H

