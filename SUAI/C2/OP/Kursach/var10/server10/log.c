#include "log.h"
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"


double getUnixTime(){
    struct timespec tv;

    if(clock_gettime(CLOCK_REALTIME, &tv) != 0) return 0;

    return (((double) tv.tv_sec) + (double) (tv.tv_nsec / 1000000000.0));
}

double get_time(){
    static double start_time;
    static int start_flag = 0;

    if(!start_flag){
        start_time  = getUnixTime();
        start_flag = 1;
    }

    return getUnixTime() - start_time;
}

void output(void* stream, const char* message, va_list va){
    char buff[512];

    vsprintf(buff, message, va);

    char out[strlen(buff) + 32];

    sprintf(out, "[%.5lf] %s\n", get_time(), buff);

    if(LOG_TO_FILE)
        fprintf(outfile, out);
    else
        fprintf(stream, out);
}

void log_to_file(FILE *f){
    LOG_TO_FILE = 1;
    outfile = f;
}


void log_o(const char* message, ...){
    va_list va;
    va_start(va, message);
    output(stdout, message, va);
    va_end(va);
}

void error(const char* message, ...){
    va_list va;
    va_start(va, message);

    char buff[strlen(message) + 64];
    sprintf(buff, RED "%s" RESET, message);
    output(stderr, buff, va);
    va_end(va);
}

