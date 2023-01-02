#include <stdio.h>
#include <stdlib.h>

#define WYGRANA 1000
#define PRZEGRANA -1000

int ocena(char pl[3][3])
{
    if (pl[0][0]=='x' && pl[0][1]=='x' && pl[0][2]=='x') return WYGRANA;
    if (pl[1][0]=='x' && pl[1][1]=='x' && pl[1][2]=='x') return WYGRANA;
    if (pl[2][0]=='x' && pl[2][1]=='x' && pl[2][2]=='x') return WYGRANA;
    if (pl[0][0]=='x' && pl[1][0]=='x' && pl[2][0]=='x') return WYGRANA;
    if (pl[0][1]=='x' && pl[1][1]=='x' && pl[2][1]=='x') return WYGRANA;
    if (pl[0][2]=='x' && pl[1][2]=='x' && pl[2][2]=='x') return WYGRANA;
    if (pl[0][0]=='x' && pl[1][1]=='x' && pl[2][2]=='x') return WYGRANA;
    if (pl[0][2]=='x' && pl[1][1]=='x' && pl[2][0]=='x') return WYGRANA;
    if (pl[0][0]=='o' && pl[0][1]=='o' && pl[0][2]=='o') return PRZEGRANA;
    if (pl[1][0]=='o' && pl[1][1]=='o' && pl[1][2]=='o') return PRZEGRANA;
    if (pl[2][0]=='o' && pl[2][1]=='o' && pl[2][2]=='o') return PRZEGRANA;
    if (pl[0][0]=='o' && pl[1][0]=='o' && pl[2][0]=='o') return PRZEGRANA;
    if (pl[0][1]=='o' && pl[1][1]=='o' && pl[2][1]=='o') return PRZEGRANA;
    if (pl[0][2]=='o' && pl[1][2]=='o' && pl[2][2]=='o') return PRZEGRANA;
    if (pl[0][0]=='o' && pl[1][1]=='o' && pl[2][2]=='o') return PRZEGRANA;
    if (pl[0][2]=='o' && pl[1][1]=='o' && pl[2][0]=='o') return PRZEGRANA;
    return 0;
}

void wypisz(char p[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("+---");
        }
        printf("+\n");
        for(int j=0;j<3;j++)
        {
            printf("| %c ",p[i][j]);
        }
        printf("|\n");
    }
    for(int j=0;j<3;j++)
        {
            printf("+---");
        }
        printf("+\n");
}

int najlepszy(char pl[3][3], int tryb, int *x, int *y)
{
    int wynik,wmax,wmin, px,py,nx,ny,brak_ruchu=1;
    wynik=ocena(pl);
    if (tryb<=0 || wynik==WYGRANA || wynik==PRZEGRANA) return wynik;
    if (tryb%2==0)  //RUCH KOMPUTERA
    {
        for (px=0, wmax=2*PRZEGRANA; px<3; px++)
            for (py=0; py<3; py++)
                if (pl[px][py]==' ')   //warunki ruchu
                {
                    pl[px][py]='x'; //ruch
                    wynik=najlepszy(pl,tryb-1,&nx,&ny); //nx,ny - niewykorzystane
                    pl[px][py]=' '; //cofniecie ruchu
                    if (wynik>wmax)
                    {
                        wmax=wynik;
                        *x=px;
                        *y=py;
                    }
                    brak_ruchu=0;
                }
        if (brak_ruchu) return 0;
        else return wmax;
    }
    else   //RUCH PRZECIWNIKA
    {
        for (px=0, wmin=2*WYGRANA; px<3; px++)
            for (py=0; py<3; py++)
                if (pl[px][py]==' ')   //warunki ruchu
                {
                    pl[px][py]='o'; //ruch
                    wynik=najlepszy(pl,tryb-1,&nx,&ny); //nx,ny - niewykorzystane
                    pl[px][py]=' '; //cofniecie ruchu
                    if (wynik<wmin)
                    {
                        wmin=wynik;
                        *x=px;
                        *y=py;
                    }
                    brak_ruchu=0;
                }
        if (brak_ruchu) return 0;
        else return wmin;
    }
}

int main(void)
{
    char pl[3][3];
    int x, y, wyn, nr_ruchu=0;
    for (x=0; x<3; x++) for (y=0; y<3; y++) pl[y][x]=' ';
    while(1)
    {
        najlepszy(pl,10,&x, &y);
        pl[x][y]='x';
        wypisz(pl); //funkcja wypisująca zawartość planszy (dwie pętle z printf)
        wyn = ocena(pl);
        if (wyn==WYGRANA)
        {
            printf("przegrales\n");
            return 0;
        }
        if (wyn==PRZEGRANA)
        {
            printf("wygrales\n");
            return 0;
        }
        if (nr_ruchu++==4)
        {
            printf("remis\n");
            return 0;
        }
        printf("podaj ruch");
        scanf("%d%d",&x,&y);
        pl[y][x]='o';
        wypisz(pl);
        if (wyn==WYGRANA)
        {
            printf("przegrales\n");
            return 0;
        }
        if (wyn==PRZEGRANA)
        {
            printf("wygrales\n");
            return 0;
        }
    }
    return 0;
}
