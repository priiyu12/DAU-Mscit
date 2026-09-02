#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	int pid;
	printf("Im the original process with PID %d and PPID %d. \n", getpid(), getppid());
	pid = fork(); /* Duplicate. Child and parent continue from here */
	if (pid != 0) /* pid is non-zero, so I must be the parent --> Parent and Child execute from this point */
	{
		int childPid, status;
		printf("Im the parent process with PID %d and PPID %d. \n", getpid(), getppid());
		printf("My child�s PID is %d \n", pid);
		childPid = wait(&status); // add wait in parent process to wait for child process, child will not become orphan
		printf("status: %d\n", status);
		printf("child with PID %d exited with exit code %d\n", childPid, WEXITSTATUS(status));
		if WIFEXITED (status)
			printf("child with PID %d terminated normally\n", childPid);
		else if WIFSIGNALED (status)
			printf("child with PID %d was terminated by signal %d\n", childPid, WTERMSIG(status));
		else
			printf("child with PID %d had abnormal termination\n", childPid);
	}
	else /* pid is zero, so I must be the child */
	{
		sleep(10); // add sleep so child process will terminate later then parent
		printf("Im the child process with PID %d and PPID %d. \n", getpid(), getppid());
		exit(100);
	}
	printf("PID %d terminates. \n", getpid()); /* Both processes execute this */
}
