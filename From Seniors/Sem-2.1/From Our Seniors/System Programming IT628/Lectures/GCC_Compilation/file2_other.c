#include <stdio.h>

int true_global=10;
void f1()
{
	true_global = 15;
	printf("This message is from function in seperate file\n");
	printf("true_global(f1) %d\n", true_global);
}