/* 
 * Stopwatch on Liquid Crystal Display (LCD).
 * (c) 2017-2025 Tomas Fryza, MIT license
 *
 * Developed using PlatformIO and Atmel AVR platform.
 * Tested on Arduino Uno board and ATmega328P, 16 MHz.
 */

// -- Includes ---------------------------------------------
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions


// -- Global variables -------------------------------------
volatile uint8_t flag = 0;

// Stopwatch values
// Declaration of "stopwatch" variable with structure "Stopwatch_structure"
struct Stopwatch_structure {
    uint8_t tenths;  // Tenths of a second
    uint8_t secs;    // Seconds
    uint8_t mins;    // Minutes
} stopwatch;


// -- Function definitions ---------------------------------
/*
 * Function: Main function where the program execution begins
 * Purpose:  Update stopwatch value on LCD screen when 8-bit Timer/Counter2
 *           overflows.
 * Returns:  none
 */
int main(void)
{
    char lcd_msg[5];  // String for converted numbers by itoa()

    // Initialize display
    lcd_init(LCD_DISP_ON_CURSOR_BLINK);

    // Put string(s) on LCD screen
    lcd_gotoxy(6, 0);  // Move to 7th column and 1st line
    lcd_puts("LCD Test");
    lcd_putc('!');

    // Set backlight
    // WRITE YOUR CODE HERE


    // Custom character(s)
    // WRITE YOUR CODE HERE


    // Configuration of 8-bit Timer/Counter2 for Stopwatch update
    // Set the overflow prescaler to 16 ms and enable interrupt
    // WRITE YOUR CODE HERE


    // Enable global interrupts
    // sei();

    // Infinite loop
    while (1) {
        if (flag == 1) {
            // Display "00:00.tenths"
            itoa(stopwatch.tenths, lcd_msg, 10);  // Convert decimal value to string
            lcd_gotoxy(7, 0);
            lcd_puts(lcd_msg);

            flag = 0;
        }
    }

    // Will never reach this
    return 0;
}


// -- Interrupt service routines ---------------------------
/*
 * Function: Timer/Counter2 overflow interrupt
 * Purpose:  Update the stopwatch on LCD screen every sixth overflow,
 *           ie approximately every 100 ms (6 x 16 ms = 100 ms).
 */
ISR(TIMER2_OVF_vect)
{
    static uint8_t n_ovfs = 0;

    n_ovfs++;

    // Do this every 6 x 16 ms = 100 ms
    if (n_ovfs >= 6)
    {
        n_ovfs = 0;
        stopwatch.tenths++;
        // Count tenth of seconds 0, 1, ..., 9, 0, 1, ...
        // WRITE YOUR CODE HERE


        flag = 1;
    }
    // Else do nothing and exit the ISR
}
