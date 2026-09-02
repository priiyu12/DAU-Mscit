#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void * thread_fn_no_param(void *arg)
{
	printf("thread id %u is starting \n", (unsigned int)pthread_self());
	int num1=5, num2=10;
	printf("Thread with No Param: %d + %d = %d\n", num1, num2, num1+num2);
	printf("thread id %u is exiting \n", (unsigned int)pthread_self());
}

int main(int argc, char *argv[])
{
	pthread_t threadID;
	printf("main thread id %u is starting \n", (unsigned int)pthread_self());
	int err = pthread_create (&threadID, NULL, thread_fn_no_param, NULL);
	if (err != 0)
			printf("cant create thread: %s\n", strerror(err));
	
	// wait for thread creation and execution
	sleep(1);
	printf("main thread id %u is exiting \n", (unsigned int)pthread_self());
}
