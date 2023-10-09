#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_SIZE 128

// Define a structure for messages
struct msg_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

// Function to check if a number is prime
int is_prime(int num) {
    if (num <= 1)
        return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

// Function to check if a number is even
int is_even(int num) {
    return (num % 2 == 0);
}

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // Generate a unique key for the message queue
    key = ftok("/tmp", 'A'); // You can use any file and character as an identifier

    // Create a message queue (or get an existing one)
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Server Process (Process 2)
    if (fork() == 0) {
        while (1) {
            // Receive service request from the message queue
            msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);

            // Process the service request
            int result;
            if (strcmp(message.msg_text, "isprime") == 0) {
                result = is_prime(atoi(message.msg_text));
            } else if (strcmp(message.msg_text, "iseven") == 0) {
                result = is_even(atoi(message.msg_text));
            } else {
                result = -1; // Invalid service request
            }

            // Prepare the response message
            sprintf(message.msg_text, "%d", result);
            message.msg_type = message.msg_type + 1;

            // Send the response back to the client
            msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        }
    }

    // Client Process 3 (Request 'isprime' service)
    if (fork() == 0) {
        message.msg_type = 1; // Client message type
        strcpy(message.msg_text, "isprime");

        // Send the service request to the server
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);

        // Receive the response from the server
        msgrcv(msgid, &message, sizeof(message.msg_text), 2, 0);
        printf("Process 3: Is Prime? %s\n", message.msg_text);
    }

    // Client Process 4 (Request 'iseven' service)
    if (fork() == 0) {
        message.msg_type = 1; // Client message type
        strcpy(message.msg_text, "iseven");

        // Send the service request to the server
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);

        // Receive the response from the server
        msgrcv(msgid, &message, sizeof(message.msg_text), 3, 0);
        printf("Process 4: Is Even? %s\n", message.msg_text);
    }

    // Wait for child processes to finish
    wait(NULL);
    wait(NULL);
    wait(NULL);

    // Remove the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
