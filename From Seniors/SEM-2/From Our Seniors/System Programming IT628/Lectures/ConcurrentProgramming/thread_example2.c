#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void * child_thr_fn(void *arg)
{
		printf("child\'s child1 thread id %u is starting \n", (unsigned int)pthread_self());
		sleep(3);
		printf("child\'s child1 thread id %u is ending \n", (unsigned int)pthread_self());
}

void * child_thr_fn1(void *arg)
{
		printf("child\'s child2 thread id %u is starting \n", (unsigned int)pthread_self());
		sleep(10);
		printf("child\'s child2 thread id %u is ending \n", (unsigned int)pthread_self());
}

void * thr_fn(void *arg)
{
	pthread_t tid;
	printf("child1 thread id %u is starting \n", (unsigned int)pthread_self());
	//sleep(1);	// ensure main thread exit first
	int err = pthread_create(&tid, NULL, child_thr_fn, NULL);
	sleep(2);
	printf("child1 thread id %u is calling return\n", (unsigned int)pthread_self());
	//exit(0);
	return 0;
}

void * thr_fn1(void *arg)
{
	pthread_t tid;
	printf("child2 thread id %u is starting \n", (unsigned int)pthread_self());
	//sleep(1);	// ensure main thread exit first
	int err = pthread_create(&tid, NULL, child_thr_fn1, NULL);
	sleep(5);
	printf("child2 thread id %u is calling return\n", (unsigned int)pthread_self());
}

int main(void)
{
	pthread_t tid;
	printf("Main thread %u is starting\n", (unsigned int)pthread_self());
	int err = pthread_create(&tid, NULL, thr_fn, NULL);
	err = pthread_create(&tid, NULL, thr_fn1, NULL);
	sleep(5);	// just enough wait for child thread to start
	printf("Main thread %u is finished\n", (unsigned int)pthread_self());
	return(0);
}
