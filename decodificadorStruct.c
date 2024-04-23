//CÓDIGO QUE DECODIFICA TODO O ARQUIVO DO MOUSE

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

struct timeval {
    long tv_sec;  // segundos
    long tv_usec; // microssegundos
};

// Define the input_event struct manually
struct input_event {
    struct timeval timestamp; // Renamed 'time' to 'timestamp'
    unsigned short type;
    unsigned short code;
    unsigned int value;
};

int main() {
    int fd;
    struct input_event event;

    // Open the mouse event file
    fd = open("/dev/input/event0", O_RDONLY);
    if (fd == -1) {
        perror("Error opening mouse event file");
        return 1;
    }

    while (1) {
        // Read the input event
        ssize_t bytes_read = read(fd, &event, sizeof(event));
        if (bytes_read == -1) {
            perror("Error reading mouse event");
            close(fd);
            return 1;
        } else if (bytes_read != sizeof(event)) {
            fprintf(stderr, "Incomplete event read\n");
            continue;
        }

        // Decode and print the event
        printf("Timestamp: %ld.%06ld, Type: %hu, Code: %hu, Value: %u\n",
               event.timestamp.tv_sec, event.timestamp.tv_usec,
               event.type, event.code, event.value);
    }

    // Close the file descriptor
    close(fd);
    
    return 0;
}
