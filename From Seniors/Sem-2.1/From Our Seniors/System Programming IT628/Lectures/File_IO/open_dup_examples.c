#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char buf[] = "abcdefgh";

	int fd11 = open("open_file.txt", O_RDWR);
	int fd12 = open("open_file.txt", O_RDWR);
	int fd21 = open("dup_file.txt", O_RDWR);
	int fd22 = dup(fd21);
	
	write(fd11, buf, 1);
	write(fd21, buf, 1);
	
	getchar();

	write(fd12, &buf[1], 1);
	write(fd22, &buf[1], 1);
	
	close(fd11);
	close(fd12);
	close(fd21);
	close(fd22);	
}