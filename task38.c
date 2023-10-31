#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void handle_client(int client_socket) {
    // Handle client requests here
    // You can implement your server logic in this function
    // Example: read/write data from/to the client

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating server socket");
        exit(1);
    }

    // Set up server address
    memset(&server_addr, 0, sizeof(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(12345); // You can choose any port

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
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
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Error accepting client connection");
            continue;
        }

        // Fork a child process to handle the client
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("Error forking a child process");
            exit(1);
        }

        if (child_pid == 0) { // This is the child process
            close(server_socket); // Close the server socket in the child process

            // Handle the client
            handle_client(client_socket);

            exit(0); // Terminate the child process
        } else { // This is the parent process
            close(client_socket); // Close the client socket in the parent process
        }

        // Reap zombie child processes
        while (waitpid(-1, NULL, WNOHANG) > 0);
    }

    close(server_socket);
    return 0;
}