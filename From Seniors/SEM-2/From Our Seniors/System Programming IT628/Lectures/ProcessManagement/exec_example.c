#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("%s", argv[0]);
    printf("Im process %d and Im about to exec an ls -l \n", getpid() );
    execl( "/bin/ls", "/bin/ls", "-l", NULL ); /* Execute ls */
    printf("This line should never be executed \n");
}
