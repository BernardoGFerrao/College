#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////Estruturas////////////////////////////////////////////////////////////////////////
typedef struct lista
{
    struct no *primeiro;
    struct no *ultimo;
    int tam;
} Lista;

typedef struct no
{
    struct no *prox;
    int num;
} No;
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

void lista_inserir_inicio(Lista *l, int dado)
{
    No *no = (No *)malloc(sizeof(No));
    if (lista_vazia(l))
    {
        no->num = dado;
        l->primeiro = no;
        l->ultimo = no;
        l->ultimo->prox = l->primeiro;
        l->tam = l->tam + 1;
    }
    else
    {
        no->num = dado;
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

void lista_inserir_final(Lista *l, int dado)
{
    No *no = (No *)malloc(sizeof(No));
    no->num = dado;
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

void lista_inserir_posicao(Lista *l, int dado, int pos)
{
    No *no = (No *)malloc(sizeof(No));
    no->num = dado;
    if (l->primeiro == NULL)
    {
        printf("Lista vazia!");
    }
    else
    {
        No *aux = l->primeiro;
        int agora = 1;
        while (agora < pos)
        {
            aux = aux->prox;
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

No *lista_remover_maior(Lista *l)
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
            printf("oi");
            if (aux->num > maior)
            {
                maior = aux->num;
                remover = aux;
            }
        i++;
        aux = aux->prox;
        }
        printf("%d", maior); // achou o maior
        /*
        if(aux == l->primeiro){ //primeiro numero
        lista_remover_primeiro(l);
        return remover;
        }
        else{

        }
        */
    }
}

void lista_liberar(Lista *l)
{
    if (lista_vazia(l))
    {
        free(l);
    }
    else
    {
        No *atual, *prox;
        int i = 0;
        atual = l->primeiro;
        while (i < l->tam)
        {
            prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }
}

void lista_imprimir(Lista *l)
{
    if (l->primeiro == NULL)
    {
        printf("Lista vazia");
    }
    else
    {
        No *aux = l->primeiro;
        int tam = l->tam;
        int i = 0;
        printf("Lista:");
        while (tam > 0)
        {
            printf("\n%d- %d", i, aux->num);
            aux = aux->prox;
            tam--;
            i++;
        }
    }
}

////////////////////////////////////////////////////////Main///////////////////////////////////////////////////////////////////////////
int main()
{
    int r = '10';
    int dado = 10;
    Lista *l1 = (Lista *)malloc(sizeof(Lista));
    No *removido;
    lista_inicializa(l1);
    while (r != 10)
    {
        system("cls");
        printf("Teste das funcoes: \n");
        printf("1 - Verificar lista vazia\n");        // feito
        printf("2 - inserir o elemento no inicio\n"); // feito
        printf("3 - Inserir em posicao\n");
        printf("4 - Inserir no final\n");           // feito
        printf("5 - Remover no inicio\n");          // feito
        printf("6 - Remove elemento em posicao\n"); // feito
        printf("7 - Verificar Tamanho\n");          // feito
        printf("8 - Maior: retorna o maior elemento da lista (removendo-o da lista).\n");
        printf("9 - Imprimir Lista\n");   // feito
        printf("10 - Finalizar Lista\n"); // feito
        scanf("%d", &r);
        fflush(stdin);
        switch (r)
        {
        case 1:
            if (lista_vazia(l1) == 0)
            {
                printf("\nLista nao esta vazia\n");
            }
            else
            {
                printf("\nLista esta vazia\n");
            }
            printf("\n");
            system("pause");
            system("cls");
            break;

        case 2:
            printf("Digite um numero para ser inserido ");
            scanf("%d", &dado);
            lista_inserir_inicio(l1, dado);
            printf("\n numero inserido com sucesso!\n");
            system("pause");
            fflush(stdin);
            system("cls");
            break;

        case 3:
            printf("\n");
            system("pause");
            system("cls");
            break;

        case 4:
            printf("Digite um numero para ser inserido ");
            scanf("%d", &dado);
            lista_inserir_final(l1, dado);
            printf("\n numero inserido com sucesso!\n");
            system("pause");
            system("cls");
            break;

        case 5:
            removido = lista_remover_primeiro(l1);

            if (removido)
            {
                printf("\n Removido com sucesso\n");
                free(removido);
            }
            else
            {
                printf("Lista vazia\n");
            }
            system("pause");
            system("cls");
            break;

        case 6:
            printf("digite uma posicao a ser removido: \n");
            scanf("%d", &dado);
            removido = lista_remover_posicao(l1, dado);

            if (removido)
            {
                printf("\n Removido com sucesso\n");
                free(removido);
            }
            else
            {
                printf("Inexistente");
            }
            system("pause");
            system("cls");
            break;

        case 7:
            printf("\nTamanho : %d\n", l1->tam);
            system("pause");
            system("cls");
            break;

        case 8:
            lista_remover_maior(l1);
            printf("\n");
            system("pause");
            system("cls");
            break;

        case 9:
            lista_imprimir(l1);
            printf("\n");
            system("pause");
            system("cls");
            break;

        case 10:
            lista_liberar(l1);
            printf("\n");
            printf("Sua lista foi liberada, Obrigado!");
            break;
        }
    }
}