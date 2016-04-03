#include <stdio.h>
#define SIZE 64
using namespace std;
//any array is a pointer and its awesome yeeeeeeah
bool voovel(char ch);

int main()
{
    char word[64];
    int count = 0;
    int i = 0;
    bool s = false;
    bool e = false;
    int l;
    printf("Enter string length(words count): ");
    scanf("%i", &l);
    printf("Enter string: ");

    for(i=0;i<l;i++){
        scanf("%s", &word);
        int end = 0;
        for(i=0;i<64;i++){
            if(word[i] == '\0' || word[i] == '\n' || word[i] == ' ')
                break;
            end++;
        }
        if(voovel(word[0]))     s = true;
        if(voovel(word[end-1]))   e = true;
        if(s && !e) count++;
        s = false;
        e = false;
    }
    printf("%i\n", count);
    return 0;
}

bool voovel(char ch){
    char v[7] = "eyuioa";
    int i;
    for(i=0;i<7;i++){
        if(ch == v[i]) return true;
    }
    return false;
}
