#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main( int argc, char* argv[] )
{
	if (argc < 3)
	{
		printf("USAGE: parent_process.out <num1> <num2> ...");
	}
	int i, childPID, status;
	for(i=0; i<argc-1; i=i+2)
	{	// only parent will execute this code, why?
		if ( fork() == 0 ) /* Child */
		{
			printf("%s %s\n", argv[i+1], argv[i+2]);
			execl( "./process_child.out", "./process_child.out",argv[i+1], argv[i+2], NULL ); /* Execute other program */
			fprintf( stderr, "Could not execute %s \n", argv[1] );
		}
		else
		{
/*			childPID = wait(&status);
			printf("Child with PID=%d finished\n", childPID);
			printf("From Parent: %s + %s = %d\n", argv[i+1], argv[i+2], WEXITSTATUS(status));*/
		}
	}
	
	for(i=0; i<argc-1; i=i+2)
	{
		childPID = wait(&status);
		printf("Child with PID=%d finished\n", childPID);
		printf("From Parent: %s + %s = %d\n", argv[i+1], argv[i+2], WEXITSTATUS(status));
			
	}
}