#include <stdio.h>   // Standard C input/output library
#include <stdint.h>  // Standard C integer library

int main(void)
{
    uint8_t val = 0x8f;
    uint8_t temp;

    for (uint8_t i=0; i<8; i++)
    {
        temp = val & 0b00000001;   // Bitwise AND with LSB
        if (temp != 0)
        {
            printf("%d is odd value\n", val);
        }
        else
        {
            printf("%d is even value\n", val);
        }
        val >>= 1;   // val = val >> 1
    }

    return 0;        // Return value of main function
}
