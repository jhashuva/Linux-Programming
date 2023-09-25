#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    char *fifo1 = "/tmp/fifo1"; // FIFO for sender to receiver
    char *fifo2 = "/tmp/fifo2"; // FIFO for receiver to sender

    mkfifo(fifo1, 0666); // Create FIFO1
    mkfifo(fifo2, 0666); // Create FIFO2

    char message[100];

    int fd1 = open(fifo1, O_WRONLY);
    int fd2 = open(fifo2, O_RDONLY);

    while (1) {
        printf("Sender: Enter a message (or 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);

        // Send message to the receiver
        write(fd1, message, sizeof(message));

        if (strcmp(message, "exit\n") == 0) {
            break;
        }

        // Receive and display the response from the receiver
        read(fd2, message, sizeof(message));
        printf("Receiver: %s", message);
    }

    close(fd1);
    close(fd2);

    unlink(fifo1); // Remove FIFO1
    unlink(fifo2); // Remove FIFO2

    return 0;
}
