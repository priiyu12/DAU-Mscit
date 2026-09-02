/*
This code shows an approach for application allocation and deallocation to core using semaphores. Assuming there are 4 cores in a system.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaphore;
pthread_t tid1, tid2;

void * allocate_core(void* arg)
{
	sleep(context_switch_time);
	sem_wait(&semaphore);
	// get thread (KTL) details from ready circular queue
	// allocate the core to thread (KLT)
}

void * deallocate_core(void* arg)
{
	sleep(context_switch_time);
	// deallocate thread (KTL) from the core
	// add thread (KLT) to ready queue
	sem_post(&semaphore);

}

int main()
{
	// initialize semaphore with number of allowable locks
	// in our case we are using 4 for each core
	sem_init(&semaphore, 0, 4);
	
	pthread_create(&tid1, NULL, allocate_core, NULL);
	pthread_create(&tid2, NULL, deallocate_core, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
}