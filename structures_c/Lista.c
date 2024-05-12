#include <stdio.h>
#include <stdlib.h>

struct no
{
    int num;
    struct no *prox;
};
typedef struct no No;
struct lista
{
    struct lista *inicio;
};
typedef struct lista Lista;

No *colocarnalista(Lista *p, int dado)
{
    No *no = (No *)malloc(sizeof(No));
    if (no == NULL)
    {
        printf("Problema na alocação\n");
    }
    else
    {
        no->num = dado;
        no->prox = p->inicio;
        p->inicio = no;
        return no;
    }
}

No *colocarnalista_atras(Lista *p, int dado)
{
    No *no = (No*)malloc(sizeof(No));
    no->num = dado;

    if (p->inicio == NULL)
    {
        p->inicio = no;
        no->prox = NULL;
        
    }
    else
    {
        No *aux = p->inicio;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        no->prox = NULL;
        aux->prox = no;
    }
    return p;
}

void imprimir(Lista *p)
{
    No *aux = p->inicio;
    if (aux == NULL)
    {
        printf("lista vazia \n");
    }
    else
    {
        while (aux != NULL)
        {
            printf("%d \n", aux->num);
            aux = aux->prox;
        }
    }
}

No *inicializalista(Lista *p){
p->inicio = NULL;

}
int main()
{
    Lista *p1 = (Lista *)malloc(sizeof(Lista));
    inicializalista(p1);
    colocarnalista_atras(p1, 10);
    colocarnalista_atras(p1, 20);
     colocarnalista_atras(p1, 20);
      colocarnalista_atras(p1, 20);
       colocarnalista_atras(p1, 20);
        colocarnalista_atras(p1, 20);
    imprimir(p1);
}