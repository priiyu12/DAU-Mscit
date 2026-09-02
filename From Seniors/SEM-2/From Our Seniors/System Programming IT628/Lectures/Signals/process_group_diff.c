#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler()
{
	printf("process %d got a SIGINT\n", getpid());
}

int main(void)
{
	signal(SIGINT, signal_handler);
	if (fork() == 0) // child
	{
		printf("child pid %d and child group %d waits\n", getpid(), getpgid(0));
		setpgid(getpid(), 0); // set process group as pid for child
		printf("child pid %d and child group %d waits\n", getpid(), getpgid(0));
	}
	else // parent
		printf("parent pid %d and parent group %d waits\n", getpid(), getpgid(0));

	pause(); // wait for signal
}
