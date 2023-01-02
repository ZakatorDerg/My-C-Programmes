#include <stdio.h>
#include <stdlib.h>

int main()
{

    int a=10;
    scanf("%d\n",&a);
    char znak='X';

    char polecenie[2];

    scanf("%c\n",&polecenie[0]);
    scanf("%c",&polecenie[1]);


    int x=(int)polecenie[0]-97;
    int y=(int)polecenie[1]-49;  // zwróci wartoœæ int


    printf("%d",x);
    printf("\n");
    printf("%d",y);
    printf("\n");

    int b=97+a;
    for(int i=97; i<b; i++)
    {
        printf(" ");
        printf("%c",i);
    }
    printf("\n");
    for(int i=0; i<a; i++)
    {
        for(int j=0;j<a;j++)
        {
            printf("--");
        }
        printf("-");
        printf("\n");
        for(int j=0;j<a;j++)
        {
            if(i==y && j==x)
            {
               printf("|");
                printf("%c",znak);
            }

            else
            printf("| ");
        }
        printf("|");
        printf("%d",i+1);
        printf("\n");
    }
    for(int j=0;j<a;j++)
        {
            printf("--");
        }
        printf("-");

    return 0;
}
