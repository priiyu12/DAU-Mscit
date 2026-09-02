#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaphore[2];
int i=2, j=1;

void threadfunc1() {
	printf("%ld entering thread function 1\n",pthread_self());
    while (1) {
        sem_wait(&semaphore[0]);
		i = i + 2;
        printf("thread %ld: i=%d!\n", pthread_self(), i);
		sleep(1);
        sem_post(&semaphore[0]);
		sleep(1);
    }

}

void threadfunc2() {
	printf("%ld entering thread function 2\n",pthread_self());
    while (1) {
        sem_wait(&semaphore[1]);
		j = j + 2;
        printf("thread %ld: j=%d!\n",pthread_self(),j);
		sleep(1);
        sem_post(&semaphore[1]);
		sleep(1);
    }

}

int main(void) {

    // initialize semaphore, only to be used with threads in this process, set value to 1
    sem_init(&semaphore[0], 0, 1);
    sem_init(&semaphore[1], 0, 1);
	
    pthread_t mythreads[4];
    // start the thread
    pthread_create(&mythreads[0], NULL, (void*)threadfunc1, NULL);
	pthread_create(&mythreads[1], NULL, (void*)threadfunc1, NULL);
	pthread_create(&mythreads[2], NULL, (void*)threadfunc2, NULL);
	pthread_create(&mythreads[3], NULL, (void*)threadfunc2, NULL);

	pthread_join(mythreads[0], NULL);
	pthread_join(mythreads[1], NULL);
	pthread_join(mythreads[2], NULL);
	pthread_join(mythreads[3], NULL);
}

