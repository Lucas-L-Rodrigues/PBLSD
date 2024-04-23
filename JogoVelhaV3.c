#include "utilsV3.h"

int main() {
    //matriz do tabuleiro
    char tabuleiro[3][3];
    
    //jogador da vez e jogador vencedor
    char jogador, vencedor;
    
    //linha e coluna da matriz
    int linha, coluna;
    
    //numero de jogadas e botoes 1 ou 4 da placa
    int jogadas, botoes;
    
    //quadrante selecionado
    int quadrante;
    
    //ponteiro para acesso ao arquivo de leitura do evento do mouse
    FILE *fp;
    
    //vetor que pega linha por linha de um evento do mouse
    char buffer[70];
    
    //Subida e descida do clique direito e esquerdo do mouse e confirmação da jogada
    int cliqueDir, cliqueEsq, confirma;
    
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
            quadrante = 1;
            cliqueDir = 0;
            cliqueEsq = 0;

            do {
                printf("\033[0;32m\t\tJogador %c - Quadrante selecionado: %d\n\n\033[0m",jogador, quadrante);
                imprimirTabuleiro(&tabuleiro,1);
                printf("\nPressione botão direito do mouse para selecionar quadrante\n");

                confirma = 0;
                memset(buffer, 0, sizeof(buffer));

                //Capta eventos do mouse até botão esquerdo ser pressionado
                do {
                    //Abre o comando xxd -E -l 48 /dev/input/event0 em modo de leitura
                    //48 pois so precisa ler 3 linhas
                    fp = popen("xxd -E -l 48 /dev/input/event0", "r");
                    if (fp == NULL) {
                        printf("Erro ao abrir o comando.\n");
                        return 1;
                    }

                    //enquanto não ler todas as linhas do evento ( 3 linhas ao total )
                    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
                        //caso strstr não retorne null ( tem o padrão )
                        if (strstr(buffer, mouseDireito) != NULL) {
                            //pressionei botão direito do mouse
                            if(cliqueDir==0){
                                cliqueDir++;

                                if(quadrante==9)
                                    quadrante = 1;
                                else
                                    quadrante++;
                                
                                system("clear");
                                printf("\033[0;32m\t\tJogador %c - Quadrante selecionado: %d\n\n\033[0m",jogador, quadrante);
                                imprimirTabuleiro(&tabuleiro,1);
                                printf("\nPressione botão direito do mouse para selecionar quadrante\n");
                            }

                            //soltei botão direito do mouse
                            else
                                cliqueDir = 0;
                            
                            //limpa buffer ( apaga linha já lida )
                            memset(buffer, 0, sizeof(buffer));
                            break;
                        }

                        //caso strstr não retorne null ( tem o padrão )
                        else if (strstr(buffer, mouseEsquerdo) != NULL) {
                            //pressionei botão esquerdo do mouse
                            if(cliqueEsq==0)
                                cliqueEsq++;   

                            //soltei botão esquerdo do mouse
                            else{
                                confirma = 1;
                                cliqueEsq = 0;
                            }
                            
                            //limpa buffer ( apaga linha já lida )
                            memset(buffer, 0, sizeof(buffer));
                            break;
                        }

                        //limpa buffer ( apaga linha já lida )
                        memset(buffer, 0, sizeof(buffer));
                    }
                    
                    //fecha arquivo de captura dos eventos do mouse
                    pclose(fp);

                } while (confirma==0);

                //Relaciona o contador ( quadrante selecionado ) com linha e coluna do tabuleiro
                linha = qualLinha(quadrante);
                coluna = qualColuna(quadrante);
                
                //Verifica se a posição está vazia
                if (tabuleiro[linha][coluna] == ' ') {
                    tabuleiro[linha][coluna] = jogador;
                    jogadas++;
                    quadrante = 1;
                    //Verifica se já tem um vencedor
                    vencedor = verificarVencedor(&tabuleiro);

                    //Troca de jogador se não houver vencedor
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
            imprimirTabuleiro(&tabuleiro,0);

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