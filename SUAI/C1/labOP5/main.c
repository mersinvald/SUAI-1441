#include <stdio.h>
#include <stdlib.h>

int getSize(int x){
    int size = 0;
    for (; x; x >>= 1, size++) //считаем количество разрядов
          continue;
    size = size + (size % 8 ? (8 - size % 8) : 0); //если кратно 8, ничего, если нет, добавляем до следующего кратного 8
    return size;
}

void printBits(int x){
    int i = 0;
    int size = getSize(x);
    char bytes[size];
    for(i = 0; i < size; i++)
        bytes[i] = '0';

    for (i = 0; x; x >>= 1, i++) //пишем в массив биты. Поскольку сдвиг к младшему разряду, биты задом наперед
        bytes[i] = ('0' + (char)(x & 1));

    for (i = size - 1; i >= 0; i--){
        printf("%c", bytes[i]);
        if(i % 8 == 0) printf(" ");
    }
}

int mirror(int byte){
    int t1 = byte;
    int t2;
    int i = 0;
    int pairs[4];
    for(i = 0; i < 4; i++)
        pairs[i] = 0b00;

    byte = 0;
    for(i = 0;t1; i++){
        t2 = t1 >> 2;
        pairs[i] = t1 ^ (t2 << 2);
        t1 >>= 2;

        if(pairs[i] == 0b01)
            pairs[i] = 0b10;
        else
            if(pairs[i] == 0b10)
                pairs[i] = 0b01;

        pairs[i] <<= 6 - i*2;
        byte = byte | pairs[i];
    }

    return byte;
}

int main(void)
{
    int x, i;
    int t1, size;
    int* bytes;
    while(1){
        printf("\nEnter integer number: ");
        scanf("%i", &x);

        printf("Original: %i \t/\t bytes: ", x); printBits(x);
        size = getSize(x);
        bytes = (int*) malloc(size * sizeof(int));

        t1 = x;
        for(i = 0; t1; t1 >>= 8, i++)
            bytes[i] = t1;

        for(i = 0; i < size/8 - 1; i++)
            bytes[i] = bytes[i] ^ bytes[i+1] << 8;

        for (i = 0; i < size/8; i++){
            bytes[i] = mirror(bytes[i]);
            bytes[i] <<= i*8;
        }
        t1 = 0;
        for (i = 0; i < size/8; i++){
            t1 = t1 | bytes[i];
        }
        x = t1;
        printf("\nMirrored: %i \t/\t bytes: ", x); printBits(x);
    }
    return 0;
}

/*11010111
11101011

10001010
01010001
*/
/*
00000000
00000001 -> 00 00 00 01 -> 00 00 00 10 -> 10 00 00 00
10011010 -> 10 01 10 10 -> 01 10 01 01 -> 01 01 10 01*/