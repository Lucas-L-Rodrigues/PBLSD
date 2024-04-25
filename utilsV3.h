#ifndef UTILSV3_H
#define UTILSV3_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <intelfpgaup/KEY.h>

//Padrões dos eventos do clique dos botões direito e esquerdo do mouse
#define mouseDireito "0400 0200 0900"
#define mouseEsquerdo "0400 0100 0900"

#define padrao "\033[0m"

#define vermelho "\033[1;31m"
#define verde "\033[1;32m"
#define azul "\033[1;34m"
#define azulClaro "\033[1;36m" 

//Função para relacionar valor do contador com a linha do tabuleiro (primeiro termo da matriz)
int qualLinha(int cont) {
    int linha;
    
    if (cont <= 3)
        linha = 0;

    else if (cont <= 6)
        linha = 1;
    
    else 
        linha = 2;

    return linha;
}

//Função para relacionar valor do contador com a coluna do tabuleiro (segundo termo da matriz)
int qualColuna(int cont) {
    int coluna;
    
    if (cont == 1 || cont == 4 || cont == 7)
        coluna = 0;

    else if (cont == 2 || cont == 5 || cont == 8)
        coluna = 1;
    
    else
        coluna = 2;

    return coluna;
}

//Função para inicializar o tabuleiro com espaços em branco
void inicializarTabuleiro(char (*tabuleiro)[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            (*tabuleiro)[i][j] = ' ';
        }
    }
}

//Função para imprimir o tabuleiro
void imprimirTabuleiro(char (*tabuleiro)[3][3], int matrizEspelho) {
    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("\t\t %c │ %c │ %c", (*tabuleiro)[i][0], (*tabuleiro)[i][1], (*tabuleiro)[i][2]);
    
        if (matrizEspelho)
            printf("\t\t %d │ %d │ %d", (i*3)+1, (i*3)+2, (i*3)+3);

        printf("\n");

        if (i < 2) {
            printf("\t\t───┼───┼───");
            
            if (matrizEspelho)
                printf("\t\t───┼───┼───");

            printf("\n");
        }
    }

    printf("\n");
}

// Função para imprimir o quadrante selecionado
void imprimirQuadrante(char *jogador, int *quadrante, char (*tabuleiro)[3][3]) {
    printf(azulClaro"\t\tJogador %c - Quadrante selecionado: %d"padrao"\n\n",*jogador, *quadrante);
    imprimirTabuleiro(tabuleiro,1);
    printf(azulClaro"\nPressione botão direito do mouse para selecionar quadrante"padrao"\n");
}

//Função para verificar se há um vencedor e retornar simbolo ( X ou O )
char verificarVencedor(char (*tabuleiro)[3][3]) {
    //Verificar linhas e colunas
    for (int i = 0; i < 3; i++) {
        if ((*tabuleiro)[i][0] == (*tabuleiro)[i][1] && (*tabuleiro)[i][0] == (*tabuleiro)[i][2])
            return (*tabuleiro)[i][0];
        if ((*tabuleiro)[0][i] == (*tabuleiro)[1][i] && (*tabuleiro)[0][i] == (*tabuleiro)[2][i])
            return (*tabuleiro)[0][i];
    }

    //Verificar diagonais
    if ((*tabuleiro)[0][0] == (*tabuleiro)[1][1] && (*tabuleiro)[0][0] == (*tabuleiro)[2][2])
        return (*tabuleiro)[0][0];
    
    if ((*tabuleiro)[0][2] == (*tabuleiro)[1][1] && (*tabuleiro)[0][2] == (*tabuleiro)[2][0])
        return (*tabuleiro)[0][2];

    //Se não houver vencedor, retorna vazio
    return ' ';
}

//Função para exibição de menus
void exibirTela(char tipo, char vencedor) {
   
    if(tipo == 'm')
	    printf("\t");
   
    printf(" _________________________________________________ \n");
    
    //inicio
    if (tipo == 'm') {
        printf("\t|           "azulClaro"Bem-vindo ao Jogo da Velha!           "padrao"|\n");
        printf("\t| ----------------------------------------------- |\n");
        printf("\t| "azulClaro"[Botao 1] Iniciar jogo                          "padrao"|\n");
        printf("\t| "azulClaro"[Botao 4] Sair                                  "padrao"|\n");
        printf("\t");
     } 

    //vitória
    else if (tipo == 'v') {
        printf("|              "verde"O jogador %c venceu!"padrao"                |\n", vencedor);
        printf("| ----------------------------------------------- |\n");
        printf("| "azulClaro"[Botao 1] Jogar novamente                       "padrao"|\n");
        printf("| "azulClaro"[Botao 4] Sair                                  "padrao"|\n");
    } 

    //empate
    else if (tipo == 'e') {
        printf("|                 "vermelho"O jogo empatou."padrao"                 |\n");
        printf("| ----------------------------------------------- |\n");
        printf("| "azulClaro"[Botao 1] Jogar novamente                       "padrao"|\n");
        printf("| "azulClaro"[Botao 4] Sair                                  "padrao"|\n");
    }
    
    printf("|_________________________________________________|"padrao"\n\n");
}

#endif
