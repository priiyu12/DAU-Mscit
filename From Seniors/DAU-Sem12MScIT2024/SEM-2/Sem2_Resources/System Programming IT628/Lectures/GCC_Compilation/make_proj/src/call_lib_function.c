#include <stdio.h>

double add(double, double);
double sub(double, double);

int main(int argc, char *argv[])
{
	double x=5, y=20;
	printf("%f + %f = %f\n", x, y, add(x, y));
	printf("%f - %f = %f\n", y, x, sub(x, y));
}