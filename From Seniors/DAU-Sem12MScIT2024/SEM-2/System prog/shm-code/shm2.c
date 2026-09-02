#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>

int main() {
  int shmid; // shared memory id
  char *shmptr; // pointer to shared memory

  shmid = shmget((key_t) 1235, sizeof(char) * 50, 0666 | IPC_CREAT);
  shmptr = shmat(shmid, NULL, 0);

  printf("Enter a message: ");
  scanf("%s", shmptr);
 
  shmdt(shmptr);

  return 0;
}
