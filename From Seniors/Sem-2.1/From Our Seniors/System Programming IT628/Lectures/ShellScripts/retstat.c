#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("Value of argc %d\n", argc);
	if (argc < 2)
		exit(1);
	else
		exit(0);
}
