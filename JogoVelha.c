#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <intelfpgaup/KEY.h>

struct timeval {
    long tv_sec;  // segundos
    long tv_usec; // microssegundos
};

struct input_event {
    struct timeval time;
    unsigned short type;
    unsigned short code;
    unsigned int value;
};

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
        printf("\t|              \033[0;32mO jogador %c venceu!\033[0m                |\n", vencedor);
        printf("\t| ----------------------------------------------- |\n");
        printf("\t| [Botao 1] Jogar novamente                       |\n");
        printf("\t| [Botao 4] Sair                                  |\n");
    } 
    else if (tipo == 'e') {
        printf("\t|                 \033[0;31mO jogo empatou.\033[0m                 |\n");
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
    int cont;
    
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
            cont=1;

            do {
                int fd;
                struct input_event event;

                fd = open("/dev/input/event0", O_RDONLY);
                if (fd == -1) {
                    perror("Error opening mouse event file\n");
                    return 1;
                }

                printf("\033[0;32m\t\tJogador %c - Quadrante selecionado: %d\n\n\033[0m",jogador, cont);
                imprimirTabuleiro(&tabuleiro);
                printf("Pressione botão direito do mouse para selecionar quadrante: ");

                while(1){
                    // Read the input event
                    ssize_t bytes_read = read(fd, &event, sizeof(event));
                    if (bytes_read == -1) {
                        perror("Error reading mouse event");
                        close(fd);
                        return 1;
                    } else if (bytes_read != sizeof(event)) {
                        fprintf(stderr, "Incomplete event read\n");
                        continue;
                    }
                
                    // Verifica se houve um botão pressionado, e se sim, qual botão foi usado
                    if (event.type == 1 && (event.code == 272 || event.code == 273) && event.value == 1) {
                        // Print do evento é feito a aprtir dos atributos da struct
                        if(event.code == 273){
                            if(cont==9)
                                cont=1;
                            else
                                cont++;
                            
                            system("clear");
                            printf("\033[0;32m\t\tJogador %c - Quadrante selecionado: %d\n\n\033[0m",jogador, cont);
                            imprimirTabuleiro(&tabuleiro);
                            printf("Pressione botão direito do mouse para selecionar quadrante: ");
                        }

                        else if(event.code == 272)
                            break;
                    }
                }

                // Close the file descriptor
                close(fd);

                linha = qualLinha(cont);
                coluna = qualColuna(cont);
                //Verificar se a posição está vazia
                if (tabuleiro[linha][coluna] == ' ') {
                    tabuleiro[linha][coluna] = jogador;
                    jogadas++;
                    cont=1;
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
