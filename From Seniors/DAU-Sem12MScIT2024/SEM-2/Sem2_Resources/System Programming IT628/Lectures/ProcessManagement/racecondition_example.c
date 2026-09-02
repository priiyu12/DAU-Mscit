#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

static void charatatime(char *str)
{
	char *ptr;
	int c;
	setbuf(stdout, NULL);
	for (ptr=str;c=*ptr++;) putc(c,stdout);
}

int main(void)
{
	pid_t pid;
	if ((pid = fork())<0) printf("fork error!\n");
	else if (pid ==0) charatatime("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\n");
	else charatatime("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz\n");
}
