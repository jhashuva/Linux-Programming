#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        printf("Child process: My PID is %d\n", getpid());
    } else {
        // Parent process
        printf("Parent process: My PID is %d\n", getpid());
        printf("Parent process: Child process ID is %d\n", child_pid);
    }

    return 0;
}


