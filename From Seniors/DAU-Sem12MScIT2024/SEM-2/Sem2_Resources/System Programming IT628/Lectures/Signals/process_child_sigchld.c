#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	printf("child pid=%d got %s %s\n", getpid(), argv[1], argv[2]);
	int num1=atoi(argv[1]), num2=atoi(argv[2]);
	sleep(10);
	int sum=num1+num2;
	printf("From Child: %d + %d = %d\n", num1, num2, sum);
	exit(sum);
}