#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
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
                memset(buffer, 0, sizeof(buffer));
                break;
            }

            else if (strstr(buffer, "0200 0100 0100") != NULL) {
                printf("BAIXO\n\n");
                memset(buffer, 0, sizeof(buffer));
                break;
            }

            else if (strstr(buffer, "0200 0000 ffff") != NULL) {
                printf("ESQUERDA\n\n");
                memset(buffer, 0, sizeof(buffer));
                break;
            }

            else if (strstr(buffer, "0200 0000 0100") != NULL) {
                printf("DIREITA\n\n");
                memset(buffer, 0, sizeof(buffer));
                break;
            }

            memset(buffer, 0, sizeof(buffer));
        }

        pclose(fp);
    }

    return 0;
}
