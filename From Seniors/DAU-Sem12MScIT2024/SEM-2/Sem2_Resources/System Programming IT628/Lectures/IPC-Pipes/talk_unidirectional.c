#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define	READ	0      /* The index of the “read” end of the pipe */ 
#define	WRITE	1      /* The index of the “write” end of the pipe */ 
char*  phrase ="Dummy data written to pipe";
int main(void) 
{
	int fd[2], bytesRead, status; 
	char message[100];   /* Parent process' message buffer */
	pipe(fd);  /* Create  an unnamed pipe */
	if ( fork() == 0 )  /* Child, write */
	{
		close(fd[READ]); /* Close unused end */
		printf("Child: Sending message \'%s\' to parent\n",phrase);
		write(fd[WRITE], phrase, strlen(phrase)+1); /* Send */
		close(fd[WRITE]); /* Close used end */
	} 
	else      /* Parent, reader */
	{
		close(fd[WRITE]);  /* Close unused end */
		bytesRead = read( fd[READ], message, 100 ); /* Receive */
		printf("Parent: Read %d bytes: %s \n", bytesRead, message );
		wait(&status);
		close(fd[READ]);  /* Close used end */ 
	}
}
