#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int contador = 0;
    int temp = 0;
    //int contador_cima=0;
    //int contador_baixo=0;
    //int contador_esquerda=0;
    //int contador_direita=0;

    FILE *fp;
    char buffer[70];

    memset(buffer, 0, sizeof(buffer));

    while (1) {
        // Abre o comando xxd -E -l 48 /dev/input/event12 em modo de leitura
        fp = popen("xxd -E -l 48 /dev/input/event0", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        // Lê e imprime a saída do comando
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            if (strstr(buffer, "0200 0100 ffff") != NULL) {
                printf("CIMA\n\n");
                if ((contador != 0) && (contador != 1) && (contador != 2)) {
                    //contador_cima = contador_cima + 1;
                    //contador_baixo = 0;
                    temp += 1;
                    if (temp == 20){
                        contador = contador -3;
                        temp=0;
                    }
                }
                /*
                if (contador_cima == 3) {
                    contador_cima = 0;
                    contador = contador - 3;
                    printf("o valor do contador eh: %d \n", contador);
                }*/

                printf("o valor do contador eh: %d \n", contador);

                memset(buffer, 0, sizeof(buffer));
                break;
            }

            else if (strstr(buffer, "0200 0100 0100") != NULL) {
                printf("BAIXO\n\n");
                if ((contador != 6) && (contador != 7) && (contador != 8)) {
                    //contador_baixo = contador_baixo +1;
                    //contador_cima = 0;
                    temp += 1;
                    if (temp == 20){
                        contador = contador + 3;
                        temp=0;
                    }
                }
                /*
                if (contador_baixo == 3) {
                    contador_baixo = 0;
                    contador = contador +3;
                    printf("o valor do contador eh: %d \n", contador);
                }*/

                printf("o valor do contador eh: %d \n", contador);


                memset(buffer, 0, sizeof(buffer));
                break;
            }

            else if (strstr(buffer, "0200 0000 ffff") != NULL) {
                printf("ESQUERDA\n\n");
                if ((contador != 0) && (contador != 3) && (contador != 6)) {
                    //contador_esquerda = contador_esquerda +1;
                    //contador_direita = 0;
                    temp += 1;
                    if (temp == 20){
                        contador = contador - 1;
                        temp=0;
                    }
                }
                /*
                if (contador_esquerda == 3) {
                    contador_esquerda = 0;
                    contador = contador -1;
                    printf("o valor do contador eh: %d \n", contador);
                }*/

                printf("o valor do contador eh: %d \n", contador);

                memset(buffer, 0, sizeof(buffer));
                break;
            }

            else if (strstr(buffer, "0200 0000 0100") != NULL) {
                printf("DIREITA\n\n");
                if ((contador != 2) && (contador != 5) && (contador != 8)) {
                    //contador_direita = contador_direita +1;
                    //contador_esquerda = 0;
                    temp += 1;
                    if (temp == 20){
                        contador = contador + 1;
                        temp=0;
                    }
                }
                /*
                if (contador_direita == 3) {
                    contador_direita = 0;
                    contador = contador +1;
                    printf("o valor do contador eh: %d \n", contador);
                }*/

                printf("o valor do contador eh: %d \n", contador);

                memset(buffer, 0, sizeof(buffer));
                break;
            }

            memset(buffer, 0, sizeof(buffer));
        }

        pclose(fp);
    }

    return 0;
}