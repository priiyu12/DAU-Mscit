//Print “hello world” from the program without use any printf or cout function. 
// C program to illustrate
// I/O system Calls
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
 
int main (void)
{
    int fd[2], rdcnt;
    char buf1[12] = "hello world";
    char buf2[12];
 
    // assume foobar.txt is already created
    fd[0] = open("file.txt", O_RDWR);        
    fd[1] = open("file.txt", O_RDWR);
     
    write(fd[0], buf1, strlen(buf1));
	while ((rdcnt = read(fd[1], buf2, 12)))
	{
		write(1, buf2, rdcnt);
		if (rdcnt < 12)
			break;
	}
    
 
    close(fd[0]);
    close(fd[1]);
 
    return 0;
}