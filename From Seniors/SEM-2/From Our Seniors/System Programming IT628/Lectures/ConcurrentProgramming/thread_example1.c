#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void * child_thr_fn(void *arg)
{
		printf("child\'s child thread id %u is starting \n", (unsigned int)pthread_self());
		sleep(3);
		printf("child\'s child thread id %u is ending \n", (unsigned int)pthread_self());
}

void * thr_fn(void *arg)
{
	pthread_t tid;
	printf("child thread id %u is starting \n", (unsigned int)pthread_self());
	int err = pthread_create(&tid, NULL, child_thr_fn, NULL);
	sleep(2);
	printf("child thread id %u is calling exit\n", (unsigned int)pthread_self());
	exit(0);
}
int main(void)
{
	pthread_t tid;
	printf("Main thread %u is starting\n", (unsigned int)pthread_self());
	int err = pthread_create(&tid, NULL, thr_fn, NULL);
	sleep(1);		// ensure tid thread calls exit before main thread is completed
	printf("Main thread %u is finished\n", (unsigned int)pthread_self());
	exit(0);
}
