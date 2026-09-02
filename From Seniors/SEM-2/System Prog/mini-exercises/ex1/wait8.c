#include "csapp.h"

/* pre-condition: cpid > 0 */
/* number of times called: 5 */
pid_t my_waitpid(pid_t cpid, int *status, int ignored)
{
}

int main() 
{
    int stat, i;
    pid_t pid[5];

    /* Parent creates N children */
    for (i = 0; i < 5; i++)                       
	if ((pid[i] = Fork()) == 0)  {
            sleep(5-i); 
	    exit(100+i);                          
        }

    /* Parent reaps N children in a particular order */
    for (i=0; i<5; i++) {
        pid_t cpid = waitpid(pid[i], &stat, 0);  
        /* pid_t cpid = wait(&stat); */
        if (WIFEXITED(stat))
	    printf("child %d terminated normally with exit status=%d\n",
		   cpid, WEXITSTATUS(stat));    
    }
}
