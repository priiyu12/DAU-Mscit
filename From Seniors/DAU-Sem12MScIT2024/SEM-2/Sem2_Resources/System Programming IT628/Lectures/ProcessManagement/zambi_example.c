#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
	   
int main(void)
{
    int pid;
    pid = fork(); /* Duplicate */
    if ( pid!= 0 ) /* Branch based on return value from fork() */
    {
		printf("Im the parent process with PID %d and PPID %d. \n", getpid(), getppid() );
        printf("My child’s PID is %d \n", pid );

        while (1) /* Never terminate, and never execute a wait() */
        sleep(1000);
    }
    else
    {
		printf("Im the child process with PID %d and PPID %d. \n", getpid(), getppid() );
        exit(42); /* Exit with a silly number */
    }
}
