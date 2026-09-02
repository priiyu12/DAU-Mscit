#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int alarmFlag = 0;	 /* Global alarm flag */
void alarmHandler(); /* Forward declaration of alarm handler */
void (*oldhandler)();
int main(void)
{
	alarm(3);									/* Schedule an alarm signal in three seconds */
	oldhandler = signal(SIGALRM, alarmHandler); /* Install signal handler */
	printf("Looping \n");
	while (!alarmFlag) /* Loop until flag set */
	{
		pause(); /* Wait for a signal */
	}
	printf("Loop ends due to alarm signal \n");
}

void alarmHandler()
{
	printf("An alarm clock signal was received \n");
	// alarmFlag=1;

	// Set Default Handler for SIGALRM
	signal(SIGALRM, oldhandler);
	// Set another alam so default handler is executed
	alarm(3);
}