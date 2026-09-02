#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  pid_t child;
  int shmid; // shared memory id
  int* shmptr; // pointer to shared memory

  shmid = shmget((key_t) 1234, 3 * sizeof(int), IPC_CREAT | 0666);
  if (shmid == -1) {
    perror("shmget");
    return -1;
  }
  shmptr = (int*) shmat(shmid, NULL, 0);
  if (shmptr == (void*) -1) {
    perror("shmat");
    return -1;
  }

  shmptr[2] = 0; // we are going to calculate sum of numbers,
// therefore set initial value to 0

  child = fork();
  if (child == -1) {
     perror("fork");
     return -1;
  } if (child > 0) {
     waitpid(child, NULL, 0);
     int s = shmptr[0], e = shmptr[1], r = shmptr[2];
     printf("Sum of numbers from %d to %d is %d.\n", s, e, r);
  } else if (child == 0) {
     int i;
     printf("Enter start and end numbers: ");
     scanf("%d %d", &shmptr[0], &shmptr[1]);
     for (i = shmptr[0]; i <= shmptr[1]; i++)
        shmptr[2] += i;
     return 0;
  }
 
  if (shmdt(shmptr) == -1) {
     perror("shmdt");
     return -1;
  }

  if (shmctl(shmid, IPC_RMID, NULL) == -1) {
     perror("shm remove");
     return -1;
  }

  return 0;
}