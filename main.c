#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *p;
    p=fopen("multi.txt","w");
    if(p==0) printf("error\n");

    for(int j=1;j<=10;j++) fprintf(p," %d",j);
    fprintf(p,"\n---------------------------------");
    for(int i=1;i<=10;i++)
    {
        fprintf(p,"\n%d|",i);
        for(int j=1;j<=10;j++)
        {
            fprintf(p,"%d ",i*j);
        }
    }
    fclose(p);

    return 0;
}
