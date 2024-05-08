#include "utilsClquesMouse.h"

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
    char buffer[32];
    
    //Subida e descida do clique direito e esquerdo do mouse e confirmação da jogada
    int cliqueDir, cliqueEsq;

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
        cliqueDir = 0;
        cliqueEsq = 0;
	 do {
            system("clear");
            inicializarTabuleiro(&tabuleiro);
            jogadas = 0;
            jogador = 'X';
            quadrante = 1;
            do {
                imprimirQuadrante(&jogador,&quadrante,&tabuleiro);

                //Capta eventos do mouse até botão esquerdo ser pressionado
                do {
                    memset(buffer, 0, sizeof(buffer));

                    fp = popen("xxd -E -l 14 -p /dev/input/event0", "r");
                    if (fp == NULL) {
                        printf("Erro ao abrir o comando.\n");
                        return 1;
                    }

                    //enquanto não ler todas as linhas do evento ( 3 linhas ao total )
                    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
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
                                imprimirQuadrante(&jogador,&quadrante,&tabuleiro);
                            }

                            //soltei botão direito do mouse
                            else
                                cliqueDir = 0;
                        }

                        //caso strstr não retorne null ( tem o padrão )
                        else if (strstr(buffer, mouseEsquerdo) != NULL) {
                            //pressionei botão esquerdo do mouse
                            if(cliqueEsq==0){
                                //Contabiliza pressionando do mouse, fecha arquivo e sai do loop (leitura de eventos)
                                cliqueEsq++;
                                pclose(fp);
                                break;
                            } 

                            //soltei botão esquerdo do mouse
                            else
                                cliqueEsq = 0;
                        }
                    } 

                    //fecha arquivo de captura dos eventos do mouse
                    pclose(fp);

                } while (1);

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
                    printf(vermelho"\t\tPosição ocupada. Selecione outro quadrante."padrao"\n\n");
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
