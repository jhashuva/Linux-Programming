#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void err_sys(const char* x) 
{ 
    perror(x); 
    exit(1); 
}

void pr_exit(int status){
   printf("Status: %d",status);
   exit(0);
}

int main(void)
{
pid_t pid;
int status;
if ((pid = fork()) < 0)
    err_sys("fork error");
else if (pid == 0) /* child */
    exit(7);
if (wait(&status) != pid) /* wait for child */
    err_sys("wait error");
pr_exit(status); /* and print its status */

if ((pid = fork()) < 0)
    err_sys("fork error");
else if (pid == 0) /* child */
    abort(); /* generates SIGABRT */

if (wait(&status) != pid) /* wait for child */
    err_sys("wait error");
pr_exit(status); /* and print its status */

if ((pid = fork()) < 0)
    err_sys("fork error");
else if (pid == 0) /* child */
    status /= 0; /* divide by 0 generates SIGFPE */
if (wait(&status) != pid) /* wait for child */
    err_sys("wait error");
pr_exit(status); /* and print its status */
exit(0);
}
