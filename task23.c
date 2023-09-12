#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
//#include "apue.h"

void pr_exit(int status){
   printf("Status: %d",status);
   exit(0);
   }

void err_sys(const char* x) 
{ 
    perror(x); 
    exit(1); 
}


int main(void) {
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        // Child process with normal termination
        exit(7);
    }

    // Parent process
    if (wait(&status) != pid)
        err_sys("wait error");

    pr_exit(status);

    // Create another child process with abnormal termination (e.g., division by zero)
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        // Child process with abnormal termination
        int a = 1, b = 0;
        int result = a / b;
        exit(0); // This line will not be reached due to the division by zero
    }

    // Parent process
    if (wait(&status) != pid)
        err_sys("wait error");

    pr_exit(status);

    return 0;
}
