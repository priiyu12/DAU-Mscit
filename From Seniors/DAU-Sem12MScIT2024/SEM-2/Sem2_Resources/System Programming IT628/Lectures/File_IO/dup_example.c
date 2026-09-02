#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char msg[] = "Write something to stdout but it will be redirected to a file\n";
	int fd = open("dup_example.txt", O_RDWR | O_CREAT);
	dup2( fd, 1);  /* Redirect stdout to a file*/
	write(1, msg, strlen(msg));
	close(fd);
}