/*
 * The I2C (TWI) bus scanner tests all addresses and detects devices
 * that are connected to the SDA and SCL signals.
 * (c) 2023-2025 Tomas Fryza, MIT license
 *
 * Developed using PlatformIO and Atmel AVR platform.
 * Tested on Arduino Uno board and ATmega328P, 16 MHz.
 */

// -- Includes ---------------------------------------------
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <twi.h>            // I2C/TWI library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdio.h>          // C library. Needed for `sprintf`
#include "timer.h"


// -- Function definitions ---------------------------------
/*
 * Function: Main function where the program execution begins
 * Purpose:  Call function to test all I2C (TWI) combinations
 *           and send detected devices to UART.
 * Returns:  none
 */
int main(void)
{
    char uart_msg[10];

    // Initialize USART to asynchronous, 8-N-1, 115200 Bd
    // NOTE: Add `monitor_speed = 115200` to `platformio.ini`
    uart_init(UART_BAUD_SELECT(115200, F_CPU));

    sei();  // Needed for UART

    // I2C Scanner
    uart_puts("Scanning I2C... ");
    twi_init();

    for (uint8_t sla = 0; sla < 128; sla++) {
        if (twi_test_address(sla) == 0) {  // If ACK from Slave
            sprintf(uart_msg, "0x%x ", sla);
            uart_puts(uart_msg);
        }
    }
    uart_puts(" Done\r\n");

    // Set Timer 1
    // WRITE YOUR CODE HERE

    // Update "minutes" and "hours" in RTC
    // WRITE YOUR CODE HERE

    // Test OLED display
    // WRITE YOUR CODE HERE

    while (1) {
    }

    return 0;
}
