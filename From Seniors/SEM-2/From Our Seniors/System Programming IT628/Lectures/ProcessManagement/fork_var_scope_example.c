#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
	   
int main(void)
{
	int pid;
	int i=1;		// Variable available in parent as well as child
    printf("Im the original process with PID %d and PPID %d. \n", getpid(), getppid() );
	printf("i before fork: %d\n", i);
    pid = fork(); /* Duplicate. Child and parent continue from here */
	i = i+4;
    if ( pid!= 0 ) /* pid is non-zero, so I must be the parent --> Parent and Child execute from this point */
    {
        printf("I’m the parent process with PID %d and PPID %d. \n", getpid(), getppid() );
        printf("My child’s PID is %d \n", pid );
		printf("i in parent before update: %d\n", i);
		i = i + 5;
		printf("i in parent after update: %d\n", i);
		int i_parent = 2;
		printf("i_parent from parent=%d\n",i_parent);
    }
	else /* pid is zero, so I must be the child */
    {
        printf("Im the child process with PID %d and PPID %d. \n", getpid(), getppid() );
		printf("i in child before update: %d\n", i);
		i = i + 10;
		printf("i in child after update: %d\n", i);
		//printf("i_parent from child=%d\n",i_parent);
    }
	
	printf("both parent and child execute i=%d\n", i);
	//printf("both parent and child execute i_parent=%d\n",i_parent);
    printf("PID %d terminates. \n", getpid() ); /* Both processes execute this */
}
