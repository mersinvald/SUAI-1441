#include <stdio.h>
//
#define bool int
#define false 0
#define true 1
bool voovel(char ch);

int main(void)
{
    int i;
    int count = 0;
    bool word = false;
    bool start = false;
    bool end = false;
    char ch;
    char prevch;

    while((ch = getchar()) != '\n'){
        if(ch != ' ' && ch != ',' && ch != '.' && ch != ';'){
            if(!word){
                word = true;
                if(voovel(ch)) start = true;
            }
        }
        else{
            if(word){
                word = false;
                if(voovel(prevch)) end = true;
            }
            if(start && ! end) count++;
            start = false;
            end = false;
        }
        prevch = ch;
    }
    
    if(word){
        if(voovel(prevch)) end = true;
        if(start && ! end) count++;
    }

    printf("%i\n", count);
    return 0;
}

bool voovel(char ch){
    char v[7] = "eyuioaEYUIOA";
    int i;
    for(i=0;i<7;i++){
        if(ch == v[i]) return true;
    }
    return false;
}
