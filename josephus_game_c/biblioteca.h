#ifndef _BIBLIOTECA_H
#define _BIBLIOTECA_H
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
    char string[31];
} No;
//////////////////////////////////////////////////////Funções////////////////////////////////////////////////////////////////////////
void lista_inicializa(Lista *l);
int  lista_vazia(Lista *l);
int  lista_tamanho(Lista *l);
void lista_inserir_inicio(Lista *l, int dado, char string[31]);
void lista_inserir_final(Lista *l, int dado, char string[31]);
void lista_inserir_posicao(Lista *l, int dado, int pos, char string[31]);
No  *lista_remover_primeiro(Lista *l);
No  *lista_remover_posicao(Lista *l, int pos);
int  lista_remover_maior(Lista *l);
void lista_imprimir(Lista *l);
void lista_imprimir_ordenado(Lista *l);
void imprimir_elemento(No *e);
char retorna_string(No *e);
int  retorna_int(No *e);
void lista_liberar(Lista *l);
void limpa_tela();
#endif





