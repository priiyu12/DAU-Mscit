#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaphore;

void threadfunc() {
    while (1) {
        sem_wait(&semaphore);
        printf("Hello from thread!\n");
        sem_post(&semaphore);
        sleep(1);
    }

}

int main(void) {

    // initialize semaphore, only to be used with threads in this process, set value to 1
    sem_init(&semaphore, 0, 1);
    pthread_t mythread;
    // start the thread
    printf("Starting thread, semaphore is unlocked.\n");
    pthread_create(&mythread, NULL, (void*)threadfunc, NULL);

    getchar();

    sem_wait(&semaphore);
    printf("Semaphore locked.\n");
    // do stuff with whatever is shared between threads
    getchar();
    printf("Semaphore unlocked.\n");
    sem_post(&semaphore);

    getchar();
    
    return 0;
}

/*
faculty@faculty-OptiPlex-3040:~/IT628-SystemProgramming$ ./semaphore1.out 
Starting thread, semaphore is unlocked.
Hello from thread!
Hello from thread!
Hello from thread!
Hello from thread!
Hello from thread!
Hello from thread!

Semaphore locked.

Semaphore unlocked.
Hello from thread!
Hello from thread!
Hello from thread!
Hello from thread!
Hello from thread!

faculty@faculty-OptiPlex-3040:~/IT628-SystemProgramming$ 

*/
