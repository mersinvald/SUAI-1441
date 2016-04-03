#ifndef STRING_UTILS_C
#define STRING_UTILS_C
#include "string_utils.h"
#include <stdio.h>
#include <memory.h>
#include <assert.h>


uint len(char* str){
    if(str == NULL){
        return 0;
    }

    int l = 0;
    while(str[l] != '\0'){
        l++;
    }
    return l;
}

char* append(char* str, char sym){
    uint l = len(str);

    char* temp = realloc(str, (l+2)*sizeof(char));
    assert(temp != NULL);

    temp[l] = sym;
    temp[l+1] = '\0';
    return temp;
}

int contains(char* str, char ch){
    uint i;
    for(i = 0; i < len(str); i++){
        if(str[i] == ch) return 1;
    }
    return 0 ;
}

char* ncpy(char* dest, char* src, int n){
    return (char*) memcpy(dest, src, n*sizeof(char));
}

char* rm(char* str, int start, int end){
    int wlen = end-start;
    char* word = malloc((wlen+1) * sizeof(char));
    word = ncpy(word, (str+start), wlen);
    printf("\nremoving word %s", word);

    int slen = len(str);

    char* before = str + start;
    char* after = str + end;

    memmove(before, after, (len(after) + 1) * sizeof(char));

    int newsize = (slen - wlen <= 0) ? 1 : slen - wlen;
    char* temp = realloc(str, newsize);
    assert(temp != NULL);

    str = temp;
    return str;
}
#endif // STRING_UTILS_C

