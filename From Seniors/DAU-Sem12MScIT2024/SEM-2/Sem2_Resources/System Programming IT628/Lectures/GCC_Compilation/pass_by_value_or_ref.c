#include <stdio.h>

void pass_by_ref(int *a) //pass by ref
{
	*a = 10;
}

void pass_by_val(int a)//pass by value
{
	a = 10;
}

int main(int argc, char *argv[])
{
	int i= 20;
	printf("i before pass_by_val %d\n", i);
	pass_by_val(i);// pass by value
	printf("i after pass_by_val %d\n", i);// what will be printed?
	
	printf("i before pass_by_ref %d\n", i);
	pass_by_ref(&i); // pass by reference
	printf("i after pass_by_ref %d\n", i);// what will be printed?
}

