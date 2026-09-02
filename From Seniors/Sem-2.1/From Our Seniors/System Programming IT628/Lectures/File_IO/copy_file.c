#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

FILE *srcfd, *dstfd;
int open_files(char *srcfile, char *dstfile)
{
		if ((srcfd = fopen(srcfile, "r")) == NULL)
	{
		if (errno == ENOENT)
		{
			fprintf(stderr, "%s path or file does not exist", srcfile);
			return(2);			
		}
		else
		{
			fprintf(stderr, "%s cannot be opened in read mode", srcfile);
			return(3);
		}

	}
	if ((dstfd = fopen(dstfile, "w")) == NULL)
	{
		fprintf(stderr, "%s cannot be opened in write mode", dstfile);
		return(4);
	}
	return(0);
}

void close_files()
{
	if (srcfd != NULL)
		fclose(srcfd);
	if (dstfd != NULL)
		fclose(dstfd);
}

void copy_file_charwise()
{
	int c;
	while ((c = fgetc(srcfd)) != EOF)
		fputc(c, dstfd);
}

void copy_file_linewise()
{
	char buf[1024];
	int cnt=0;
	while (feof(srcfd) == 0)
	{
		printf("%d", cnt++);
		fgets(buf, 1024, srcfd);
		fputs(buf, dstfd);
	}
}

int main(int argc, char *argv[])
{
	int ret;
	if(argc < 3)
	{
		fprintf(stdout, "Usage: copy_file sourcefile_with_path destfile_with_path");
		exit(1);
	}
	
	if ((ret = open_files(argv[1], argv[2])) != 0)
	{
		close_files();
		exit(ret);
	}
	
	//copy_file_charwise();
	copy_file_linewise();
	close_files();
	exit(0);
	
	
}