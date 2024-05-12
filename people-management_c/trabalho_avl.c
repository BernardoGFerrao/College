
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa
{
    char nome[25];
    int idade;
    float peso;
    float altura;
    int cod;
} Pessoa;

typedef struct no
{
    Pessoa *pessoa;
    struct no *esquerdo, *direito;
    short altura;
} No;

/*
    Função que cria um novo nó
    x -> valor a ser inserido no nó
    Retorna: o endereço do nó criado
*/
No *novoNo(Pessoa *x)
{
    No *novo = (No*)malloc(sizeof(No));
    if (novo)
    {
        novo->pessoa = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    }
    else
        printf("\nERRO ao alocar no!\n");
    return novo;
}

/*
    Retorna o maior dentre dois valores
    a, b -> altura de dois nós da árvore
*/
short maior(short a, short b)
{
    return (a > b) ? a : b;
}

//  Retorna a altura de um nó ou -1 caso ele seja null
short alturaDoNo(No *no)
{
    if (no == NULL)
        return -1;
    else
        return no->altura;
}

//   Calcula e retorna o fator de balanceamento de um nó
short fatorDeBalanceamento(No *no)
{
    if (no)
        return (alturaDoNo(no->esquerdo) - alturaDoNo(no->direito));
    else
        return 0;
}

// --------- ROTAÇÕES ---------------------------

// função para a rotação à esquerda
No *rotacaoEsquerda(No *r)
{
    No *y, *f;

    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

// função para a rotação à direita
No *rotacaoDireita(No *r)
{
    No *y, *f;

    y = r->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaDoNo(r->esquerdo), alturaDoNo(r->direito)) + 1;
    y->altura = maior(alturaDoNo(y->esquerdo), alturaDoNo(y->direito)) + 1;

    return y;
}

No *rotacaoEsquerdaDireita(No *r)
{
    r->esquerdo = rotacaoEsquerda(r->esquerdo);
    return rotacaoDireita(r);
}

No *rotacaoDireitaEsquerda(No *r)
{
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}

