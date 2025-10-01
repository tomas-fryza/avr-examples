/*
 * Blink a LED using delay.
 * (c) 2018-2025 Tomas Fryza, MIT license
 *
 * Developed using PlatformIO and Atmel AVR plafform.
 * Tested on Arduino Uno board and ATmega328P, 16 MHz.
 */

// -- Defines ----------------------------------------------
#define LED PB5  // On-board LED pin


// -- Includes ---------------------------------------------
#include <avr/io.h>      // AVR device-specific IO definitions
#include <util/delay.h>  // Functions for busy-wait delay loops


// -- Function definitions ---------------------------------
/*
 * Function: Main function where the program execution begins
 * Purpose:  Toggle LED using delay.
 * Returns:  none
 */
int main(void)
{
    // Set output pin in Data Direction Register
    DDRB = DDRB | (1 << LED);
    // Set pin LOW in Data Register (LED off)
    PORTB = PORTB & ~(1 << LED);

    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(500);
        // Invert LED in Data Register
        PORTB = PORTB ^ (1 << LED);
    }

    // Will never reach this
    return 0;
}
