#include <stdio.h>  // Added
#include "utils.h"  // Added

#define N 20

int main()
{
    unsigned int result = square(N);
    printf("Square of %d is %u\n", N, result);

    printf("Fibonacci sequence (%d):\n", N);
    fibonacci(N);

    return 0;
}
