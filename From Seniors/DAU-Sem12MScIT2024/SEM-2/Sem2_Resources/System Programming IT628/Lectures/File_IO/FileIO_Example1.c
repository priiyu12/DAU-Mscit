#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char buf1[] = "abcdefghij";
	char buf2[] = "klmnopqrst";
	int fd;
	
	if ( (fd = open("file1.txt", O_RDWR | O_CREAT, 0755)) < 0)
		{ printf("open error!"); exit(-1);}
	
	if ( write(fd, buf1, 10) != 10)
		{ printf("buf1 write error!"); exit(-1);}
	
	if ( lseek(fd, 40, SEEK_SET) == -1)
		{ printf("buf1 seek error!"); exit(-1);}
	
	if ( write(fd, buf2, 10) != 10)
		{ printf("buf2 write error!"); exit(-1);}
	
	close(fd); 
	exit (0);
}