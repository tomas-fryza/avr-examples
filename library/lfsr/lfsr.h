// -- Includes ---------------------------------------------
#include <avr/io.h>         // AVR device-specific IO definitions


// -- Function prototypes ----------------------------------
// Goxygen module with assembly functions starts here
/**
 * @defgroup func_asm Assembly functions
 * @brief Function(s) written in AVR Assembly language.
 * @{
 */


/**
 * @brief  Multiply-and-Accumulate operation, ie. result = result + (a*b).
 * @param  result Current MAC value
 * @param  a Value A
 * @param  b Value B
 * @return New MAC result
 * @note   Function programmed in AVR assembly language.
 */
uint8_t multiply_accumulate_asm(uint8_t result, uint8_t a, uint8_t b);


/**
 * @brief  LFSR-based 4-bit pseudo-random generator with Fibonacci
 *         architecture. Taps are 4, 3.
 * @param  value Current value of LFSR
 * @return New value of LFSR
 * @note   Function programmed in AVR assembly language.
 */
uint8_t lfsr4_fibonacci_asm(uint8_t value);


// uint8_t lfsr8_fibonacci_asm(uint8_t value);


// Goxygen module with assembly functions ends here
/** @} */
