#include <stdio.h>    // Standard C input/output library
#include <stdint.h>   // Standard C integer types library
#define N_LINES 5     // Define `N_LINES` to substitute with `5`

int main(void)        // Main function
{
    // Outer loop controls the number of lines (i.e., rows of stars)
    for (uint8_t i = 0; i < N_LINES; i++)
    {
        // Inner loop controls the number of stars printed per line
        // It prints one more star with each new line
        for (uint8_t j = 0; j <= i; j++)
        {
            printf("*");  // Print a single star
        }
        printf("\n");     // Print a newline character on the current line
    }

    return 0;         // Return value of main function
}                     // End of function body
