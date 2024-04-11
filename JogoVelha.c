#include "utils.h"

int main() {
    char tabuleiro[3][3];
    char jogador, vencedor;
    int linha, coluna, jogadas, botoes;
    int cont;
    
    //Limpa buffer
    KEY_close();

    //Verifica se botão está sendo lido
    if (!KEY_open ( )){
        printf("Erro na inicialização dos botoes.\n");
        return -1;
    }

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

            int fd;
            struct input_event event;

            //Abre arquivo do evento do mouse
            fd = open("/dev/input/event0", O_RDONLY);
            if (fd == -1) {
                perror("Error opening mouse event file\n");
                return 1;
            }

            do {
                printf("\033[0;32m\t\tJogador %c - Quadrante selecionado: %d\n\n\033[0m",jogador, cont);
                imprimirTabuleiro(&tabuleiro);
                printf("\nPressione botão direito do mouse para selecionar quadrante\n");

                //Capta eventos do mouse até botão esquerdo ser pressionado
                while(1){
                    //Lê evento
                    ssize_t bytes_read = read(fd, &event, sizeof(event));
                    if (bytes_read == -1) {
                        perror("Error reading mouse event");
                        close(fd);
                        return 1;
                    } else if (bytes_read != sizeof(event)) {
                        fprintf(stderr, "Incomplete event read\n");
                        continue;
                    }
                
                    //Verifica se houve um botão do mouse pressionado, e se sim, qual botão foi usado
                    if (event.type == 1 && (event.code == 272 || event.code == 273) && event.value == 1) {
                        //Se for o botão direito
                        if(event.code == 273){
                            if(cont==9)
                                cont=1;
                            else
                                cont++;
                            
                            system("clear");
                            printf("\033[0;32m\t\tJogador %c - Quadrante selecionado: %d\n\n\033[0m",jogador, cont);
                            imprimirTabuleiro(&tabuleiro);
                            printf("\nPressione botão direito do mouse para selecionar quadrante\n");
                        }

                        //Se for o botão esquerdo
                        else if(event.code == 272)
                            break;
                    }
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

            //Fecha o arquivo do evento do mouse
            close(fd);

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

    //Fecha conexão com os botões da placa
    KEY_close ( );

    return 0;
}
