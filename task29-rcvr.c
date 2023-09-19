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

    int fd1 = open(fifo1, O_RDONLY);
    int fd2 = open(fifo2, O_WRONLY);

    while (1) {
        // Receive and display the message from the sender
        read(fd1, message, sizeof(message));
        printf("Sender: %s", message);

        if (strcmp(message, "exit\n") == 0) {
            break;
        }

        // Send a response to the sender
        printf("Receiver: Enter a response: ");
        fgets(message, sizeof(message), stdin);
        write(fd2, message, sizeof(message));
    }

    close(fd1);
    close(fd2);

    unlink(fifo1); // Remove FIFO1
    unlink(fifo2); // Remove FIFO2

    return 0;
}
