#include <stdio.h>
#include <stdlib.h>

/*
        OZNACZENIA LICZBOWE POSZCZEGOLNYCH FIGUR
GRACZ:
0-krol
1-hetman
2-wieza
3-goniec
4-skoczek
5-pionek

KOMPUTER:
6-krol_k
7-hetman_k
8-wieza_k
9-goniec_k
10-skoczek_k
11-pionek_k

12-pole puste
*/

#define WIN 1000
#define LOSE -1000
#define EMPTY 12


int MAX_KIER[]= {8,8,4,4,8,3,8,8,4,4,8,3,0};
int MAX_ODL[]= {2,8,8,8,2,2,2,8,8,8,2,2,0};

int WX[12][8]={
{0,1,1,1,0,-1,-1,-1},
{0,1,1,1,0,-1,-1,-1},
{0,1,0,-1},
{1,1,-1,-1},
{1,2,2,1,-1,-2,-2,-1},
{-1,0,1},
{0,1,1,1,0,-1,-1,-1},
{0,1,1,1,0,-1,-1,-1},
{0,1,0,-1},
{1,1,-1,-1},
{1,2,2,1,-1,-2,-2,-1},
{-1,0,1}
};

int WY[12][8]={
{-1,-1,0,1,1,1,0,-1},
{-1,-1,0,1,1,1,0,-1},
{-1,0,1,0},
{-1,1,1,-1},
{-2,-1,1,2,2,1,-1,-2},
{-1,-1,-1},
{-1,-1,0,1,1,1,0,-1},
{-1,-1,0,1,1,1,0,-1},
{-1,0,1,0},
{-1,1,1,-1},
{-2,-1,1,2,2,1,-1,-2},
{1,1,1}
};

int ocena(char plansza[8][8])
{
    int i,j,w=0;
    int wartosc[]={LOSE,-9,-5,-4,-3,-1,WIN,9,5,4,3,1,0};
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
            w+=wartosc[plansza[i][j]];
    return w;
}

int king(char plansza[8][8])
{
    int gr=0,kom=0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(plansza[j][i]==0)
                gr++;
            if(plansza[j][i]==6)
                kom++;
        }
    }
    if(gr==0)
       {
           printf("You lost\n");
           return 1;
       }
    else if(kom==0)
    {
        printf("You won\n");
        return 2;
    }
    else
        return 0;

}

void wypisz(char pl[8][8])
{
    char figury[]="khwgspKHWGSP ";
    printf(" 0 1 2 3 4 5 6 7\n");
    printf("-----------------\n");
    for(int i=0; i<8; i++)
    {
        printf("|");
        for(int j=0; j<8; j++)
        {
            printf("%c|",figury[pl[j][i]]);
        }
        printf(" %d\n",i);
    }
    printf("-----------------\n");
}


