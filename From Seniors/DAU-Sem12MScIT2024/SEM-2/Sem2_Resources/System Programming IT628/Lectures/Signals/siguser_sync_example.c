#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int parent_pid;

void sigalrm_handler()
{
	kill((getpgid(getpid())*-1), SIGUSR1);
}
void siguser1_handler()
{
	printf("SIGUSR1 is received by pid %d\n", getpid());
}
int main()
{
	int child_pids[5], i;
	parent_pid = getpid();
	printf("Parent process %d\n", parent_pid);
	// set SIGUSR1 handler
	signal(SIGUSR1, siguser1_handler);
	// create 5 child processes
	for (i=0; i<5; i++)
	{
		child_pids[i] = fork();
		// only for parent run the loop
		if (child_pids[i] != 0)
		{
			printf("Child process %d\n", child_pids[i]);
			continue;
		}
		else
			break;
	}
	// set SIGALRM handler for parent
	if (parent_pid == getpid())
	{
		signal(SIGALRM, sigalrm_handler);
		alarm(3);
	}
	while(1);
}