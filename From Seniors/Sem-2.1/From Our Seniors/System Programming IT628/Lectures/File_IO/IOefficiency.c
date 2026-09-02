#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

copy_using_unbuffered_io()
{
	// copy using unbuffered IO
	char ch;
	while(read(STDIN_FILENO, &ch, 1) > 0)
		write(STDOUT_FILENO, &ch, 1);
}

copy_using_buffered_io_charattime()
{
	int ch;
	while((ch = fgetc(stdin)) != EOF)
		fputc(ch, stdout);
}

copy_using_buffered_io_lineattime()
{
	int bufsize = 1024*1024*5;
	char buf[bufsize];
	while(fgets(buf,bufsize,stdin) != NULL)
		fputs(buf, stdout);
}
int main()
{
	//copy_using_unbuffered_io();
	//copy_using_buffered_io_charattime();
	copy_using_buffered_io_lineattime();
}

