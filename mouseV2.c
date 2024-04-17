#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mouseDireito "0400 0400 0200 0900"
#define mouseEsquerdo "0400 0400 0100 0900"

int main() {
    FILE *fp;
    char buffer[80];

    while (1) {
        //Abre o comando xxd -E -l 144 /dev/input/event12 em modo de leitura
        fp = popen("xxd -E -l 96 /dev/input/event0", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        //enquanto não ler todas as linhas
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            //caso strstr não retorne null ( tem o padrão )
            if (strstr(buffer, mouseDireito) != NULL) {
                printf("Botão direito clicado!\n");
                memset(buffer, 0, sizeof(buffer));
                break;
            }

            //caso strstr não retorne null ( tem o padrão )
            else if (strstr(buffer, mouseEsquerdo) != NULL) {
                printf("Botão esquerdo clicado!\n");
                memset(buffer, 0, sizeof(buffer));     
	            break;
            }

	        memset(buffer, 0, sizeof(buffer));
        }
        pclose(fp);
    }
    return 0;
}
