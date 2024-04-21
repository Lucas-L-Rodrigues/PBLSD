#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char buffer[70];
    int cliqueDir = 0, cliqueEsq = 0;

    memset(buffer, 0, sizeof(buffer));

    while (1) {
        // Abre o comando xxd -E -l 48 /dev/input/event12 em modo de leitura
        fp = popen("xxd -E -l 48 /dev/input/event12", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        //Testar removendo linha 10
        //memset(buffer, 0, sizeof(buffer));

        // Lê e imprime a saída do comando
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            if (strstr(buffer, "0400 0400 0200 0900") != NULL) {
                if(cliqueDir==0){
                    cliqueDir++;
                    printf("Botão direito clicado!\n");
                }

                else
                    cliqueDir=0;
                
                memset(buffer, 0, sizeof(buffer));
                break;
            }

            // Verifica se a linha contém o padrão para o botão esquerdo
            else if (strstr(buffer, "0400 0400 0100 0900") != NULL) {
                if(cliqueEsq==0){
                    cliqueEsq++;
                    printf("Botão esquerdo clicado!\n");
                }

                else
                    cliqueEsq=0;
                
                memset(buffer, 0, sizeof(buffer));
                break;
            }

            memset(buffer, 0, sizeof(buffer));
        }

        pclose(fp);
    }

    return 0;
}