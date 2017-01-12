#include <stdio.h>

void reverse_c_string(char* str){
    char* end = str;
    char tmp;
    if (str) {
        while (*end) {
            ++end;
        }
        --end;
        while (str < end) {
            tmp = *str;
            *str++ = *end;
            *end-- = tmp;
        }
    }
}



int main()
{
    char* str = "mutation";
    printf("%s\n", str);
    reverse_c_string(str);
    printf("%s\n", str);
    return 0;
}

