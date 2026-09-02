#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler()
{
	printf("process %d got a SIGINT\n", getpid());
}

int main(void)
{
	int i,status;
	signal(SIGINT, signal_handler);
	if (fork() ==0)	// child
	{
		//setpgid(getpid(), 0);	// set process group as pid for child
		printf("child pid %d and child group %d waits\n", getpid(), getpgid(0));
		sleep(1);
		printf("Child input:");
		fflush(stdout);
		scanf("%d", &i);
	}
	else		// parent
		printf("parent pid %d and parent group %d waits\n", getpid(), getpgid(0));
		printf("Parent input:");
		fflush(stdout);
		scanf("%d", &i);
		//pause();	// wait for signal
		wait(&status);
}
