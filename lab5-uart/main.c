/*
 * Use USART unit and transmit data between ATmega328P and computer.
 * (c) 2018-2025 Tomas Fryza, MIT license
 *
 * Developed using PlatformIO and Atmel AVR platform.
 * Tested on Arduino Uno board and ATmega328P, 16 MHz.
 */

// -- Includes ---------------------------------------------
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdlib.h>         // C library. Needed for number conversions


// -- Function definitions ---------------------------------
/*
 * Function: Main function where the program execution begins
 * Purpose:  Use Timer/Counter1 and transmit UART data.
 * Returns:  none
 */
int main(void)
{
    // Initialize USART to asynchronous, 8-N-1, 9600 Bd
    uart_init(UART_BAUD_SELECT(9600, F_CPU));

    // Configure 16-bit Timer/Counter1 to transmit UART data
    // Set prescaler to 1 sec and enable overflow interrupt

    // WRITE YOUR CODE HERE

    // Interrupts must be enabled, bacause of `uart_puts()`
    sei();

    // Put strings to ringbuffer for transmitting via UART
    uart_puts("\r\n");  // New line only
    uart_puts("Start using Serial monitor...\r\n");

    // Infinite loop
    while (1)
    {
    }

    // Will never reach this
    return 0;
}


// -- Interrupt service routines ---------------------------
/*
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Transmit UART data.
 */
ISR(TIMER1_OVF_vect)
{
    // WRITE YOUR CODE HERE
}
