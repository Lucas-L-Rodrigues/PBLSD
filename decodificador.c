#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

// Struct encontrada na documentação do linux inputs para decodificar o arquivo binário 
// de eventos do mouse
struct input_event {
    struct timeval time;
    unsigned short type;
    unsigned short code;
    unsigned int value;
};

int main() {
    int fd;
    struct input_event event;

    // Abertura do arquivo de eventos do mouse
    fd = open("/dev/input/event6", O_RDONLY);
    if (fd == -1) {
        perror("Erro na abertura do arquivo");
        return 1;
    }

    while (1) {
        // Leitura dos eventos
        ssize_t bytes_read = read(fd, &event, sizeof(event));
        if (bytes_read == -1) {
            perror("Erro na leitura do evento");
            close(fd);
            return 1;
        } else if (bytes_read != sizeof(event)) {
            fprintf(stderr, "Evento incompleto\n");
            continue;
        }

        // Verifica se houve um botão pressionado, e se sim, qual botão foi usado
        if (event.type == 1 && (event.code == 272 || event.code == 273) && event.value == 1) {
            // Print do evento é feito a aprtir dos atributos da struct
            printf("Time: %ld.%06ld, Botão: %s\n",
                   event.time.tv_sec, event.time.tv_usec,
                   event.code == 272 ? "Esquerda" : "Direita");
        }
    }
    close(fd);
    return 0;
}
