#include <stdio.h>   // Standard I/O library for 'printf'
#include <stdint.h>  // Standard C integer library

// Function declaration
uint16_t mul(uint8_t, uint8_t);

// Main function
int main(void)
{
    // Function call
    uint16_t product = mul(200, 120);

    // Display the result
    printf("Product: %d\n", product);

    return 0;
}

// Function definition
uint16_t mul(uint8_t x, uint8_t y)
{
    return (x * y);
}
