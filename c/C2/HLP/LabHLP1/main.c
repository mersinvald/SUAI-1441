#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "string_utils.h"

char* weed(char* str, char* restricted){
    uint pos = 0;
    uint wstart = 0;
    uint wend = 0;
    uint to_rm = 0;
    uint no_word = 1;

    for(pos = 0; pos < len(str)+1;pos++){
        char current = str[pos];

        if(no_word && current != ' '){
            no_word = 0;
            wstart = pos;
        }

        if(contains(restricted, current)){
            to_rm = 1;
        }

        if(current == ' ' || current == '\0'){
            wend = pos;
            if(to_rm) {
                str = rm(str, wstart, wend);
                pos = wstart;
            }

            to_rm = 0;
            no_word = 1;
        }
    }
    return str;
}

int main(void)
{
    char* str = NULL;
    printf("Enter string: ");

    char ch;
    while((ch = getchar()) != '\n'){
        str = append(str, ch);
    }

    printf("Enter restricted symbols: ");
    char* restricted = malloc(64 * sizeof(char));
    scanf("%s", restricted);

    str = weed(str, restricted);
    printf("\n\nResult: %s\n", str);

    return 0;
}

