#include <stdio.h>
#include <stdlib.h>

float add(float a, float b)
{
	return a+b;
}

float subtract(float a, float b)
{
	return a-b;
}

float multiply(float a, float b)
{
	return a*b;
}

float divide(float a, float b)
{
	if (b != 0.0)
		return a/b;
	else
		return 0.0;
}

float stop(float a, float b)
{
	exit(0);
}

int main(int argc, char* argv[])
{
	float (*fns[5])(float a, float b) = {add, subtract, multiply, divide, stop};
	char ops[4]={'+', '-', '*', '/'};
	float x, y;
	int i, ch;
	while (1)
	{
		printf("1 for Addition\n");
		printf("2 for Subtraction\n");
		printf("3 for Multiplication\n");
		printf("4 for Division\n");
		printf("5 for Exit\n");
		printf("Enter operation to perform: ");
		scanf("%d", &ch);
		if (ch<1 || ch>5)
		{
			printf("%d invalid option\n", ch);
		}
		else
		{
			printf("Enter two float values seperated by space:");
			scanf("%f %f", &x, &y);
			float result = fns[ch-1](x, y);
			printf("%f %c %f = %f\n", x, ops[i], y, result);

		}
	}
	
	
}