#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <intelfpgaup/KEY.h>

//Estrutura para capitar tempo do evento do mouse
struct timeval {
    long tv_sec;  // segundos
    long tv_usec; // microssegundos
};

//Estrutura que capita tempo, tipo, ação e acontecimento do evento do mouse
struct input_event {
    struct timeval time;
    unsigned short type;
    unsigned short code;
    unsigned int value;
};

//Função para relacionar valor do contador com a linha do tabuleiro (primeiro termo da matriz)
int qualLinha(int cont) {
    int linha;
    
    if (cont <= 3) {
        linha = 0;
    } else if (cont <= 6) {
        linha = 1;
    } else {
        linha = 2;
    }

    return linha;
}

//Função para relacionar valor do contador com a coluna do tabuleiro (segundo termo da matriz)
int qualColuna(int cont) {
    int coluna;
    
    if (cont == 1 || cont == 4 || cont == 7) {
        coluna = 0;
    } else if (cont == 2 || cont == 5 || cont == 8) {
        coluna = 1;
    } else {
        coluna = 2;
    }

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
void imprimirTabuleiro(char (*tabuleiro)[3][3]) {
    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("\t\t\t %c │ %c │ %c \n", (*tabuleiro)[i][0], (*tabuleiro)[i][1], (*tabuleiro)[i][2]);
        if (i < 2) {
            printf("\t\t\t───┼───┼───\n");
        }
    }

    printf("\n");
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
    printf("\t _________________________________________________ \n");
    
    //inicio
    if (tipo == 'm') {
        printf("\t|           Bem-vindo ao Jogo da Velha!           |\n");
        printf("\t| ----------------------------------------------- |\n");
        printf("\t| [Botao 1] Iniciar jogo                          |\n");
        printf("\t| [Botao 4] Sair                                  |\n");
    } 
    //vitória
    else if (tipo == 'v') {
        printf("\t|              \033[0;32mO jogador %c venceu!\033[0m                |\n", vencedor);
        printf("\t| ----------------------------------------------- |\n");
        printf("\t| [Botao 1] Jogar novamente                       |\n");
        printf("\t| [Botao 4] Sair                                  |\n");
    } 
    //empate
    else if (tipo == 'e') {
        printf("\t|                 \033[0;31mO jogo empatou.\033[0m                 |\n");
        printf("\t| ----------------------------------------------- |\n");
        printf("\t| [Botao 1] Jogar novamente                       |\n");
        printf("\t| [Botao 4] Sair                                  |\n");
    }
    
    printf("\t|_________________________________________________|\n\n");
}

#endif  
