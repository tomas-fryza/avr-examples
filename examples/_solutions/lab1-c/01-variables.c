#include <stdio.h>    // Standard C input/output library for `printf`
#include <stdint.h>   // Standard C integer library for `int8_t, uint8_t`

int main(void)        // Main function with no input parameters
{                     // Beginning of function body
    // Definition of two local variables
    uint8_t a = 200;
    int8_t b = 200;   // [!] Signed 8-bit variable can not store 200

    // Print formated strings to the Terminal
    printf("int8 value is %d\n", a);  // Integer `a` will be printed instead of `%d`
    printf("uint8 value is %d\n", b); // Formatting char. `\n` inserts a new line

    printf("Size of int16_t: %ld Bytes\n", sizeof(int16_t));
    printf("int16_t range: %d to %d\n", INT16_MIN, INT16_MAX);

    return 0;         // Return value of main function
}                     // End of function body
