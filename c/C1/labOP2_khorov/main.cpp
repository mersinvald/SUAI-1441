#include <stdio.h>

int main()
{
    bool slovo=false;
    int c=0,n=1,i=0,nmax=1;
    char a[100], a2[100];

    while((c=getchar())!='\n')
    {
        if(c!=' ')
            if(slovo==false)
                slovo=true;
        if (c==' ')
        {
            for (c=1;c<n;c++)
                if(a[c]==a[n-c]) i++;
            if(i==(n-1))
            {
                if(n>nmax)
                {
                    nmax=n;
                    for (c=1;c<n;c++) a2[c]=a[c];
                }
            }
            n=1;
            i=0;
            slovo =  false;
        }

        if(slovo == true)
        {
            a[n]=c;
            n++;
        }


    }
    for (c=1;c<nmax;c++) printf("%c",a2[c]);
    return 0;
}

