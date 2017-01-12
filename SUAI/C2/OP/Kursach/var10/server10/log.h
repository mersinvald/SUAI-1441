#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

FILE *outfile;
int  LOG_TO_FILE;

extern double getUnixTime();
extern void log_o(const char* message, ...);
extern void error(const char* message, ...);
extern void log_to_file(FILE *f);

#endif // LOG_H

