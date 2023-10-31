#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_CLIENTS 10

void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    free(arg);

    // Handle client requests here
    // You can implement your server logic in this function
    // Example: read/write data from/to the client

    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t threads[MAX_CLIENTS];
    int client_count = 0;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating server socket");
        exit(1);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(12345); // You can choose any port

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr) == -1) {
        perror("Error binding server socket");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Error listening on server socket");
        exit(1);
    }

    printf("Server is listening on port 12345...\n");

    while (1) {
        // Accept a new connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Error accepting client connection");
            continue;
        }

        // Create a new thread to handle the client
        pthread_t thread;
        int *client_socket_ptr = (int *)malloc(sizeof(int));
        if (client_socket_ptr == NULL) {
            perror("Error allocating memory for client socket pointer");
            continue;
        }
        *client_socket_ptr = client_socket;

        if (pthread_create(&thread, NULL, handle_client, (void *)client_socket_ptr) != 0) {
            perror("Error creating thread");
            free(client_socket_ptr);
            close(client_socket);
        } else {
            threads[client_count] = thread;
            client_count++;
        }
    }

    // Join all threads
    for (int i = 0; i < client_count; i++) {
        pthread_join(threads[i], NULL);
    }

    close(server_socket);
    return 0;
}