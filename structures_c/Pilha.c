#include<stdio.h>
#include<stdlib.h>


typedef struct no No;

struct no{
int valor;
struct no *prox;
};

typedef struct pilha PILHA;
struct pilha{
struct pilha *topo;
int tam; 
};
void inicializapilha(PILHA *p){
p->topo = NULL;
p->tam = 0;
}

No *empilha(int dado, PILHA *p){
No *no = (No *)malloc(sizeof(No));
if(no == NULL){
printf("Erro de alocação");
}
else{
no->valor = dado;
no->prox = p->topo;
p->topo = no;
p->tam= p->tam +1;
}
}

int desempilha(PILHA *p){
No * no = p->topo;
int dado;
if(no == NULL){
printf("pilha vazia");
}
else{
p->topo = no->prox;
no->prox = NULL;
dado = no->valor;
free(no);
return dado;
}
}

void imprime(PILHA *p){
No *no = p->topo;
if(no == NULL){
printf("pilha vazia\n");
}
else{
while( no != NULL){
printf("%d   ", no->valor);
no = no->prox;
}    
}
}

int tamanho(PILHA *p){     
No *aux = p->topo;
int tam=1;
if(aux == NULL){

tam=0;
}
else{
while(aux->prox != NULL){
tam++;
aux = aux->prox;
}    
}
return tam;
}
/*
PILHA concatena(PILHA *p1, PILHA *p2){
int i;
No *aux;
No *aux2 = p2->topo;
while(i=0;i<p2->tam;i++){
aux = aux2;
aux->prox = p1->topo;
p1->topo = aux;
aux2=aux2->prox;
}
}
*/
int main(){
int tam;
PILHA *p1 = (PILHA*)malloc(sizeof(PILHA));
PILHA *p2 = (PILHA*)malloc(sizeof(PILHA));
if(p1 == NULL){
printf("Erro de alocação da pilha");
exit(0);
}
if(p2 == NULL){
printf("Erro de alocação da pilha");
exit(0);
}
inicializapilha(p1);
inicializapilha(p2);
empilha(10,p1);
empilha(20,p1);
empilha(30,p1);
empilha(40,p2);
empilha(50,p2);
empilha(60,p2);
printf("\ntamanho p1: %d\n",p1->tam);
imprime(p1);
printf("\ntamanho p2: %d\n",p2->tam);
imprime(p2);
//concatena(p1,p2);

/*
tam = tamanho(p1);
printf("\nTamanho  %d\n", tam);
imprime(p1);
printf("\n");
desempilha(p1);
tam = tamanho(p1);
printf("\nTamanho  %d\n", tam);
imprime(p1);
printf("\n");
desempilha(p1);
tam = tamanho(p1);
printf("\nTamanho  %d\n", tam);
imprime(p1);
printf("\n");
desempilha(p1);
tam = tamanho(p1);
printf("\nTamanho  %d\n", tam);
imprime(p1);
printf("\n ");
desempilha(p1);
tam = tamanho(p1);
printf("\nTamanho  %d\n", tam);
imprime(p1);
printf("\n ");
desempilha(p1);
tam = tamanho(p1);
printf("\nTamanho  %d\n", tam);
imprime(p1);
printf("\n ");
desempilha(p1);
tam = tamanho(p1);
printf("\nTamanho  %d\n", tam);
imprime(p1);
printf("\n ");
desempilha(p1);
tam = tamanho(p1);
printf("\nTamanho  %d\n", tam);
imprime(p1);
printf("\n ");*/
}




