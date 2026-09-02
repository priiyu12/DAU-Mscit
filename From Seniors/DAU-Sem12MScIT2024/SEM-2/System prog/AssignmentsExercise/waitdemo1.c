#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <unistd.h>

int main() {
   pid_t cpid;
   if (vfork() == 0) {  // Use vfork() instead of fork() for better MinGW compatibility
      exit(0);          // terminate child
   } else { 
      wait(NULL);       // reaping parent
   }

   printf("Parent pid = %d \n", getpid());
   printf("Child pid = %d \n", cpid);

   while (1);          // Infinite loop
}
