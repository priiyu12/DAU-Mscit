#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

struct params
{
	int num1;
	int num2;
};

void * thread_fn_multiple_param(void *arg)
{
	printf("thread id %u is starting \n", (unsigned int)pthread_self());
	struct params *thread_p = arg;
	printf("Thread with One Param: %d + %d = %d\n", thread_p->num1, thread_p->num2, thread_p->num1+thread_p->num2);
	printf("thread id %u is exiting \n", (unsigned int)pthread_self());

}

int main(int argc, char *argv[])
{
	pthread_t threadID;
	printf("main thread id %u is starting \n", (unsigned int)pthread_self());
	struct params p;
	p.num1 = 5;
	p.num2 = 10;
	int err = pthread_create (&threadID, NULL, thread_fn_multiple_param, (void *)&p);
	if (err != 0)
			printf("cant create thread: %s\n", strerror(err));
	// wait for thread creation and execution
	sleep(1);
	printf("main thread id %u is exiting \n", (unsigned int)pthread_self());
	
		
}
