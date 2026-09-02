#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void inthandler(int s)
{
	printf(" Received SIGINT signal %d .. waiting\n", s );
	printf(" Leaving inthandler \n");
}

void quithandler(int s)
{
	signal(SIGINT, SIG_IGN);
	printf(" Received SIGQUIT signal %d .. waiting\n", s );
	sleep(5);
	printf(" Leaving quithandler \n");
	signal( SIGINT, inthandler );
}

int main(int ac, char *av[])
{
	char input[100];
	signal( SIGINT, inthandler ); // set trap
	signal( SIGQUIT, quithandler ); // set trap
	int i=1;
	while (i<2)
	{
		sleep(5);
		printf("main:%d\n",i++);
		printf("sending SIGQUIT signal\n");
		kill(getpid(), SIGQUIT);
	}
}
