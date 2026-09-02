#include <stdio.h>
#include <stdlib.h>
void getenv_fn()
{
	printf("SHELL = %s\n", getenv("SHELL"));
	printf("HOME = %s\n", getenv("HOME"));
}

void setenv_fn()
{
	setenv("COURSE", "Systems Programming", 1);
	printf("COURSE = %s\n", getenv("COURSE"));
}

int main()
{
	getenv_fn();
	setenv_fn();
}