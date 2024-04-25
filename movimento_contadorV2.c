#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sensibilidade 20

void zeraTemp(int *tempCima, int *tempBaixo, int *tempEsquerda, int *tempDireita){
    *tempCima = 0;
    *tempBaixo = 0;
    *tempEsquerda = 0;
    *tempDireita = 0;
}

int main() {

    int contador = 1;
    int tempCima = 0,tempBaixo = 0,tempDireita = 0,tempEsquerda = 0;
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
                
                if (contador > 3) {
                    tempCima += 1;
                    if (tempCima == sensibilidade){
                        contador -= 3;
                        zeraTemp(&tempBaixo,&tempCima,&tempDireita,&tempEsquerda);
                    }
                }

                printf("o valor do contador eh: %d \n", contador);

                memset(buffer, 0, sizeof(buffer));
                break;
            }

            else if (strstr(buffer, "0200 0100 0100") != NULL) {
                printf("BAIXO\n\n");

                if (contador < 7) {
                    tempBaixo += 1;
                    if (tempBaixo == sensibilidade){
                        contador += 3;
                        zeraTemp(&tempBaixo,&tempCima,&tempDireita,&tempEsquerda);
                    }
                }

                printf("o valor do contador eh: %d \n", contador);

                memset(buffer, 0, sizeof(buffer));
                break;
            }

            else if (strstr(buffer, "0200 0000 ffff") != NULL) {
                printf("ESQUERDA\n\n");

                if ((contador != 1) && (contador != 4) && (contador != 7)) {
                    tempEsquerda += 1;
                    if (tempEsquerda == sensibilidade){
                        contador -= 1;
                        zeraTemp(&tempBaixo,&tempCima,&tempDireita,&tempEsquerda);
                    }
                }

                printf("o valor do contador eh: %d \n", contador);

                memset(buffer, 0, sizeof(buffer));
                break;
            }

            else if (strstr(buffer, "0200 0000 0100") != NULL) {
                printf("DIREITA\n\n");
                if ((contador != 3) && (contador != 6) && (contador != 9)) {
                    tempDireita += 1;
                    if (tempDireita == sensibilidade){
                        contador += 1;
                        zeraTemp(&tempBaixo,&tempCima,&tempDireita,&tempEsquerda);
                    }
                }

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