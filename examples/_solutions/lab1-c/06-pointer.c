#include <stdio.h>   // Standard I/O library for 'printf'
#include <stdint.h>  // Standard C integer library
#define SIZE 10      // Define the number of elements

int main(void)
{
    // Declare and initialize a zero integer array
    uint8_t values[SIZE] = {0};  //
    // Point `pValues` to the start of the 'values' array
    uint8_t *pValues = values;   // *pValues = &values[0]

    // Modify elements of the array
    for (uint8_t i = 0; i < SIZE; i++)
    {
        *(pValues + i) = i*i + 1;// {1, 2, 5, 10, 17, ...}
    }

    printf("Modified array:\n"); // Print modified array
    for (uint8_t i = 0; i < SIZE; i++)
    {
        printf("[%d] %p: %d\n", i, pValues, *pValues++);
    }

    return 0;
}
