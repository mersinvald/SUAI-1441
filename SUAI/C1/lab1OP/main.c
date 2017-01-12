#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("Введите E: ");
    float E;
    scanf("%f",&E);

    float lastc=1, lastz=1;
    float ch = 1;
    float zn = 1;
    float q = 1;
    float Sum = 1;

    while(1){
        lastc += 2;
        lastz += 3;
        ch *= lastc;
        zn *= lastz;
        q = ch/zn;
        if(fabs(q)<=E)
            break;
        Sum += q;
    }

    printf("Sum = %f\n", Sum);
    return 0;
}
