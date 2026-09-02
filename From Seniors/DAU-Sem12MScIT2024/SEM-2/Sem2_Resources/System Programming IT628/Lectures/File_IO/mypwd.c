#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

ino_t get_inode(char *fname)
// returns inode number for the file
{
	struct stat info;
	if ( stat(fname, &info) == -1 ){
		fprintf(stderr, "Cannot stat!");
		exit(1);
	}
	return info.st_ino;
}

void inum_to_name(ino_t inode_to_find, char *namebuf, int buflen)
/*
*! looks through current directory for a file with this inode
*! number and copies its name into namebuf
*/
{
	DIR *dir_ptr; /* the directory */
	struct dirent *direntp; /* each entry! */
	dir_ptr = opendir( "." );
	if ( dir_ptr == NULL ){
		fprintf(stderr, "cannot open a directory\n");
		exit(1);
	}
	//search directory for a file with specified inum

	while ( ( direntp = readdir(dir_ptr) ) != NULL ){
		if (direntp->d_ino == inode_to_find)
		{
			printf("%lu, %s\n", direntp->d_ino, direntp->d_name);
			strncpy( namebuf, direntp->d_name, buflen);
			namebuf[buflen-1] = '\0';
			closedir( dir_ptr );
			return;
		}
	}
	fprintf(stderr, "error looking for inum %lu\n", inode_to_find);
	exit(1);
}

void printpathto( ino_t this_inode )
// prints path leading down to an object with this inode
{
	ino_t my_inode;
	char its_name[BUFSIZ];
	if (get_inode("..") != this_inode)
	{
		chdir(".."); /* up one dir! */
		inum_to_name(this_inode, its_name, BUFSIZ); /* get its name! */
		my_inode = get_inode(".");
		printpathto(my_inode);
		printf("/%s", its_name);
	}
}


// implement pwd
int main()
{
	printpathto(get_inode("."));
	putchar('\n'); /* then add newline!*/
	return 0;
}

