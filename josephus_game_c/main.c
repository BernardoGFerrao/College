#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "biblioteca.h"
///////////////////////////////////////////////////////////////////////////////////////////////////main////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Lista *l1 = (Lista *)malloc(sizeof(Lista));
    lista_inicializa(l1);
    int i = 1, num, eliminar, quantidade, enviar, pos = 0;
    No *aux = l1->primeiro, *removido;
    printf("  \n\n\n\n\n\n\n                                                                                    			   \n");
    printf("     ###                               #                           ###                  #       ## 				   \n");
    printf("       #                               #                           #  #                 #        # 				   \n");
    printf("       #    ##    ####    ##    ###    # #    #  #   ####          #  #   # #     ##    ###      #     ##    ## #  \n");
    printf("       #   #  #   ##     # ##   #  #   ## #   #  #   ##            ###    ## #   #  #   #  #     #    # ##   # # # \n");
    printf("    #  #   #  #     ##   ##     #  #   #  #   #  #     ##          #      #      #  #   #  #     #    ##     # # # \n");
    printf("     ###    ##    ####    ###   ###    #  #    ###   ####          #      #       ##    ###     ###    ###   #   # \n");
    printf("                                # 																				   \n");
    printf("                                # 																				   \n");
	printf("\n\n\n\t\t\t\t\t  Pressione para comecar o jogo...\n\n");
    getch();
    limpa_tela();
    printf("\n\n\n\n\n\n\n\t\t\t\t  Digite a quantidade de soldados do jogo: ");
    scanf("%d", &quantidade);
    limpa_tela();
    printf("\n\n\n\n\n\n\n \t   Um grupo de %d soldados estao cercados pelo inimigo, e ha apenas um cavalo, quem sera o sobrevivente?", quantidade);
    printf("\neles se reunem em volta da fogueira e decidem jogar um jogo, um numero sera sorteado, e o primeiro soldado ira passar contando por cada um dos soldados, incluindo a si mesmo, em quem ficar o ultimo numero, sera o eliminado, depois a contagem continua da posicao do ultimo eliminado!\n");
    // insere os soldados
    while (i != quantidade+1)
    {
        num = i;
        lista_inserir_final(l1, num, "Soldado");
        i++;
    }
    lista_imprimir(l1);
    printf("\n\n\n\t\t\t\t\t\t  Que os jogos comecem...\n\n");
    getch();
    limpa_tela();
    while (lista_tamanho(l1) != 1)
    {
        limpa_tela();
        eliminar = rand() % (lista_tamanho(l1) * 2);
        printf("\n\t\t\t\t Quem contava estava na posicao %d, numero sorteado %d\n", pos, eliminar);
        lista_imprimir(l1);
        eliminar = eliminar % lista_tamanho(l1);
        printf("\n resto %d", eliminar);
        pos = eliminar + pos;
        // TESTE ANTES ELIMINAÇÃO
        if (pos == lista_tamanho(l1))
        {
            pos = 0;
        }
        else if (pos >= lista_tamanho(l1))
        {
            pos = pos % lista_tamanho(l1);
        }
        removido = lista_remover_posicao(l1, pos);
        if (removido)
        {
            printf("\n\t\t\t\t\t    !!! O Soldado %d foi eliminado !!!\n", removido->num);
            free(removido);
        }
        // TESTE PÓS ELIMINAÇÃO
        if (pos == lista_tamanho(l1))
        {
            pos = 0;
        }
        else if (pos >= lista_tamanho(l1))
        {
            pos = pos % lista_tamanho(l1);
        }
        lista_imprimir(l1);
        if(lista_tamanho(l1) == 1){
        printf("\n\n\t\t\t\t\t Parece que temos um vencedor...");
		}
		else{
		printf("\n\n\t\t\t\t\t     Pressione para proximo round...");	
		}
        getch();
    }
    limpa_tela();
    printf("\n\n\n\t\t\t\t\t\tO soldado sobrevivente foi: \n");
    lista_imprimir(l1);
    lista_liberar(l1);
}
