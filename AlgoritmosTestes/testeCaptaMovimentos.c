#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Usado para captar movimentações do mouse

int main() {
    FILE *fp;
    char buffer[32];

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        fp = popen("xxd -E -l 14 -p /dev/input/event0", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        if (fgets(buffer, sizeof(buffer), fp) != NULL) {
            if (strstr(buffer, "02000100ffff") != NULL)
                printf("CIMA\n\n");

            else if (strstr(buffer, "020001000100") != NULL)
                printf("BAIXO\n\n");

            else if (strstr(buffer, "02000000ffff") != NULL)
                printf("ESQUERDA\n\n");

            else if (strstr(buffer, "020000000100") != NULL)
                printf("DIREITA\n\n");
        }

        pclose(fp);
    }

    return 0;
}
