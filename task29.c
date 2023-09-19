#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_MESSAGE_SIZE 256

// Define a structure for the message
struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MESSAGE_SIZE];
};

int main() {
    key_t msg_queue_key;
    int msg_queue_id;
    struct msg_buffer message;

    // Generate a unique key for the message queue
    if ((msg_queue_key = ftok(".", 'a')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Create or open the message queue
    if ((msg_queue_id = msgget(msg_queue_key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(1);
    }

    // Prepare a message to send
    message.msg_type = 1; // Message type must be greater than 0
    strcpy(message.msg_text, "Hello, Message Queue!");

    // Send the message to the queue
    if (msgsnd(msg_queue_id, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent: %s\n", message.msg_text);

    // Receive a message from the queue
    if (msgrcv(msg_queue_id, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }

    printf("Message received: %s\n", message.msg_text);

    // Remove the message queue
    if (msgctl(msg_queue_id, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
