#include <stdio.h>
#include <unistd.h>

int main( int argc, char* argv[] )
{
	int cpid, status;
	if ( fork() == 0 ) /* Child */
	{
		execvp( argv[1], &argv[1] ); /* Execute other program */
		fprintf( stderr, "Could not execute %s \n", argv[1] );
	}
	else	/* parent */
	{
		printf("In this case there is nothing to be done in parent\n");
		
		printf("Parent is waiting for child to terminate\n");
		cpid = wait(&status);
	}
}