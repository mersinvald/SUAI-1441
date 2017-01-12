#include <stdio.h>
#define SIZE 10

int check(float *arr);
int main(void)
{
    int i;
    char *message;
    float arr[SIZE];

    printf("Enter numbers: ");
    for(i=0;i<SIZE;i++){
        scanf("%f",&arr[i]);
    }

    if(check(arr))			message = "Progression! O_O\n";
    else			        message = "Here is no progression\n";

    printf("%s", message);
    return 0;
}

int check(float *arr){
    int i, dist = arr[1] - arr[0];
    if(dist != 0){
    	for(i=0;i<SIZE-1;i++)
        	if(arr[i]+dist != arr[i+1]) return 0;
    }
    else return 0;
    return 1;
}

//tests:
// 1 2 3 4 5
// 5 2 4 1 3
// 1 3 17 88 99
// 9 -1 18 5 77
// 25 -5 0 5 15 10 20
