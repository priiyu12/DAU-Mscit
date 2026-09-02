#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "USAGE: stat_example.out file_or_dir_with_path\n");
		exit(1);
	}

	struct stat st;
	stat(argv[1], &st);
	printf("st_mode value for %s is %x\n", argv[1], st.st_mode);

	printf("Number of links for %s with inode %d is %d\n", argv[1], st.st_ino, st.st_nlink);
}