#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Create a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // This code runs in the child process
        printf("Child process is running\n");
        // Simulate some work in the child
        sleep(2);
        printf("Child process is done\n");
        exit(0); // Exit the child process
    } else {
        // This code runs in the parent process
        printf("Parent process is waiting for the child to finish...\n");
        wait(&status); // Wait for the child to exit
        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
        printf("Parent process is done\n");
    }

    return 0;
}
