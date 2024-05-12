#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioteca.h"
//////////////////////////////////////////////////////Funções////////////////////////////////////////////////////////////////////////
void lista_inicializa(Lista *l)
{
    l->primeiro = NULL;
    l->ultimo = NULL;
    l->tam = 0;
}

int lista_vazia(Lista *l)
{
    if (l->primeiro == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int lista_tamanho(Lista *l)
{
    if (lista_vazia(l))
    {
        return 0;
    }
    else
    {
        return l->tam;
    }
}
void lista_inserir_inicio(Lista *l, int dado, char string[31])
{
    No *no = (No *)malloc(sizeof(No));
    no->num = dado;
    strcpy(no->string, string);
    if (lista_vazia(l))
    {
        l->primeiro = no;
        l->ultimo = no;
        l->ultimo->prox = l->primeiro;
        l->tam = l->tam + 1;
    }
    else
    {
        no->prox = l->primeiro;
        l->primeiro = no;
        if (l->ultimo == NULL)
        {
            l->ultimo = no;
        }
        else
        {
            l->ultimo->prox = l->primeiro;
        }
        l->tam++;
    }
}

void lista_inserir_final(Lista *l, int dado, char string[31])
{
    No *no = (No *)malloc(sizeof(No));
    no->num = dado;
    strcpy(no->string, string);
    if (lista_vazia(l))
    {
        l->primeiro = no;
        l->ultimo = no;
        l->ultimo->prox = l->primeiro;
    }
    else
    {
        l->ultimo->prox = no;
        l->ultimo = no;
        l->ultimo->prox = l->primeiro;
    }
    l->tam = l->tam + 1;
}

void lista_inserir_posicao(Lista *l, int dado, int pos, char string[31])
{
    No *no = (No *)malloc(sizeof(No)), *aux = l->primeiro, *aux2;
    no->num = dado;
    int i = 0;
    strcpy(no->string, string);
    if (lista_vazia(l)) // vazia
    {
        if (pos != 0)
        {
            printf("Lista vazia - Deve adicionar algo na posicao zero primeiro");
        }
        else if (pos == 0)
        {
            lista_inserir_inicio(l, dado, string);
        }
    }
    else // ja tem algo
    {
        if (pos < 0)
        {
            printf("posicao invalida");
        }
        else if (pos > l->tam)
        {
            printf("posicao invalida");
        }
        else
        { // posicao valida
            if (pos == 0)
            { // inicio
                lista_inserir_inicio(l, dado, string);
            }
            else if (pos == l->tam)
            {
            lista_inserir_final(l, dado, string);
            }
            else
            {
                while (pos != i + 1)
                {
                    aux = aux->prox;
                    i++;
                }
                no->prox = aux->prox;
                aux->prox = no;
                l->tam++;
            }
        }
    }
}

No *lista_remover_primeiro(Lista *l)
{
    No *remover = NULL;
    if (lista_vazia(l))
    {
        remover = NULL;
    }
    else if (l->primeiro == l->ultimo)
    { // um só nó
        remover = l->primeiro;
        l->primeiro = NULL;
        l->ultimo = NULL;
        l->tam--;
    } // Primeiro nó
    else
    {
        remover = l->primeiro;
        l->primeiro = remover->prox;
        l->ultimo->prox = l->primeiro;
        l->tam--;
    }
    return remover;
}

No *lista_remover_posicao(Lista *l, int pos)
{
    No *aux, *remover = NULL;
    int i = 0;
    if (lista_vazia(l)) // lista vazia
    {
        remover = NULL;
        return remover;
    }
    else
    {
        if (pos == 0) // primeira posicao
        {
            remover = lista_remover_primeiro(l);
            return remover;
        }
        else
        {

            if (pos > l->tam - 1) // limite maximo
            {
                remover = NULL;
                return remover;
            }
            else if (pos < 0) // limite minimo
            {
                remover = NULL;
                return remover;
            }
            else if (pos == l->tam - 1) // Último número
            {
                aux = l->primeiro;
                while (i != l->tam - 2)
                {
                    aux = aux->prox;
                    i++;
                }
                remover = aux->prox;
                l->ultimo = aux;
                aux->prox = remover->prox;
                l->tam--;
                return remover;
            }
            else // numero no meio
            {
                aux = l->primeiro;
                while (i != pos - 1 && i < l->tam)
                {
                    aux = aux->prox;
                    i++;
                } // achou a posição
                remover = aux->prox;
                aux->prox = remover->prox;
                l->tam--;
                return remover;
            }
        }
    }
}

int lista_remover_maior(Lista *l)
{
    No *remover = NULL, *aux = l->primeiro;
    int maior = 0, i = 0, tam;
    if (lista_vazia(l))
    {
        return NULL;
    }
    else
    {
        tam = l->tam;
        while (i < tam)
        {
            if (aux->num > maior)
            {
                maior = aux->num;
            }
            i++;
            aux = aux->prox;
        }
        if (l->primeiro->num == maior) // primeiro
        {
            lista_remover_primeiro(l);
        }
        else // ultimo ou no meio
        {
            aux = l->primeiro;
            while (aux->prox != l->primeiro && aux->prox->num != maior)
            {
                aux = aux->prox;
            }
            if (aux->prox->num == maior)
            {                               // o proximo contem o número desejado
                if (l->ultimo == aux->prox) // ultimo numero
                {
                    remover = aux->prox;
                    aux->prox = remover->prox;
                    l->ultimo = aux;
                    l->tam--;
                }
                else
                { // no meio
                    remover = aux->prox;
                    aux->prox = remover->prox;
                    l->tam--;
                }
            }
        }

        return maior;
    }
}
void lista_liberar(Lista *l)
{
    if (lista_vazia(l))
    {
        free(l);
        return NULL;
    }
    else
    {
        No *atual, *prox;
        int i = 0;
        atual = l->primeiro;
        while (i != l->tam-1)
        {
            prox = atual->prox;
            free(atual);
            atual = prox;
        }
        free(l);
        return NULL;
    }
}

void lista_imprimir(Lista *l)
{
    if (lista_vazia(l))
    {
       printf("Lista vazia!");
    }
    else
    {
        No *aux = l->primeiro;
        int tam = l->tam;
        int i = 0;
        printf("  pos\n");
        while (tam > 0)
        {
            printf("\n   %d  |  ", i);
            lista_imprimir_elemento(aux);
            aux = aux->prox;
            tam--;
            i++;
        }
    }
}

void lista_imprimir_ordenado(Lista *l)
{
    No *aux = l->primeiro;
    int v[l->tam], i = 0, aux2, j;
    if(lista_vazia(l)){
    printf("Lista vazia!");
    return NULL;
	}
    while (i < l->tam)
    {
        v[i] = aux->num;
        aux = aux->prox;
        i++;
    }

    for (i = 0; i < l->tam; i++)
    {
        for (j = 0; j < l->tam - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                aux2 = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux2;
            }
        }
    }
    i = 0;
    aux = l->primeiro;
    printf("elementos desordenados: ");
    lista_imprimir(l);
    printf("\nelementos ordenados: ");
    printf("\n  pos | num | string\n");
    while (i < l->tam)
    {
        if (aux->num == v[i])
        {
            printf("\n   %d  -  ", i);
            lista_imprimir_elemento(aux);
            i++;
        }
        else
        {
            aux = aux->prox;
        }
    }
}

void lista_imprimir_elemento(No *e)
{
    printf(" \t\t\t\t\t\t%s %d \n",e->string,e->num);
}

char lista_retorna_string(No *e)
{
    return e->string;
}

int lista_retorna_int(No *e)
{
    return e->num;
}

void limpa_tela()
{
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else
    #endif
}


