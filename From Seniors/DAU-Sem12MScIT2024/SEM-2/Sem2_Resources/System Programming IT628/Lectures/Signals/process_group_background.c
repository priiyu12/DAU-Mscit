#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void (*oldHandler)();
void newHandler() 
{
	printf("SIGTTIN signal received \n");
	signal(SIGTTIN, oldHandler);
}

int main(void)
{
	oldHandler = signal(SIGTTIN, newHandler); 
	printf("Run in background then try scanf to generate SIGTTIN signal\n");
	int i;
	scanf("%d", &i);
}

