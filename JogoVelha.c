#include "utils.h"

int main() {
    char tabuleiro[3][3];
    char jogador, vencedor;
    int linha, coluna, jogadas, botoes;
    int cont;
    FILE *fp;
    char buffer[80];
    int encerra;
    int cliqueDir,cliqueEsq;
    
    //Limpa buffer
    KEY_close();

    //Verifica se botão está sendo lido
    if (!KEY_open ( )){
        printf("Erro na inicialização dos botoes.\n");
        return -1;
    }

    system("clear");

    exibirTela('m', ' ');
    
    //Lê botões da placa
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
            cont=1;

            do {
                printf("\033[0;32m\t\tJogador %c - Quadrante selecionado: %d\n\n\033[0m",jogador, cont);
                imprimirTabuleiro(&tabuleiro);
                printf("\nPressione botão direito do mouse para selecionar quadrante\n");

                encerra = 0;
                cliqueDir = 0;
                cliqueEsq = 0;
                memset(buffer, 0, sizeof(buffer));

                //Capta eventos do mouse até botão esquerdo ser pressionado
                while (1) {
                    //Abre o comando xxd -E -l 144 /dev/input/event12 em modo de leitura
                    fp = popen("xxd -E -l 96 /dev/input/event0", "r");
                    if (fp == NULL) {
                        printf("Erro ao abrir o comando.\n");
                        return 1;
                    }

                    //enquanto não ler todas as linhas
                    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
                        //caso strstr não retorne null ( tem o padrão )
                        if (strstr(buffer, mouseDireito) != NULL) {
                            if(cliqueDir==0){
                                cliqueDir++;

                                if(cont==9)
                                    cont=1;
                                else
                                    cont++;
                                
                                system("clear");
                                printf("\033[0;32m\t\tJogador %c - Quadrante selecionado: %d\n\n\033[0m",jogador, cont);
                                imprimirTabuleiro(&tabuleiro);
                                printf("\nPressione botão direito do mouse para selecionar quadrante\n");
                                memset(buffer, 0, sizeof(buffer));
                                break;
                            }

                            else
                                cliqueDir=0;
                        }

                        //caso strstr não retorne null ( tem o padrão )
                        else if (strstr(buffer, mouseEsquerdo) != NULL) {
                            if(cliqueEsq==0){
                                cliqueEsq++;
                                encerra = 1;
                                memset(buffer, 0, sizeof(buffer));     
                                break;
                            }

                            else
                                cliqueEsq=0;
                        }

                        memset(buffer, 0, sizeof(buffer));
                    }
                    pclose(fp);
                    if(encerra==1)
                        break;
                }

                //Relaciona o contador com linha e coluna do tabuleiro
                linha = qualLinha(cont);
                coluna = qualColuna(cont);
                
                //Verifica se a posição está vazia
                if (tabuleiro[linha][coluna] == ' ') {
                    tabuleiro[linha][coluna] = jogador;
                    jogadas++;
                    cont=1;
                    //Verifica se já tem um vencedor
                    vencedor = verificarVencedor(&tabuleiro);

                    //Troca de jogador
                    if(vencedor==' ')
                        jogador = (jogador == 'X') ? 'O' : 'X';
                    
                    system("clear");
                }
                
                //Posição já está marcada
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
    
    printf("\nSaindo. Até a próxima!\n\n");

    //Fecha conexão com os botões da placa
    KEY_close ( );

    return 0;
}
