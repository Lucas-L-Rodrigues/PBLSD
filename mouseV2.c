#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;

    // Abre o comando xxd -E -l 144 /dev/input/event12 em modo de leitura
    fp = popen("xxd -E -l 144 /dev/input/event12", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o comando.\n");
        return 1;
    }

    int cont1 = 0, cont2 = 0;

    while (1) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            if (strstr(buffer, "0400 0400 0200 0900") != NULL) {
                if(cont1==0){
                    printf("Botão direito clicado!\n");
                    cont1++;
                }    
                
                else
                    cont1=0;
            }

            else if (strstr(buffer, "0400 0400 0100 0900") != NULL) {
                if(cont2==0){
                    printf("Botão esquerdo clicado!\n");
                    cont2++;
                }    
                
                else
                    cont2=0;
            }
        }
    }

    pclose(fp);

    return 0;
}



