#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Usado para testar captar cliques nos botões do mouse

int main() {
    FILE *fp;
    char buffer[32];
    int cliqueDir = 0, cliqueEsq = 0;

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        fp = popen("xxd -E -l 14 -p /dev/input/event0", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        if(fgets(buffer, sizeof(buffer), fp) != NULL) {
            if (strstr(buffer, "040004000200") != NULL) {
                if(cliqueDir==0){
                    cliqueDir++;
                    printf("Botão direito clicado!\n");
                }

                else
                    cliqueDir=0;
            }

            else if (strstr(buffer, "040004000100") != NULL) {
                if(cliqueEsq==0){
                    cliqueEsq++;
                    printf("Botão esquerdo clicado!\n");
                }

                else
                    cliqueEsq=0;
            }
        }

        pclose(fp);
    }

    return 0;
}
