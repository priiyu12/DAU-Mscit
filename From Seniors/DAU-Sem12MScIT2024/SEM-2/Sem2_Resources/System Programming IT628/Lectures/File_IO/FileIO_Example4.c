#include <stdio.h>
int main()
{
	int bufsize = 1024;
	char buf[bufsize];
	while (fgets(buf, bufsize, stdin) != NULL)
	fputs(buf, stdout);
}
