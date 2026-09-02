#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

int fd, ppid, cpid, status, end_of_file=0;

int critical_section()
{
	char buf, line_buf[255];
	int bytes_read, indx=0;
	while ((bytes_read = read(fd, &buf, 1)) != -1)
	{
		if (bytes_read == 0)
		{
			return 1;	// indicates end of file
		}
		else
		{
			write(1,&buf,1);
			line_buf[indx++]=buf;
			if (buf == '\n')
			{
				line_buf[indx++]='\0';
				printf("pid %d --> %s\n", getpid(), line_buf);
				indx=0;
				return 0;	// each process either parent or child prints only 1 line at a time
			}
		}
	
	}
}

void sigusr_handler(int signum)
{
	int i;
	if (signum == SIGUSR1)	// if SIGUSR1 is received loop infinitely until SIGUSR2 is received
	{
		printf("received SIGUSR1 in pid %d\n", getpid());
		sleep(1000);
	}
	else if (signum == SIGUSR2)
	{
		printf("received SIGUSR2 in pid %d\n", getpid());
		if (getpid() == ppid)
			kill(cpid, SIGUSR1);	// send SIGUSR1 to child so that it waits
		else
			kill(ppid, SIGUSR1);	// send SIGUSR1 to parent so that it waits
		sleep(1);
		int ret = critical_section();
		sleep(1);
		if (ret == 1)
		{
			if (getpid() == ppid)
				kill(cpid, SIGINT);	// send SIGINT to child to terminate
			else
				kill(ppid, SIGINT);	// send SIGINT to paent to terminate
		}
		else
		{
			if (getpid() == ppid)
				kill(cpid, SIGUSR2);	// send SIGUSR1 to child so that it continues
			else
				kill(ppid, SIGUSR2);	// send SIGUSR1 to parent so that it continues
		}
	}
}

int main(void)
{
	if ((fd = open("merged.txt", O_RDONLY)) == -1)
	{
		printf("Error opening file\n");
		exit(-1);
	}

	if (signal(SIGUSR1, sigusr_handler) == SIG_ERR)	// both parent and child register for SIGUSR1 handler
	{
		printf("Unable to crete handler for SIGUSR1\n");
		exit(-1);
	}

	if (signal(SIGUSR2, sigusr_handler) == SIG_ERR)	// both parent and child register for SIGUSR2 handler
	{
		printf("Unable to crete handler for SIGUSR2\n");
		exit(-1);
	}


	printf("I am main process %d\n", getpid());
	ppid = getpid();
	cpid = fork();	// create child process
	if (cpid != 0)	// parent
	{

		printf("I am parent process %d\n", ppid);
		kill(cpid, SIGUSR1);	// send SIGUSR1 to child so that it waits
		critical_section();
		kill(cpid, SIGUSR2);	// send SIGUSR1 to child so that it continues
		wait(&status);		// wait for child to exit(), not to create zombie
	}
	else		// child
	{
		printf("I am child process %d\n", getpid());
		sleep(10);
		while(1);
	}
}
