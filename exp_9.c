#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 128

// Define a structure for your message
struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate a unique key for the message queue
    key = ftok("/tmp", 'A'); // You can use any file and character as an identifier

    // Create a message queue (or get an existing one)
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Fork a child process for communication
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (child_pid == 0) {
        // This is the child process (Receiver)

        // Receive a message from the message queue
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);

        // Display the received message
        printf("Received Message: %s\n", message.msg_text);
    } else {
        // This is the parent process (Sender)

        // Prepare the message
        message.msg_type = 1; // Message type must be greater than 0
        strcpy(message.msg_text, "Hello from parent process!");

        // Send the message to the message queue
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);

        // Wait for the child process to finish
        wait(NULL);

        // Remove the message queue
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
