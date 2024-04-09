#include <stdio.h>
#include <stdlib.h>
#include <intelfpgaup/KEY.h>

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

    //Se não houver vencedor, retorn vazio
    return ' ';
}

//Função para exibição de menus
void exibirTela(char tipo, char vencedor) {
    printf("\t _________________________________________________ \n");
    
    if (tipo == 'm') {
        printf("\t|           Bem-vindo ao Jogo da Velha!           |\n");
        printf("\t| ----------------------------------------------- |\n");
        printf("\t| [Botao 1] Iniciar jogo                          |\n");
        printf("\t| [Botao 4] Sair                                  |\n");
    } 
    else if (tipo == 'v') {
        printf("\t|              O jogador %c venceu!                |\n", vencedor);
        printf("\t| ----------------------------------------------- |\n");
        printf("\t| [Botao 1] Jogar novamente                       |\n");
        printf("\t| [Botao 4] Sair                                  |\n");
    } 
    else if (tipo == 'e') {
        printf("\t|                 O jogo empatou.                 |\n");
        printf("\t| ----------------------------------------------- |\n");
        printf("\t| [Botao 1] Jogar novamente                       |\n");
        printf("\t| [Botao 4] Sair                                  |\n");
    }
    
    printf("\t|_________________________________________________|\n\n>>> ");
}

int main() {
    char tabuleiro[3][3];
    char jogador, vencedor;
    int linha, coluna, jogadas, botoes;
    
    //Limpa buffer
    KEY_close();

    //Verifica se botão está sendo lido
    if (!KEY_open ( )){
        printf("Erro na inicialização dos botoes.\n");
        return -1;
    }

    exibirTela('m', ' ');
    
    //Lê botões
    KEY_read (&botoes);
    while (botoes!=8 && botoes!=1)
        KEY_read (&botoes);

    //Botão 1 pressionado
    if (botoes==8) {
        do {
            system("clear");
            inicializarTabuleiro(&tabuleiro);
            jogadas = 0;
            jogador = 'X';

            do {
                imprimirTabuleiro(&tabuleiro);

                printf("Jogador %c, informe a linha (1-3) e coluna (1-3) separados por espaco: ", jogador);
                scanf("%d %d", &linha, &coluna);
                linha--; // Ajustar para o índice 0
                coluna--; // Ajustar para o índice 0

                //Verificar se a posição está vazia
                if (tabuleiro[linha][coluna] == ' ') {
                    tabuleiro[linha][coluna] = jogador;
                    jogadas++;
                    vencedor = verificarVencedor(&tabuleiro);

                    //Trocar de jogador
                    if(vencedor==' ')
                        jogador = (jogador == 'X') ? 'O' : 'X';
                    
                    system("clear");
                }
                
                else{
                    system("clear");
                    printf("\033[0;31m\t\tPosição ocupada. Tente novamente.\n\n\033[0m");
                } 

            } while (vencedor==' ' && jogadas < 9);

            //Tabuleiro final
            imprimirTabuleiro(&tabuleiro);;

            if (vencedor != ' ') 
                exibirTela('v', vencedor);
            
            else
                exibirTela('e', ' ');
    
            //Lê botões
            KEY_read (&botoes);
            while (botoes!=8 && botoes!=1)
                KEY_read (&botoes);

        } while (botoes==8);
    }
    
    printf("\nSaindo. Até a próxima!\n");

    //Fecha conexão
    KEY_close ( );

    return 0;
}
