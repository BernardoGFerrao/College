#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
struct pessoa
{
    char *nome;
    int idade;
    float peso;
    float altura;
    int cod;
};
typedef struct pessoa Pessoa;

struct no
{
    struct no *esquerda;
    struct no *direita;
    int altura;
    Pessoa pessoa;
};
typedef struct no No;

No *inicializar()
{
    return NULL;
}

Pessoa CriarPessoa(int cod, char *nome, int idade, float peso, float altura)
{
    Pessoa pessoa;
    pessoa.idade = idade;
    pessoa.altura = altura;
    pessoa.peso = peso;
    pessoa.cod = cod;
    pessoa.nome = (char *)malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(pessoa.nome, nome);
    return pessoa;
}

No *inserir(No *raiz, Pessoa p)
{
    No *no = (No *)malloc(sizeof(No));
    no->pessoa = p;
    if (raiz == NULL)
    {
        raiz = no;
        no->direita = NULL;
        no->esquerda = NULL;
        no->altura = 0;
        return no;
    }
    else
    {
        if (p.cod > raiz->pessoa.cod)
        {
            raiz->direita = inserir(raiz->direita, p);
        }

        else if (p.cod < raiz->pessoa.cod)
        {
            raiz->esquerda = inserir(raiz->esquerda, p);
        }
        else
            printf("Insercao nao realizada, codigo repetido");
    }
    // recalcula a altura dos nós entre a raiz e o novo nó
    raiz->altura = maior(alturadono(raiz->esquerda), alturadono(raiz->direita)) + 1;
    // verifica a necessidade de balancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

No *balancear(No *raiz)
{
    int fb = fatordebalanceamento(raiz);

    // rotacao esquerda
    if (fb < -1 && fatordebalanceamento(raiz->direita) <= 0)
        raiz = arvore_rotacao_esquerda(raiz);
    // rotacao a direita
    else if (fb > 1 && fatordebalanceamento(raiz->esquerda) >= 0)
        raiz = arvore_rotacao_direita(raiz);
    // rotacao dupla a esquerda
    else if (fb > 1 && fatordebalanceamento(raiz->esquerda) < 0)
        raiz = arvore_esquerda_direita(raiz);
    else if (fb < -1 && fatordebalanceamento(raiz->direita) > 0)
        raiz = arvore_direita_esquerda(raiz);
    return raiz;
}

void imprimir(No *raiz)
{
    if (raiz != NULL)
    {
        printf("Codigo : %d \n Nome: %s \n Idade: %d anos\n Peso: %.2f kg \n Altura: %.2f m", raiz->pessoa.cod, raiz->pessoa.nome, raiz->pessoa.idade, raiz->pessoa.peso, raiz->pessoa.altura);
        printf("\n");
        imprimir(raiz->direita);
        imprimir(raiz->esquerda);
    }
}

void imprimir_arvore(No *raiz, int nivel)
{
    int i;
    if (raiz)
    {
    imprimir_arvore(raiz->direita, nivel + 1);
    printf("\n\n");

    for(i = 0; i<nivel ; i++)
    printf("\t");
    printf("Codigo : %d Nome: %s  Idade: %d anos Peso: %.2f kg  Altura: %.2f m", raiz->pessoa.cod, raiz->pessoa.nome, raiz->pessoa.idade, raiz->pessoa.peso, raiz->pessoa.altura);
    imprimir_arvore(raiz->esquerda, nivel + 1);
    }
}

void liberar(No *raiz)
{
    if (raiz != NULL)
    {
        liberar(raiz->direita);
        liberar(raiz->esquerda);
        free(raiz);
    }
}

No *arvoremenor(No *raiz)
{
    if (raiz != NULL)
    {
        No *aux = raiz;
        while (aux->esquerda != NULL)
        {
            aux = raiz->esquerda;
        }
        return aux;
    }
    return NULL;
}

No *remover(No *raiz, int cod)
{
    if (raiz == NULL)
    {
        printf("Valor nao encontrado!\n");
        return NULL;
    }
    else
    {
        if (cod > raiz->pessoa.cod) // codigo maior que raiz
        {
            raiz->direita = remover(raiz->direita, cod);
        }
        else if (cod < raiz->pessoa.cod) // codigo menor que raiz
        {
            raiz->esquerda = remover(raiz->esquerda, cod);
        }
        else
        { // encontrou
            if (raiz->direita == NULL && raiz->esquerda == NULL)
            { // Nó não tem filhos
                free(raiz);
                return NULL;
            }
            else
            {
                // 2 filhos
                if (raiz->esquerda != NULL && raiz->direita != NULL)
                {
                    No *aux = raiz->esquerda;
                    Pessoa pessoa_aux;
                    while (aux->direita != NULL)
                    {
                        aux = aux->direita;
                    }
                    pessoa_aux = raiz->pessoa;
                    raiz->pessoa = aux->pessoa;
                    aux->pessoa = pessoa_aux;
                    raiz->esquerda = remover(raiz->esquerda, cod);
                    return raiz;
                }
                else
                {
                    // 1 filho
                    No *aux;
                    if (raiz->esquerda != NULL)
                    {
                        aux = raiz->esquerda;
                    }
                    else
                    {
                        aux = raiz->direita;
                    }
                    free(raiz);
                    return aux;
                }
            }
        }
        // recalcula a altura dos nós entre a raiz e o novo nó
        raiz->altura = maior(alturadono(raiz->esquerda), alturadono(raiz->direita)) + 1;
        // verifica a necessidade de balancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}

No *arvore_rotacao_esquerda(No *raiz)
{ // Resolve desbalanceamento para direita
    No *y, *f;

    y = raiz->direita;
    f = y->esquerda;

    y->esquerda = raiz;
    raiz->direita = f;

     raiz->altura = maior(alturadono(raiz->esquerda), alturadono(raiz->direita)) + 1; //recalcula altura
     y->altura = maior(alturadono(y->esquerda), alturadono(y->direita)) + 1;//recalcula altura
    return y;
}

No *arvore_rotacao_direita(No *raiz)
{ // Resolve desbalanceamento para esquerda
    No *y, *f;

    y = raiz->esquerda;
    f = y->direita;

    y->direita = raiz;
    raiz->esquerda = f;

     raiz->altura = maior(alturadono(raiz->esquerda), alturadono(raiz->direita)) + 1; //recalcula altura
     y->altura = maior(alturadono(y->esquerda), alturadono(y->direita)) + 1;//recalcula altura
    return y;
}

No *arvore_direita_esquerda(No *raiz) // Pende primeiro para a direita e depois esquerda
{
    raiz->direita = arvore_rotacao_direita(raiz->direita);
    return arvore_rotacao_esquerda(raiz);
}

No *arvore_esquerda_direita(No *raiz) // Pende primeiro para a esquerda e depois direita
{
    raiz->esquerda = arvore_rotacao_esquerda(raiz->esquerda);
    return arvore_rotacao_direita(raiz);
}

int maior(int a, int b){
return (a>b)? a: b;
}

int alturadono(No *no){
if(no == NULL){
return -1;
}
else
return no->altura;
}

int fatordebalanceamento(No *no){
if(no){
    return (alturadono(no->esquerda) - alturadono(no->direita));   
}
else
return 0;
}


int main()
{
    setlocale(LC_ALL, "Portuguese");
    char nome[50];
    int idade, cod, r = 1;
    float altura, peso;
    No *raiz = inicializar();
    imprimir(raiz);
    while (r != 9)
    {
        /*Crie um menu com as seguintes opções:

       - incluir

       - buscar e imprimir (todos os campos de um elemento)

       - editar o valor de um elemento (buscar por uma chave e permitir alterar o valor correspondente)

       - excluir

       - imprimir todos elementos (de forma ordenada)

       - imprimir quantidade de elementos

       - informar altura da árvore

       - imprimir com estrutura de arvore (apresentando a forma que as chaves estão armazenadas).
       */
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
        scanf("%d", &r);
        switch (r)
        {

        case 1:
            system("cls");
            printf("\nDigite um codigo: \n");
            scanf("%d", &cod);
            fflush(stdin);
            printf("Digite um nome: \n");
            scanf("%s", nome);
            fflush(stdin);
            printf("Digite uma idade: \n");
            scanf("%d", &idade);
            fflush(stdin);
            printf("Digite uma peso:(ex: 70,2) \n");
            scanf("%f", &peso);
            fflush(stdin);
            printf("Digite uma altura:(ex: 1,70) \n");
            scanf("%f", &altura);
            fflush(stdin);
            raiz = inserir(raiz, CriarPessoa(cod, nome, idade, peso, altura));
            break;
        case 2:
            system("cls");
            imprimir(raiz);
            printf("Digite o codigo de quem voce deseja remover: ");
            scanf("%d", &cod);
            raiz = remover(raiz, cod);
            break;
        case 3:
            system("cls");
            imprimir(raiz);
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