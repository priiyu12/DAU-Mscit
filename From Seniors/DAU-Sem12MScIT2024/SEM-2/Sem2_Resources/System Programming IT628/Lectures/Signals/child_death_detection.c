#include <stdio.h> 
#include <signal.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int delay; 

void childHandler()  /* Executed if the child dies before the parent */ 
{
	int  childPid, childStatus;
	childPid = wait(&childStatus);   /* Accept child’s termination code */
	printf("Child %d terminated within %d seconds \n", childPid, delay);
	exit(/* EXIT SUCCESS */  0); 
}

int main( int argc, char* argv[] ) 
{
	int pid;
	signal( SIGCHLD, childHandler );  /* Install death-of-child handler */
	pid = fork();  /* Duplicate */
	if ( pid == 0 )  /* Child */
	{
		execvp( argv[2], &argv[2] );   /* Execute command */
		perror("limit");   /* Should never execute */ 
    } 
	else   /* Parent */ 
	{
		sscanf( argv[1], "%d", &delay );  /* Read delay from command-line */
		sleep(delay);   /* Sleep for the specified number of seconds */
		printf("Child %d exceeded limit and is being killed \n", pid );
		kill( pid, SIGINT );   /* Kill the child */
	} 
} 
