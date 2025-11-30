#include <stdio.h>
#include "utils.h"

unsigned int square(unsigned char x)
{
	return (x*x);
}

int add(int a, int b)
{
	return a+b;
}

/*
 * Fibonacci sequence is a series of numbers where each number is
 * the sum of the two preceding ones.
 */
void fibonacci(unsigned char n)
{
	unsigned int a = 0, b = 1;

	printf("%d, %d", a, b);

	for (int i = 2; i < n; i++) {
		unsigned int temp = a+b;
		printf(", %u", temp);
		a = b;
		b = temp;
	}
	printf("\n");
}
