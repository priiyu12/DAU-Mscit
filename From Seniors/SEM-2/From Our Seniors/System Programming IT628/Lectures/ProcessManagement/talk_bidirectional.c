#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define	READ	0      /* The index of the “read” end of the pipe */ 
#define	WRITE	1      /* The index of the “write” end of the pipe */ 
char*  from_parent_phrase ="Parent sending info to child";
char*  from_child_phrase ="Child sending info to parent";

int main(void) 
{
	int fd1[2], fd2[2], bytesRead; 
	char message[100];   /* process message buffer */
	pipe(fd1);  /* For fd1, Parent - writer, Child - reader */
	pipe(fd2);	/* For fd2, Parent - reader, Child - writer */
	if ( fork() == 0 )  /* Child */
	{
		close(fd1[WRITE]); /* Close unused end */
		close(fd2[READ]); /* Close unused end */
		printf("Child: Sending message \'%s\' to parent\n", from_child_phrase);
		write(fd2[WRITE], from_child_phrase, strlen(from_child_phrase)+1); /* Send */
		bytesRead = read( fd1[READ], message, 100 ); /* Receive */
		printf("Child: Read %d bytes: %s \n", bytesRead, message );
		close(fd1[READ]); /* Close used end */
		close(fd2[WRITE]); /* Close used end */
	} 
	else      /* Parent */
	{
		close(fd1[READ]);  /* Close unused end */
		close(fd2[WRITE]);  /* Close unused end */
		printf("Parent: Sending message \'%s\' to child\n", from_parent_phrase);
		write(fd1[WRITE], from_parent_phrase, strlen(from_parent_phrase)+1); /* Send */
		bytesRead = read( fd2[READ], message, 100 ); /* Receive */
		printf("Parent: Read %d bytes: %s \n", bytesRead, message );
		close(fd1[WRITE]);  /* Close used end */ 
		close(fd2[READ]);  /* Close used end */ 
	}
}
