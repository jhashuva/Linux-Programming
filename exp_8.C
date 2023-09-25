#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int pipe_fd[2];
    pid_t pid;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        error("pipe");
    }

    // Fork a child process
    if ((pid = fork()) == -1) {
        error("fork");
    }

    if (pid == 0) { // Child process
        // Redirect stdout to the write end of the pipe
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        // Execute the 'ls' command
        execlp("ls", "ls", NULL);
        error("execlp ls");
    } else { // Parent process
        // Wait for the child to finish
        wait(NULL);

        // Close the write end of the pipe
        close(pipe_fd[1]);

        // Redirect stdin to the read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);

        // Execute the 'wc' command with options '-l -c -w'
        execlp("wc", "wc", "-l", "-c", "-w", NULL);
        error("execlp wc");
    }

    return 0;
}
