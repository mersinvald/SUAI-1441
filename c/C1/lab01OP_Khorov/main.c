#include <stdio.h>

int main(void)

{
 int i,n;
 float x=-0.5;
 float s=0.0;
 float a;
 scanf("%i",&n);
 for(i=1;i<=n;i++)
 {
 x=x*(-2.0);
 a=i/x;
 printf("a%i=%f\n",i,a);
 s=s+a;

 }
 printf("summa=");
 printf("%f\n",s);
}

