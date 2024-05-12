#include <stdio.h>
#include <stdlib.h>

struct fila
{
    struct fila *primeiro;
};
typedef struct fila Fila;

struct no
{
    struct no *prox;
    int num;
};
typedef struct no No;

Fila *fila_criar()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    return f;
}

void fila_inicializa(Fila *f)
{
    f->primeiro = NULL;
}

void fila_inserir(Fila *f, int dado)
{
    No *no = (No *)malloc(sizeof(No));
    no->num = dado;
    if (f->primeiro == NULL)
    {
        f->primeiro = no;
        no->prox = NULL;
    }
    else
    {
        No *aux = f->primeiro;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = NULL;
    }
}

void fila_imprimir(Fila *f)
{
    No *aux = f->primeiro;
    if (aux == NULL)
    {
        printf("Fila vazia");
    }
    else
    {
        while (aux != NULL)
        {
            printf("- %d\n", aux->num);
            aux = aux->prox;
        }
    }
}

int fila_retirar(Fila *f)
{
    No *aux = f->primeiro;
    if (aux == NULL)
    {
        printf("fila vazia");
    }
    else
    {
        int v;
        v = aux->num;
        f->primeiro = aux->prox;
        aux->prox = NULL;
        return v;
    }
}

void fila_concatenar(Fila *f1,Fila *f2){
int v;
No *aux = f2->primeiro;
while(aux != NULL){
aux = aux->prox;
v = fila_retirar(f2);
fila_inserir(f1,v);   
}
}

int main()
{
    Fila *f1,*f2;
    f1 = fila_criar();
    fila_inicializa(f1);
    fila_inserir(f1, 20);
    fila_inserir(f1, 30);
    fila_inserir(f1, 40);
    fila_inserir(f1, 50);
    printf("Fila 1:\n");
    fila_imprimir(f1);
   /* fila_retirar(f1);
    printf("Fila 1:\n");
    fila_imprimir(f1);
    fila_retirar(f1);
    printf("Fila 1:\n");
    fila_imprimir(f1);
    fila_retirar(f1);
    printf("Fila 1:\n");
    fila_imprimir(f1);
    fila_retirar(f1);
    printf("Fila 1:\n");
    fila_retirar(f1);*/
    f2 = fila_criar();
    fila_inicializa(f2);
    fila_inserir(f2, 100);
    fila_inserir(f2, 101);
    fila_inserir(f2, 102);
    fila_inserir(f2, 103);
    printf("Fila 2:\n");
    fila_imprimir(f2);
    fila_concatenar(f1,f2);
    printf("Depois de concatenados:\n");
    fila_imprimir(f2);
    printf("\n");
    fila_imprimir(f1);
}
