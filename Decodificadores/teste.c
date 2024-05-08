#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char buffer[300];

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        // Abre o comando xxd -E -l 48 /dev/input/event12 em modo de leitura
        fp = popen("xxd -E -l 16 -p /dev/input/event0", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        // Lê e imprime a saída do comando
        if(fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s",buffer);
            printf("\n%d\n",strlen(buffer));
            memset(buffer, 0, sizeof(buffer));
        }
        
        pclose(fp);
    }

    return 0;
}
