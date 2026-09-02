#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
	int value; 
	sem_t sem;
	sem_init(&sem, 0, 0);
	sem_getvalue(&sem, &value);
	printf("Semaphore value before post:%d\n", value);
	sem_post(&sem);
	sem_post(&sem);
	sem_post(&sem);
	sem_getvalue(&sem, &value);
	printf("Semaphore value after post:%d\n", value);

}