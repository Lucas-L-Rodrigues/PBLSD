#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char buffer[70];

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        // Abre o comando xxd -E -l 48 /dev/input/event12 em modo de leitura
        fp = popen("xxd -E -l 48 /dev/input/event0", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        // Lê e imprime a saída do comando
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s\n",buffer);
            memset(buffer, 0, sizeof(buffer));
        }
        
        printf("\n");
        pclose(fp);
    }

    /*while (1) {
        memset(buffer, 0, sizeof(buffer));
        // Abre o comando xxd -E -l 48 /dev/input/event12 em modo de leitura
        fp = popen("xxd -E -l 48 -p /dev/input/event0", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        // Lê e imprime a saída do comando
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s\n",buffer);
            memset(buffer, 0, sizeof(buffer));
        }
        
        printf("\n");
        pclose(fp);
    }*/

    return 0;
}
