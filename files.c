#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct student
{
    int w;
    char name[100];
    struct student *next;
}o1;


int main()
{
    //Wczytanie tekstu i liczb 1...100 do pliku1
    char tekst[100]="Hello world";

    FILE *plik;
    plik = fopen("plik1.txt","w");
    if(plik==NULL)
    {
        printf("Open error");
        exit(1);
    }
    fprintf(plik,"%s\n",tekst);
    for(int i=1;i<=100;i++)
    {
        fprintf(plik,"%d\n",i);
    }
    fclose(plik);

    //Wypisanie zawartosci pliku2
    FILE *p;
    p=fopen("plik2.txt","r");
    if(p==NULL)
    {
        printf("Open error");
        exit(1);
    }
    int liczba;
    fscanf(p,"%d",&liczba);
    printf("%d",liczba);
    fclose(p);

    //Wczytanie do pliku co trzecia literke a...z i potem odwrotnie
    FILE *pl;
    pl=fopen("plikalfa.txt","w");
    if(pl==NULL)
    {
        printf("Open error");
        exit(1);
    }
    for(char i='a';i<='z';i=i+3)
    {
       fprintf(pl,"%c\n",i);
    }
    for(char i='z';i>='a';i=i-3)
    {
       fprintf(pl,"%c\n",i);
    }
    fclose(pl);

    //Odczyt z pliku 1 bajtu???
    FILE *wsk;
    char w;
    wsk=fopen("plikalfa.txt","r");
    while((w=fgetc(wsk))!=EOF)
    {

        printf("%c",w);
    }
    fclose(wsk);

    //Wpisanie struktury studentow (bin blokow danych)
    /*FILE *st;
    st=fopen("plikst.txt","w");
    struct student o1;
    o1.w=6;
    char name[3]="ere";
    strcpy(o1.name,name);
    fprintf(st,"%d ",o1.w);
    fwrite((const void*)o1.name,1,3,st);
    fclose(st);
    */

    printf("\n");
    FILE *wsk1;
    char w1;
    char slowo[1000]="";
    int wartosc=0;
    int licznik=0;
    struct student tablica[100];
    wsk1=fopen("plikst.txt","r");
    while((w1=fgetc(wsk1))!=EOF)
    {

        //printf("%c",w1);
        if(w1!=' ')
        {
            slowo[licznik]=w1;
            licznik++;
        }
        else
        {
            printf(slowo,"\n");
            if(wartosc%2==0)
            {
                strcpy(tablica[wartosc/2].name,slowo);
            }
            else
            {
                tablica[wartosc/2].w=slowo[licznik] - '0';
            }
            for(int i =0;i<licznik;i++)
            {
                slowo[i]="";
            }
            licznik=0;
            wartosc++;
        }
    }

        printf("\n");
        for( int i =0;i<licznik/2;i++)
        {
            printf(tablica[i].w);
            printf(tablica[i].name);
        }



    fclose(wsk1);






    return 0;
}
