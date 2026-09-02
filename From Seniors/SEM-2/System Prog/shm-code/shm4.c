#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <semaphore.h>

int main() {
  int shmid;
  sem_t* mutex;

  shmid = shmget((key_t) 1236, sizeof(sem_t), IPC_CREAT | 0666);
  mutex = shmat(shmid, NULL, 0);
  sem_init(mutex, 1, 0); 
  // 2nd parameter denotes this semaphore
  // will be shared between processes
  // it is initially locked (value = 0)

  int i, limit;
  printf("How many numbers do you want to generate? ");
  scanf("%d", &limit);
  FILE* fp = fopen("list.txt", "w");
  for (i = 0; i < limit; i++)
    fprintf(fp, "%d ", rand() % 100);
  fclose(fp);
  sem_post(mutex); 
  // file is ready, now let the other process
  // to do its job

  shmdt(mutex);
  return 0;
}