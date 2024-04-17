#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mouseDireito "0400 0400 0200 0900"
#define mouseEsquerdo "0400 0400 0100 0900"

int main() {
    FILE *fp;

    int cont1 = 0, cont2 = 0;

    while (1) {
        //Abre o comando xxd -E -l 144 /dev/input/event12 em modo de leitura
        fp = popen("xxd -E -l 144 /dev/input/event0", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        char buffer[256];
        //enquanto não ler todas as linhas

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            //caso strstr não retorne null ( tem o padrão )
            if (strstr(buffer, mouseDireito) != NULL) {
                if(cont1==0){
                    printf("Botão direito clicado!\n");
                    cont1++;
                }    
                
                else
                    cont1=0;

                break;
            }

            //caso strstr não retorne null ( tem o padrão )
            else if (strstr(buffer, mouseEsquerdo) != NULL) {
                if(cont2==0){
                    printf("Botão esquerdo clicado!\n");
                    cont2++;
                }    
                
                else
                    cont2=0;

                break;
            }
        }

        pclose(fp);
    }

    return 0;
}