int najlepszy(char plansza[8][8],int tryb,int *x,int *y,int *k, int *o)
{
    int px_pom,py_pom,o_pom,k_pom,px,py,dx,dy,kierunek,odleglosc;
    int wynik,wmax,wmin,ruch_fig,bita_fig;

    wynik=ocena(plansza);
    if(tryb==0||2*wynik>WIN||2*wynik<LOSE)
        return wynik;

    if(tryb%2==0)   //sprawdza czy komputer gra
    {
        for(px=0,wmax=100*LOSE; px<8; px++)
            for(py=0; py<8; py++)    //2 petle do poruszania sie po szachownicy
                if (plansza[px][py]>=6 && plansza[px][py]<12)   // sprawdza czy pole to figura komputera
                    for(kierunek=0; kierunek<MAX_KIER[plansza[px][py]]; kierunek++)   //wykrywa kierunek ruchu figury KOMPUTERA
                        for(odleglosc=1; odleglosc<MAX_ODL[plansza[px][py]]; odleglosc++)    //wykrywa odległosc ruchu figury KOMPUTERA
                        {
                            dx=(odleglosc-1)*WX[plansza[px][py]][kierunek];  //przemieszczenie wspolrzednej x figury
                            dy=(odleglosc-1)*WY[plansza[px][py]][kierunek];  //przemieszczenie wspolrzednej y figury
                            if(odleglosc>=2 && plansza[px+dx][py+dy]!=EMPTY) break; //sprawdza czy zadna figura nie stoi na drodze figury poruszajacej sie
                            dx=odleglosc*WX[plansza[px][py]][kierunek];
                            dy=odleglosc*WY[plansza[px][py]][kierunek];
                            if(px+dx>=0 && px+dx<8 && py+dy>=0 && py+dy<8)   //sprawdza czy ruch miesci sie w szachownicy
                                if(plansza[px+dx][py+dy]==EMPTY || plansza[px+dx][py+dy]<=5)  //sprawdza czy ruch jest na pole puste LUB z figura przeciwnika
                                {
                                    if(plansza[px][py]!=11 || (plansza[px+dx][py+dy]==EMPTY && dx==0) || (plansza[px+dx][py+dy]!=EMPTY && dx!=0))  //warunek dla pionka
                                    {
                                        ruch_fig=plansza[px][py];     //bicie figury przeciwnika przez komputer lub po prostu ruch
                                        bita_fig=plansza[px+dx][py+dy];
                                        plansza[px+dx][py+dy]=plansza[px][py];
                                        plansza[px][py]=EMPTY;
                                        if(plansza[px+dx][py+dy]==11 && py+dy==7)   // sprawdza czy pionek doszedl do drugiego konca planszy
                                            plansza[px+dx][py+dy]=7; // jesli tak to zamienia go na hetmana
                                        wynik=najlepszy(plansza,tryb-1,&px_pom,&py_pom,&o_pom,&k_pom);  //REKURENCJA
                                        plansza[px][py]=ruch_fig;
                                        plansza[px+dx][py+dy]=bita_fig;
                                        if(wynik>=wmax)
                                        {
                                            wmax=wynik;
                                            *x=px;
                                            *y=py;
                                            *k=kierunek;
                                            *o=odleglosc;
                                        }
                                    }
                                }
                        }
        return wmax;
    }
    else    //sprawdza czy przeciwnik gra
    {
        for(px=0,wmin=100*WIN; px<8; px++)
            for(py=0; py<8; py++)   //2 petle do poruszania sie po szachownicy
                if (plansza[px][py]<=5)   // sprawdza czy pole to figura przeciwnika
                    for(kierunek=0; kierunek<MAX_KIER[plansza[px][py]]; kierunek++)     //wykrywa kierunek ruchu figury GRACZA
                        for(odleglosc=1; odleglosc<MAX_ODL[plansza[px][py]]; odleglosc++)       //wykrywa odleglosc ruchu figury GRACZA
                        {
                            dx=(odleglosc-1)*WX[plansza[px][py]][kierunek]; //przemieszczenie wspolrzednej x figury
                            dy=(odleglosc-1)*WY[plansza[px][py]][kierunek]; //przemieszczenie wspolrzednej y figury
                            if(odleglosc>=2 && plansza[px+dx][py+dy]!=EMPTY) break; //sprawdza czy zadna figura nie stoi na drodze figury poruszajacej sie
                            dx=odleglosc*WX[plansza[px][py]][kierunek];
                            dy=odleglosc*WY[plansza[px][py]][kierunek];
                            if(px+dx>=0 && px+dx<8 && py+dy>=0 && py+dy<8)   //sprawdza czy ruch miesci sie w szachownicy
                                if(plansza[px+dx][py+dy]>=6)  //sprawdza czy ruch jest na pole puste LUB z figure komputera
                                {
                                    if(plansza[px][py]!=5 || (plansza[px+dx][py+dy]==EMPTY && dx==0) || (plansza[px+dx][py+dy]!=EMPTY && dx!=0))
                                    {
                                        ruch_fig=plansza[px][py];     //bicie figury komputera przez przeciwnika lub po prostu ruch
                                        bita_fig=plansza[px+dx][py+dy];
                                        plansza[px+dx][py+dy]=plansza[px][py];
                                        plansza[px][py]=EMPTY;
                                        if(plansza[px+dx][py+dy]==5 && py+dy==0)   // sprawdza czy pionek doszedl do drugiego koñca planszy
                                            plansza[px+dx][py+dy]=1; // jesli tak to zamienia go na hetmana
                                        wynik=najlepszy(plansza,tryb-1,&px_pom,&py_pom,&o_pom,&k_pom);  //REKURENCJA
                                        plansza[px][py]=ruch_fig;
                                        plansza[px+dx][py+dy]=bita_fig;
                                        if(wynik<=wmin)
                                        {
                                            wmin=wynik;
                                            *x=px;
                                            *y=py;
                                            *k=kierunek;
                                            *o=odleglosc;
                                        }
                                    }
                                }
                        }
        return wmin;
    }
}


int main(void)
{
    char pl[8][8]= {8,11,12,12,12,12,5,2,       //deklaracja planszy
                    10,11,12,12,12,12,5,4,
                    9,11,12,12,12,12,5,3,
                    6,11,12,0,12,12,5,12,
                    7,11,12,12,12,12,5,1,
                    9,11,12,12,12,12,5,3,
                    10,11,12,12,12,12,5,4,
                    8,11,12,12,12,12,5,2
                   };
    int x,y,wyn,k,o,dx,dy,x2,y2,temp;

    while(king(pl)==0)
    {

        temp=najlepszy(pl,4,&x,&y,&k,&o);  //wywolanie funkcji drzewa ruchow
        printf("%d\n",temp);

        dx=o*WX[pl[x][y]][k];
        dy=o*WY[pl[x][y]][k];
        pl[x+dx][y+dy]=pl[x][y];
        pl[x][y]=12;

        if(pl[x+dx][y+dy]==11 && y+dy==7)   //spr czy pionek KOMPUTERA zamienia sie na hetmana
            pl[x=dx][y+dy]=7;

        wypisz(pl);   //wypisuje ruch KOMPUTERA
        if(king(pl)==1) break;

        printf("podaj ruch (skad dokad): ");
        scanf("%d%d%d%d",&x,&y,&x2,&y2);   //GRACZ podaje 2 pary wspolrzednych

        pl[x2][y2]=pl[x][y];
        pl[x][y]=EMPTY;

        if (pl[x2][y2]==5 && y2==0) //spr czy pionek GRACZA zamienia sie na hetmana
            pl[x2][y2]=1;


        wypisz(pl);  //wypisuje ruch GRACZA
    }

    return 0;
}
