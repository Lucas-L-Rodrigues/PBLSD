/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    FILE *fp;

    // Abre o comando xxd -E -l 144 /dev/input/event6 em modo de leitura
    fp = popen("xxd -E -l 144 /dev/input/event12", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o comando.\n");
        return 1;
    }

    int a = 0;

    // Lê e imprime a saída do comando
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        a++;
        printf("\n%d\n",a);
        if (strstr(buffer, "0400 0400 0200 0900") != NULL) {
            printf("Botão direito clicado!\n");
        }
        // Verifica se a linha contém o padrão para o botão esquerdo
        else if (strstr(buffer, "0400 0400 0100 0900") != NULL) {
            printf("Botão esquerdo clicado!\n");
        }
    }

    pclose(fp);
    return 0;
}*/



/*#include <stdio.h>

int main() {
    FILE *file;
    unsigned char buffer[16]; // Tamanho típico de uma linha no formato hexadecimal

    // Abre o arquivo com o xxd usando a opção -E
    file = popen("xxd -E -l 144 /dev/input/event12", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lê e imprime continuamente as linhas do arquivo
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    // Fecha o arquivo
    pclose(file);

    return 0;
}*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;

    while (1) {
        // Abre o comando xxd -E -l 144 /dev/input/event12 em modo de leitura
        fp = popen("xxd -E -l 144 /dev/input/event12", "r");
        if (fp == NULL) {
            printf("Erro ao abrir o comando.\n");
            return 1;
        }

        // Lê e imprime a saída do comando
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            if (strstr(buffer, "0400 0400 0200 0900") != NULL) {
                printf("Botão direito clicado!\n");
            }
            // Verifica se a linha contém o padrão para o botão esquerdo
            else if (strstr(buffer, "0400 0400 0100 0900") != NULL) {
                printf("Botão esquerdo clicado!\n");
            }
        }

        pclose(fp);
    }

    return 0;
}



