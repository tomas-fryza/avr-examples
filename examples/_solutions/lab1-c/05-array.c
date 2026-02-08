#include <stdio.h>   // Standard I/O library for 'printf'
#include <stdint.h>  // Standard C integer library
#define SIZE 5       // Define the number of elements

int main(void)
{
    // Declare and initialize a zero integer array
    uint8_t values[SIZE] = {0};  // {0, 0, 0, 0, 0}

    // Modify elements of the array
    for (uint8_t i = 0; i < SIZE; i++)
    {
        values[i] = i*i + 1;  // {1, 2, 5, 10, 17}
    }

    // Print the modified array
    printf("Modified array:\n");
    for (uint8_t i = 0; i < SIZE; i++)
    {
        printf("[%d] %d\n", i, values[i]);
    }

    return 0;
}
