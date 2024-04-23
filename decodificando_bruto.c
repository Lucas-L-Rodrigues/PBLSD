#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t little_endian_uint16(unsigned char *bytes) {
    return (uint16_t)bytes[0] | ((uint16_t)bytes[1] << 8);
}

int32_t little_endian_int32(unsigned char *bytes) {
    return (int32_t)((uint32_t)bytes[0] | ((uint32_t)bytes[1] << 8) | ((uint32_t)bytes[2] << 16) | ((uint32_t)bytes[3] << 24));
}

int main() {
    FILE *fp;
    unsigned char b[24];

    // Abre o dispositivo de entrada do mouse
    fp = fopen("/dev/input/event0", "rb");
    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir o dispositivo de entrada\n");
        return 1;
    }

    while (1) {
        // Lê os dados brutos do dispositivo de entrada
        if (fread(b, sizeof(unsigned char), sizeof(b), fp) != sizeof(b)) {
            if (feof(fp)) {
                // Fim do arquivo, reabre o dispositivo para continuar a leitura
                fclose(fp);
                fp = fopen("/dev/input/event8", "rb");
                if (fp == NULL) {
                    fprintf(stderr, "Erro ao reabrir o dispositivo de entrada\n");
                    return 1;
                }
            } else {
                fprintf(stderr, "Erro ao ler do dispositivo de entrada\n");
                return 1;
            }
        }

        uint16_t code = little_endian_uint16(&b[18]);
        uint16_t type = little_endian_uint16(&b[16]);
        int32_t value = little_endian_int32(&b[20]);

        //printf("%u\n", code);
        
        if(type == 2) {
            if(code == 0){
                if(value > 0){
                    printf("Direita\n");
                } else if (value < 0) {
                    printf("Esuqerda\n");
                }
            }
            else if(code == 1){
                if(value > 0){
                    printf("Baixo\n");
                } else if (value < 0){
                    printf("Cima\n");
                }
            }
        }
    }

    // Nunca será alcançado neste exemplo
    fclose(fp);
    return 0;
}
