#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int global_var = 1;

int main() {
    pid_t pid;

    // Using fork
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // This code runs in the child process created by fork
        global_var++;
        printf("Child (fork) - Process ID: %d, Parent Process ID: %d, Global Variable: %d\n", getpid(), getppid(), global_var);
        exit(0);
    } else {
        // This code runs in the parent process
        printf("Parent (fork) - Process ID: %d, Child Process ID: %d, Global Variable: %d\n", getpid(), pid, global_var);
        wait(NULL);
    }

    // Using vfork
    pid = vfork();

    if (pid < 0) {
        perror("vfork failed");
        exit(1);
    } else if (pid == 0) {
        // This code runs in the child process created by vfork
        global_var++;
        printf("Child (vfork) - Process ID: %d, Parent Process ID: %d, Global Variable: %d\n", getpid(), getppid(), global_var);
        _exit(0); // Using _exit to avoid issues with vfork
    } else {
        // This code runs in the parent process
        printf("Parent (vfork) - Process ID: %d, Child Process ID: %d, Global Variable: %d\n", getpid(), pid, global_var);
        // No need to wait with vfork; the child runs in the parent's address space
    }

    return 0;
}
