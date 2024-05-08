#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Usado para testar identificar padrões de eventos e tamanho do vetor após leitura

int main() {
    FILE *fp;
    char buffer[50];

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        fp = popen("xxd -E -l 14 -p /dev/input/event0", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        if(fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s",buffer);
            printf("\n%d\n",strlen(buffer));
        }
        
        pclose(fp);
    }

    return 0;
}
