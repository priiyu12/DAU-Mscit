#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void childHandler()
{
	int status, childPID;
	childPID = wait(&status);
	printf("Child PID=%d finished with sum=%d\n", childPID, WEXITSTATUS(status));
}
int main(int argc, char *argv[])
{

	int i, num1, num2;
	signal(SIGCHLD, childHandler);
	while (1)
	{
		// only parent will execute this code, why?
		printf("Enter two numbers sepeated by space\n");
		scanf("%d %d", &num1, &num2);
		// only child will execute this code
		if (fork() == 0) /* Child */
		{
			// printf("%d %d\n", num1, num2);
			// fflush(stdout);
			char num1_str[10], num2_str[10];
			sprintf(num1_str, "%d", num1);
			sprintf(num2_str, "%d", num2);
			execl("./process_child_sigchld.out", "./process_child_sigchld.out", num1_str, num2_str, NULL); /* Execute other program */
																										   // fprintf( stderr, "Could not execute %s \n", argv[1] );
		}
	}
}