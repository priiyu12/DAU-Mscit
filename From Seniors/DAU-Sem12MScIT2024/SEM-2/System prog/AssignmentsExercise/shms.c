//ID - 202412048 Harsh Mehta

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>

#define SIZE 10

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[]) {
    if (argc != SIZE + 1) {
        printf("Enter 10 integers\n", argv[0]);
        exit(1);
    }

    // Shared Memory for Array
    int shmid = shmget(1234, SIZE * sizeof(int), 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget array error");
        exit(1);
    }
    int *arr = (int *)shmat(shmid, NULL, 0);

    for (int i = 0; i < SIZE; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    // Shared Memory for Semaphore
    int semid = shmget(1235, sizeof(sem_t), 0666 | IPC_CREAT);
    if (semid < 0) {
        perror("shmget semaphore error");
        exit(1);
    }
    sem_t *sem1 = (sem_t *)shmat(semid, NULL, 0);

    sem_init(sem1, 1, 0);  // Shared semaphore

    if (fork() == 0) {
        // Child 1
        qsort(arr, 5, sizeof(int), compare);
        sem_post(sem1);  // Signal C2
        exit(0);
    }

    if (fork() == 0) {
        // Child 2
        sem_wait(sem1);  // Wait for C1
        qsort(arr + 5, 5, sizeof(int), compare);
        int max = (arr[4] > arr[9]) ? arr[4] : arr[9];
        printf("Maximum element = %d\n", max);
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    int min = (arr[0] < arr[5]) ? arr[0] : arr[5];
    printf("Minimum element = %d\n", min);

    shmdt(arr);
    shmctl(shmid, IPC_RMID, NULL);

    shmdt(sem1);
    shmctl(semid, IPC_RMID, NULL);

    sem_destroy(sem1);

    return 0;
}