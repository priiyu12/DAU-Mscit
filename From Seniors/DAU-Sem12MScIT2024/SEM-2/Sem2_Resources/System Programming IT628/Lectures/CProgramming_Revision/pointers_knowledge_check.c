#include <stdio.h>
main()
{
	int i=8, j=8;
	int *p, *p1, *p2;
	p=&i; p1=&i; p2=&j;
	
	double *d = &i;
	printf("*d: %lf\n", *d);
	
	double d1 = i;
	printf("d1: %lf\n", d1);
	
	double d2 = 10000000000000.1234;
	i = d2;
	int i1 = (int)d2;
	printf("i: %d, i1: %d\n", i, i1);
	
	if (sizeof(p) == sizeof(d))
		printf("p and d have same size\n");
	else
		printf("p and d have diff size\n");

	if (sizeof(*p) == sizeof(*d))
		printf("*p and *d have same size\n");
	else
		printf("*p and *d have diff size\n");

	if (p1 == p2)
		printf("p1 and p2 are same\n");
	else
		printf("p1 and p2 are diff\n");

	if (*p1 == *p2)
		printf("*p1 and *p2 are same\n");
	else
		printf("*p1 and *p2 are diff\n");

	if (p == p1)
		printf("p and p1 are same\n");
	else
		printf("p and p1 are diff\n");
	
	int k = 8; int *p3;
	p3 = &k; *p3 = 12;
	printf("k: %d\n", k);


}