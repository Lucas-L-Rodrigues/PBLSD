#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;

    while (1) {
        //Abre o comando xxd -E -l 144 /dev/input/event12 em modo de leitura
        fp = popen("xxd -E -l 144 /dev/input/event0", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        char buffer[100];

        //enquanto não ler todas as linhas
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%d\n",strlen(buffer));
            memset(buffer, 0, sizeof(buffer));
        }

        pclose(fp);
    }

    return 0;
}



