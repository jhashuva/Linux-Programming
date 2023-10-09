#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

// Signal handler function
void sigchld_handler(int signo) {
    int status;
    pid_t pid;

    // Wait for any child process to terminate and get its status
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child process with PID %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process with PID %d terminated by signal %d\n", pid, WTERMSIG(status));
        }
    }
}

int main() {
    pid_t child_pid;
    int status;

    // Register the signal handler for SIGCHLD
    if (signal(SIGCHLD, sigchld_handler) == SIG_ERR) {
        perror("Failed to register signal handler");
        return 1;
    }

    // Create a child process
    if ((child_pid = fork()) == 0) {
        // This is the child process
        printf("Child process executing...\n");
        // Simulate some work
        sleep(2);
        // Exit the child process with a status code
        exit(42);
    } else if (child_pid < 0) {
        perror("Failed to fork");
        return 1;
    } else {
        // This is the parent process
        printf("Parent process waiting for child to exit...\n");
        // Parent process can continue doing other work
        // Child's exit status will be handled asynchronously by the signal handler

        // Sleep to allow time for the child to finish
        sleep(5);
    }

    return 0;
}
