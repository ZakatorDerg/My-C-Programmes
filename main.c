#include <stdio.h>
#include <malloc.h>

struct tree
{
    int w;
    struct tree *left,*right;
};

void wstaw(struct tree **p,int v)
{
    struct tree *new,*ws=*p,*next;
    new=malloc(sizeof(struct tree));
    new->w=v;
    new->left=new->right=0;
    if(ws==0) *p=new;
    else
    {
        while(1)
        {
            if(v<ws->w)
            {
                if(ws->left==0)
                {
                    ws->left=new;
                    break;
                }
                else ws=ws->left;
            }
            else
            {
                if(ws->right==0)
                {
                    ws->right=new;
                    break;
                }
                else ws=ws->right;
            }
        }
    }
}

void wypisz(struct tree *p)
{
    if(p==0) return;
    wypisz(p->left);
    printf("%d\n",p->w);
    wypisz(p->right);
}

struct tree *search(struct tree *p, int v)
{
    if(p==NULL || v==p->w)
    {
        return p;
    }
    if (v < p->w)
    return search(p->left,v);
  else
    return search(p->right,v);
};

int main(void)
{
    printf("wstawianie i wypisywanie drzewa\n");
    struct tree *root=0;
    wstaw(&root,10);
    wstaw(&root,5);
    wstaw(&root,1);
    wstaw(&root,20);
    wstaw(&root,2);
    wypisz(root);
    printf("\n");
    printf("wyszukiwanie elementu w drzewie\n");
    root=search(root,2);
    if(root) root->w =244;
    wypisz(root);
    printf("\n");





    return 0;
}
