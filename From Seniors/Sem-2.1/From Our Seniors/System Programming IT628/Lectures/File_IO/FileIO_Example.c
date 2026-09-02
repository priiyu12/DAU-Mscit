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
	
	if ( (fd = open("file.txt", O_RDWR, 0755)) < 0)
		{ printf("open error!"); exit(-1);}
	
	if ( read(fd, buf2, 2) != 2)
		{ printf("buf1 write error!"); exit(-1);}

	if ( write(fd, buf1, 10) != 10)
		{ printf("buf1 write error!"); exit(-1);}

	close(fd); 
	exit (0);

}