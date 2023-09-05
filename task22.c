#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int globvar = 6; /* External variable in initialized data */

int main(void) {
    int var; /* Automatic variable on the stack */
    pid_t pid;
    var = 88;
    printf("before vfork\n"); /* We don't flush stdio */

    if ((pid = vfork()) < 0) {
        perror("vfork error"); /* Corrected error message function */
        exit(1); /* Exit with an error status */
    } else if (pid == 0) { /* Child */
        globvar++; /* Modify parent's variable */
        var++;
        _exit(0); /* Child terminates */
    }

    /* Parent continues here */
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}
