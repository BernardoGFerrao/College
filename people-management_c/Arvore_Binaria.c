#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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
        return no;
    }
    else
    {
        if (p.cod > raiz->pessoa.cod)
        {
            raiz->direita = inserir(raiz->direita, p);
        }

        if (p.cod < raiz->pessoa.cod)
        {
            raiz->esquerda = inserir(raiz->esquerda, p);
        }
    }
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

void liberar(No *raiz)
{
    if (raiz != NULL)
    {
        liberar(raiz->direita);
        liberar(raiz->esquerda);
        free(raiz);
    }
}

No *pesquisar(No *raiz, int cod)
{
    if (raiz != NULL)
    {
        if (raiz->pessoa.cod = cod)
        {
            return raiz;
        }
        else
        {
            if (cod > raiz->pessoa.cod)
            {
                return pesquisar(raiz->direita, cod);
            }
            else if (cod < raiz->pessoa.cod)
            {
                return pesquisar(raiz->esquerda, cod);
            }
        }
    }
    return NULL;
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
    if (raiz != NULL)
    {
        if (cod > raiz->pessoa.cod)
        {
            raiz->direita = remover(raiz->direita, cod);
        }
        else if (cod < raiz->pessoa.cod)
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
            else if (raiz->esquerda == NULL && raiz->direita != NULL)
            { // Um filho direita
                No *aux = raiz->direita;
                free(raiz);
                return aux;
            }
            else if (raiz->direita == NULL && raiz->esquerda != NULL)
            { // Um filho esquerda
                No *aux = raiz->esquerda;
                free(raiz);
                return aux;
            }
            else
            {
                No *aux = arvoremenor(raiz->direita); // encontrei o menor número da maior subarvore
                Pessoa pessoaaux = aux->pessoa;
                raiz = remover(raiz, pessoaaux.cod);
                raiz->pessoa = pessoaaux;
            }
        }
        return raiz;
    }
    else
        return NULL;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    char nome[50];
    int idade, cod, r = 1;
    float altura, peso;
    No *raiz = inicializar();
    imprimir(raiz);
    while (r != 5)
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
            scanf("%d",&cod);
            raiz = remover(raiz, cod);
            break;
        case 3:
            system("cls");
            imprimir(raiz);
            break;
        case 4:

            break;
        case 5:
            liberar(raiz);
            break;
        }
    }
}