#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <semaphore.h>

int main() {
  int shmid;
  sem_t* mutex;

  shmid = shmget((key_t) 1236, sizeof(sem_t), IPC_CREAT | 0666);
  mutex = shmat(shmid, NULL, 0);
  sem_wait(mutex); 
  // wait until file is created

  FILE* fp = fopen("list.txt", "r");
  int evens = 0, odds = 0, n;
  while (!feof(fp)) {
    fscanf(fp, "%d ", &n);
    if (n % 2 == 0)
       evens++;
    else
       odds++;
  }
  printf("File has %d even and %d odd numbers.\n", evens, odds);
  fclose(fp);

  shmdt(mutex);
  shmctl(shmid, IPC_RMID, 0);
  return 0;
}
