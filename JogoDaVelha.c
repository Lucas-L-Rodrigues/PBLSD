#include "utils.h"

int main() {
    //Matriz do tabuleiro
    char tabuleiro[3][3];
    
    //Jogador da vez e jogador vencedor
    char jogador, vencedor;
    
    //Linha e coluna da matriz
    int linha, coluna;
    
    //Número de jogadas e botões 1 ou 4 da placa
    int jogadas, botoes;
    
    //Quadrante selecionado
    int quadrante;

    //Subida e descida do clique esquerdo do mouse e confirmação da jogada
    int cliqueEsq, confirma;

    //Temporizadores para contabilizar eventos necessários para mudar quadrante
    int tempCima, tempBaixo, tempDireita, tempEsquerda;
    
    //Ponteiro para acesso ao arquivo de leitura do evento do mouse
    FILE *fp;
    
    //Vetor que pega linha por linha de um evento do mouse
    char buffer[70];
    
    //Limpa buffer
    KEY_close();

    //Verifica se botão está sendo lido
    if (!KEY_open ( )){
        printf("Erro na inicialização dos botoes.\n");
        return -1;
    }

    system("clear");

    //Menu inicial
    exibirTela('m', ' ');
    
    //Lê botões da placa
    KEY_read (&botoes);
    while (botoes!=8 && botoes!=1)
        KEY_read (&botoes);

    //Botão 1 pressionado
    if (botoes==8) {
        cliqueEsq = 0;
        tempCima = 0, tempBaixo = 0, tempDireita = 0, tempEsquerda = 0;
	    do {
            system("clear");
            inicializarTabuleiro(&tabuleiro);
            jogadas = 0;
            jogador = 'X';
            quadrante = 1;

            do {
                confirma = 0;
                memset(buffer, 0, sizeof(buffer));
                
                imprimirQuadrante(&jogador,&quadrante,&tabuleiro);

                //Capta eventos do mouse até botão esquerdo ser pressionado
                do {
                    //Abre o comando xxd -E -l 48 /dev/input/event0 em modo de leitura -> 48 pois so precisa ler 3 linhas
                    fp = popen("xxd -E -l 48 /dev/input/event0", "r");
                    if (fp == NULL) {
                        printf("Erro ao abrir o comando.\n");
                        return 1;
                    }

                    //Enquanto não ler todas as linhas do evento ( 3 linhas ao total )
                    while (fgets(buffer, sizeof(buffer), fp) != NULL) {

                        //Caso strstr não retorne null -> Clicou botão esquerdo do mouse
                        if (strstr(buffer, mouseEsquerdo) != NULL) {
                            //pressionei botão esquerdo do mouse
                            if(cliqueEsq==0){
                                confirma = 1;
                                cliqueEsq++;
                            } 

                            //soltei botão esquerdo do mouse
                            else
                                cliqueEsq = 0;
                            
                            //limpa buffer ( apaga linha já lida )
                            memset(buffer, 0, sizeof(buffer));
                            break;
                        }

                        //Caso strstr não retorne null -> Moveu mouse para cima
                        else if (strstr(buffer, mouseMovCima) != NULL) {
                            if (quadrante > 3) {
                                tempCima += 1;
                                if (tempCima == sensibilidade){
                                    quadrante -= 3;
                                    zeraTemp(&tempBaixo,&tempCima,&tempDireita,&tempEsquerda);
                                    system("clear");
                                    imprimirQuadrante(&jogador,&quadrante,&tabuleiro);
                                }
                            }

                            memset(buffer, 0, sizeof(buffer));
                            break;
                        }

                        //Caso strstr não retorne null -> Moveu mouse para baixo
                        else if (strstr(buffer, mouseMovBaixo) != NULL) {
                            if (quadrante < 7) {
                                tempBaixo += 1;
                                if (tempBaixo == sensibilidade){
                                    quadrante += 3;
                                    zeraTemp(&tempBaixo,&tempCima,&tempDireita,&tempEsquerda);
                                    system("clear");
                                    imprimirQuadrante(&jogador,&quadrante,&tabuleiro);
                                }
                            }

                            memset(buffer, 0, sizeof(buffer));
                            break;
                        }

                        //Caso strstr não retorne null -> Moveu mouse para esquerda
                        else if (strstr(buffer, mouseMovEsquerda) != NULL) {
                            if ((quadrante != 1) && (quadrante != 4) && (quadrante != 7)) {
                                tempEsquerda += 1;
                                if (tempEsquerda == sensibilidade){
                                    quadrante -= 1;
                                    zeraTemp(&tempBaixo,&tempCima,&tempDireita,&tempEsquerda);
                                    system("clear");
                                    imprimirQuadrante(&jogador,&quadrante,&tabuleiro);
                                }
                            }

                            memset(buffer, 0, sizeof(buffer));
                            break;
                        }

                        //Caso strstr não retorne null -> Moveu mouse para direita
                        else if (strstr(buffer, mouseMovDireita) != NULL) {
                            if ((quadrante != 3) && (quadrante != 6) && (quadrante != 9)) {
                                tempDireita += 1;
                                if (tempDireita == sensibilidade){
                                    quadrante += 1;
                                    zeraTemp(&tempBaixo,&tempCima,&tempDireita,&tempEsquerda);
                                    system("clear");
                                    imprimirQuadrante(&jogador,&quadrante,&tabuleiro);
                                }
                            }

                            memset(buffer, 0, sizeof(buffer));
                            break;
                        }

                        //Limpa buffer ( apaga linha já lida )
                        memset(buffer, 0, sizeof(buffer));
                    }
                    
                    //Fecha arquivo de captura dos eventos do mouse
                    pclose(fp);
                
                //Enquanto não for clicado botão esquerdo do mouse
                } while (confirma == 0);

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
                    printf(vermelho"\t\tPosição ocupada. Tente novamente."padrao"\n\n");
                }
            //Enquanto não tiver um vencedor ou número de jogadas for menor que 9
            } while (vencedor==' ' && jogadas < 9);

            //Tabuleiro final
            imprimirTabuleiro(&tabuleiro,0);

            //Se alguém venceu, exibe menu do vencedor
            if (vencedor != ' ') 
                exibirTela('v', vencedor);
            
            //Se empatou, exibe menu de empate
            else
                exibirTela('e', ' ');
    
            //Lê botões
            KEY_read (&botoes);
            while (botoes!=8 && botoes!=1)
                KEY_read (&botoes);
        //Enquanto primeiro botão for pressionado
        } while (botoes == 8);
    }
    
    printf("\nSaindo. Até a próxima!\n\n");

    //Fecha conexão com os botões da placa
    KEY_close ( );

    return 0;
}
