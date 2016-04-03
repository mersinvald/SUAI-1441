#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define ERR_NO 0
#define ERR_NOTENOUGHARGS 1
#define ERR_OPENFILE 2

#define BUFFSIZE 256

void usage(char* arg0){
    fprintf(stdout, "%s input_file output_file max_len", arg0);
}

uint len(char* str){
    if(str == NULL){
        return 0;
    }

    int l = 0;
    while(*(++str) != '\0'){
        l++;
    }
    return l;
}

void trim(char* src, int maxlen){
    if(maxlen < len(src)){
        char* newend = (src + sizeof(char) * maxlen);
        if(*newend != ' '){
            while(*newend != ' ' && maxlen > 0){
                newend--;
                maxlen--;
            }
        }
        *newend = '\0';
    }
}

int main(int argc, char** argv){
    int ECODE = ERR_NO;

    if(argc < 4 || argc > 4){
        usage(argv[0]);
        ECODE = ERR_NOTENOUGHARGS;
        goto exit;
    }

    FILE *in, *out;
    int maxlen = 0;

    if((in = fopen(argv[1], "r")) == NULL){
        ECODE = ERR_OPENFILE;
        goto exit;
    }

    if((out = fopen(argv[2], "w")) == NULL){
        ECODE = ERR_OPENFILE;
        goto close;
    }

    maxlen = atoi(argv[3]);

    int n;
    char* str;
    char buffer[BUFFSIZE];
    memset(&buffer, '\0', sizeof(buffer));

    while((str = fgets(buffer, sizeof(buffer), in)) != NULL){
        if(buffer[0] != 4) trim(&buffer, maxlen);
        fputs(buffer, out);
    }

close:
    fcloseall();
exit:
    return ECODE;
}