/*
    Função para realizar o balanceamento da árvore após uma inserção ou remoção
    Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
No *balancear(No *raiz)
{
    short fb = fatorDeBalanceamento(raiz);

    // Rotação à esquerda
    if (fb < -1 && fatorDeBalanceamento(raiz->direito) <= 0)
        raiz = rotacaoEsquerda(raiz);

    // Rotação à direita
    else if (fb > 1 && fatorDeBalanceamento(raiz->esquerdo) >= 0)
        raiz = rotacaoDireita(raiz);

    // Rotação dupla à esquerda
    else if (fb > 1 && fatorDeBalanceamento(raiz->esquerdo) < 0)
        raiz = rotacaoEsquerdaDireita(raiz);

    // Rotação dupla à direita
    else if (fb < -1 && fatorDeBalanceamento(raiz->direito) > 0)
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;
}

/*
    Insere um novo nó na árvore
    raiz -> raiz da árvore
    x -> valor a ser inserido
    Retorno: endereço do novo nó ou nova raiz após o balanceamento
*/
No *inserir(No *raiz, Pessoa *x)
{
    if (raiz == NULL) // árvore vazia
        return novoNo(x);
    else
    { // inserção será à esquerda ou à direita
        if (x->cod < raiz->pessoa->cod)
            raiz->esquerdo = inserir(raiz->esquerdo, x);
        else if (x->cod > raiz->pessoa->cod)
            raiz->direito = inserir(raiz->direito, x);
        else
            printf("\nInsercao nao realizada!\nO elemento %d a existe!\n", x);
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

    // verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

/*
    Função para remover um nó da Árvore binária balanceada
    Pode ser necessário rebalancear a árvore e a raiz pode ser alterada
    por isso precisamos retornar a raiz
*/
No *remover(No *raiz, int chave)
{
    if (raiz == NULL)
    {
        printf("Valor nao encontrado!\n");
        return NULL;
    }
    else
    { // procura o nó a remover
        if (raiz->pessoa->cod == chave)
        {
            // remove nós folhas (nós sem filhos)
            if (raiz->esquerdo == NULL && raiz->direito == NULL)
            {
                free(raiz);
                printf("Elemento folha removido: %d !\n", chave);
                return NULL;
            }
            else
            {
                // remover nós que possuem 2 filhos
                if (raiz->esquerdo != NULL && raiz->direito != NULL)
                {
                    No *aux = raiz->esquerdo;
                    Pessoa *pessoa_aux;
                    while (aux->direito != NULL)
                    {
                        aux = aux->direito;
                    }
                    pessoa_aux = raiz->pessoa;
                    raiz->pessoa = aux->pessoa;
                    aux->pessoa = pessoa_aux;
                    printf("Elemento trocado: %d !\n", chave);
                    raiz->esquerdo = remover(raiz->esquerdo, chave);
                    return raiz;
                }
                else
                {
                    // remover nós que possuem apenas 1 filho
                    No *aux;
                    if (raiz->esquerdo != NULL)
                        aux = raiz->esquerdo;
                    else
                        aux = raiz->direito;
                    free(raiz);
                    printf("Elemento com 1 filho removido: %d !\n", chave);
                    return aux;
                }
            }
        }
        else
        {
            if (chave < raiz->pessoa->cod)
                raiz->esquerdo = remover(raiz->esquerdo, chave);
            else
                raiz->direito = remover(raiz->direito, chave);
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(alturaDoNo(raiz->esquerdo), alturaDoNo(raiz->direito)) + 1;

        // verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}

void imprimir(No *raiz, int nivel)
{
    int i;
    if (raiz)
    {
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");

        for (i = 0; i < nivel; i++)
            printf("\t");

        printf("Codigo: %d Nome: %s Idade: %d Peso: %.2f Altura: %.2f\n", raiz->pessoa->cod, raiz->pessoa->nome, raiz->pessoa->idade, raiz->pessoa->peso, raiz->pessoa->altura);
        imprimir(raiz->esquerdo, nivel + 1);
    }
}

void liberar(No *raiz)
{
    if (raiz != NULL)
    {
        liberar(raiz->direito);
        liberar(raiz->esquerdo);
        free(raiz);
    }
}

int main()
{

    int opcao = 0, cod;
    No *raiz = NULL;
    Pessoa *p;
    while (opcao != 9)
    {
        system("cls");
        printf("\t\t\t\t    Seja bem vindo ao sistema da academia Phisical Boost\n");
        printf("\t\t\t\t\t        O que deseja fazer?\n\n");
        printf("\t\t\t\t\t        1 - incluir pessoas\n\n");
        printf("\t\t\t\t\t        2 - Remover pessoa\n\n");
        printf("\t\t\t\t\t        3 - Imprimir de forma ordenada\n\n");
        printf("\t\t\t\t\t        4 - Imprimir quantidade de pessoas\n\n");
        printf("\t\t\t\t\t        5 - Imprimir altura\n\n");
        printf("\t\t\t\t\t        6 - Imprimir altura\n\n");
        printf("\t\t\t\t\t        7 - Buscar e imprimir\n\n");
        printf("\t\t\t\t\t        8 - Buscar e editar\n\n");
        printf("\t\t\t\t\t        9 - Fechar\n");
        fflush(stdin);
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            p = (Pessoa*)malloc(sizeof(Pessoa));
            system("cls");
            printf("\nDigite um codigo: \n");
            scanf("%d", &p->cod);
            printf("Digite um nome: \n");
            scanf("%s", p->nome);
            printf("Digite uma idade: \n");
            scanf("%d", &p->idade);
            printf("Digite uma peso:(ex: 70,2) \n");
            scanf("%f", &p->peso);
            printf("Digite uma altura:(ex: 1,70) \n");
            scanf("%f", &p->altura);
            raiz = inserir(raiz, p);
            printf("\nPressione qualquer tecla para prosseguir");
            getch();
            break;
        case 2:
         system("cls");
            imprimir(raiz, 1);
            printf("Digite o codigo de quem voce deseja remover: ");
            scanf("%d", &cod);
            raiz = remover(raiz, cod);
            printf("\nPressione qualquer tecla para prosseguir");
            getch();
            break;
        case 3:
            system("cls");
            imprimir(raiz, 1);
            getch();
            printf("\nPressione qualquer tecla para prosseguir");
            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:
            liberar(raiz);
            break;
        }
    }
}