#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct student
{
    int grade;
    int w;
    char name[100];
    struct student *next;
};

void getData(struct student *v)
{
    printf("Podaj ocene: ");
    scanf("%d", &((*v).grade));
    printf("Podaj nazwisko: ");
    scanf("%s", &((*v).name));
}

void printData(struct student *v)
{
    printf("Student %s otrzymuje ocene %d\n",(*v).name,(*v).grade);
}


void print(struct student *p)
{
    while(p)
    {
        printf("%d ",p->w);
        int i=0;
        while(p->name[i]!=NULL)
        {
            printf("%c",p->name[i]);
            i++;
        }
        printf("\n");

        p=p->next;
    }
}

void add(struct student **p,int v,char n[100])  // dodac nazwisko
{
    struct student *NEW, *ww=*p;
    NEW=malloc(sizeof(struct student));
    NEW->w=v;
    strcpy(NEW->name,n);
    NEW->next=0;
    if (ww==0) *p=NEW;
    else
    {
        while (ww->next) ww=ww->next;
        ww->next=NEW;
    }
}

void put(struct student **p, int v, char n[100])
{
    struct student *NEW, *ww=*p;
    NEW=malloc(sizeof(struct student));
    NEW->w=v;
    strcpy(NEW->name,n);
    if (ww==0 || v < ww->w)
    {
        NEW->next = ww;
        *p=NEW;
    }
    else
    {
        while (ww->next!=0 && v > ww->next->w)
            ww = ww->next;
        NEW->next = ww->next;
        ww->next = NEW;
    }
}

void clear(struct student *p)
{
    struct student *pom, *ww=p;

    while (ww)
    {
        pom = ww;
        ww = ww->next;
        free(pom);
    }
}

struct student *search(struct student *p,int v)
{
    while (p && p->w != v) p=p->next;
    return p;
}

void remove_test(struct student **p, int v)
{
    struct student *pom, *ww=*p;
    if (ww==0) return;
    if (v == ww->w)
    {
        *p=ww->next;
        free(ww);
    }
    else
    {
        while (ww->next!=0 && v != ww->next->w) ww = ww->next;
        if (ww->next!=0 && v == ww->next->w)
        {
            pom=ww->next;
            ww->next = ww->next->next;
            free(pom);
        }
    }
}


struct student *copy(struct student *p)
{
    struct student *NEW, *previous, *l2=0;
    while (p)
    {
        NEW=malloc(sizeof(struct student));
        NEW->w = p->w;
        strcpy(NEW->name,p->name);
        if (l2==0) l2=NEW;
        else previous->next=NEW;
        previous=NEW;
        p=p->next;
    }
    if(l2) NEW->next=0;
    return l2;
}

struct student *sum(struct student *p1, struct student *p2)
{
    struct student *k1, *k2, *pom;
    k1 = copy(p1);
    k2 = copy(p2);
    if (k1==0) return k2;
    pom=k1;
    while (pom->next) pom = pom->next;
    pom->next = k2;
    return k1;
}



int main(void)
{

    /*int n;
    printf("Podaj ilosc: studentow: ");
    scanf("%d",&n);
    struct student st;
    getData(&st);
    printData(&st);
    struct student st2;
    getData(&st);
    printData(&st);*/


    struct student *lista, *ws=0;
    printf("dodawanie do listy z sortowaniem i wypisywanie listy\n");
    put(&ws,8,"adam");
    put(&ws,10,"bartek");
    put(&ws,2,"czarek");
    print(ws);
    printf("\n");
    clear(ws);



    printf("szukanie elementu\n");
    struct student *lis1, *wx=0;
    put(&wx,4,"adam");
    put(&wx,14,"bartek");
    put(&wx,10,"czarek");
    lis1=search(wx,14);
    if(lis1) lis1->w = 244;
    print(wx);
    printf("\n");
    clear(wx);


    printf("usuwanie wybranego elementu z listy\n");
    struct student *lis4, *wr=0;
    put(&wr,8,"adam");
    put(&wr,17,"bartek");
    put(&wr,10,"czarek");
    print(wr);
    printf("\n");
    remove_test(&wr,8);
    print(wr);
    printf("\n");
    clear(wr);


   /*
    struct student *listc, *wc=0;
    printf("kopiowanie listy\n");
    put(&wc,8,"adam");
    put(&wc,10,"bartek");
    put(&wc,2,"czarek");
    struct student *lis2, *wy=0;
    lis2=copy(wc);
    put(&wy,20,"daria");
    put(&wy,15,"ewa");
    print(lis2);
    printf("\n");



    printf("dodawanie list\n");
    struct student *suma, *wa=0;
    suma=sum(wc,wy);
    print(suma);
    printf("\n");



    clear(wc);
    clear(wy);
    clear(suma);
*/
    return 0;
  }

