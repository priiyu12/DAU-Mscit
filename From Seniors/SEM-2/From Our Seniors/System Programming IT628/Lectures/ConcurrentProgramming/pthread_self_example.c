#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

int main()
{
	printf("Process %d has thread ID %ld\n", getpid(), pthread_self());
}