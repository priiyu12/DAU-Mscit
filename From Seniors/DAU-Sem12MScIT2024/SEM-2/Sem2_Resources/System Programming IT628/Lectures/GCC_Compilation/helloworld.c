#include <stdio.h>
#include <math.h>
#include "helloworld.h"


#ifdef intel
	char model[6]="Intel";
#else
	char model[6]="other";
#endif

int main(void)
{
	printf("Model: %s", model);
	int a=2, b=5, c;
	c = pow(a, b);
	printf("power %d", c);
}
