#include <stdio.h>

extern int true_global;
extern void f1();
//#include "myheader.h"
int main()
{
	true_global = 20;
	printf("Calling external function\n");
	printf("true_global(main-1) %d\n", true_global);
	f1();
	printf("true_global(main-2) %d\n", true_global);
}