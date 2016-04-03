#include <stdio.h>
#include <stdlib.h>

int checkProgression(float* arr, int size);
float* sort(float* arr, int size);

int main(void)
{
    int sizeX, sizeY;
    float** array;
    int i, j;
    int done = 0;

    while(!done){
        printf("Enter size (x y): ");
        scanf("%i%i", &sizeX, &sizeY);
        (sizeX > 1 && sizeY > 0) ? done = 1 : printf("Error! Y must be positive and X must be > 1\n");
    }

    array = malloc(sizeY * sizeof(float*));

    for(i = 0; i < sizeY; i++){
        array[i] = malloc(sizeX * sizeof(float));
        for(j = 0; j < sizeX; j++){
            scanf("%f", &array[i][j]);
            if(array[i][j] == 0) {
                printf("Error. Member of geometry progression can't be null. Exiting...\n");
                return 0;
            }
        }
    }

    for(i = 0; i < sizeY; i++)
        if(checkProgression(array[i], sizeX))
            printf("Progression in %i line\n", i+1);

    return 0;
}

int checkProgression(float* arr, int size){
    arr = sort(arr, size);
    int step = arr[--size] / arr[size-1];
    for(; size > 0;){
        if((arr[size] / arr[--size]) != step) return 0;
    }
    return 1;
}


float* sort(float* arr, int size){
    int i, j;
    float t;
    for(j = 0; j < size; j++){
        for(i = 0; i < size-1; i++){
            if(arr[i] > arr[i+1]) {
                t  = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = t;
            }
        }
    }
    return arr;
}
