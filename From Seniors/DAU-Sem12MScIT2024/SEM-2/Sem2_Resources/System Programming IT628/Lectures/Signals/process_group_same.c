#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler()
{
	printf("process %d, %d got a SIGINT\n", getpid(), getpgid(0));
}

int main(void)
{
	signal(SIGINT, signal_handler);
	if (fork() ==0)	// child
		printf("child pid %d and child group %d waits\n", getpid(), getpgid(0));
	else		// parent
		printf("parent pid %d and parent group %d waits\n", getpid(), getpgid(0));

	pause();	// wait for signal

}
