// Compile with : gcc -pthread -o threadtest.out threadtest.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void * thr_fn1( void *arg)
{
	sleep(0.25);
	printf("child thread %u exiting\n", (unsigned int)pthread_self());
	int *ret1 = (int *)malloc(sizeof(int));
	*ret1 = 1;
	return ((void *) ret1);
}

void * thr_fn2( void *arg)
{
	sleep(1);
	printf("child thread %u exiting\n", (unsigned int)pthread_self());
	int *ret2 = (int *)malloc(sizeof(int));
	*ret2 = 2;
	pthread_exit((void *) ret2);
}

int main(void)
{
	int err;
	pthread_t tid1, tid2;
	int *tret1, *tret2;

	printf("Main thread is %u \n", (unsigned int)pthread_self());

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
		printf("cant create thread1: %s\n", strerror(err));
	else
		printf("child thread %u is created\n", (unsigned int)tid1);
	
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
		printf("cant create thread2: %s\n", strerror(err));
	else
		printf("child thread %u is created\n", (unsigned int)tid2);
	printf("main thread %u will wait for child thread %u\n", (unsigned int)pthread_self(), (unsigned int)tid1);
	err = pthread_join(tid1, (void **)&tret1);
	if (err != 0)
		printf("cant join with thread1: %s\n", strerror(err));
	printf("child thread %u exit code %d\n", (unsigned int)tid1, (int)(*tret1));
	free(tret1);
	printf("main thread %u will wait for child thread %u\n", (unsigned int)pthread_self(), (unsigned int)tid2);
	err = pthread_join(tid2, (void **)&tret2);
	if (err != 0)
		printf("cant join with thread2: %s\n", strerror(err));
	printf("child thread %u exit code %d\n", (unsigned int)tid2, (int)(*tret2));
	free(tret2);
	printf("Main thread %u exiting\n", (unsigned int)pthread_self());
	pthread_exit(0);
}


