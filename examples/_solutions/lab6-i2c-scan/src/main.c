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
#include <util/delay.h>     // !!! Just for the simulation in SimulIDE !!!


// -- Function definitions ---------------------------------
/*
 * Function: Main function where the program execution begins
 * Purpose:  Call function to test all I2C (TWI) combinations and send
 *           detected devices to UART.
 * Returns:  none
 * 
 * Some known devices:
 *   - 0x3c - OLED display
 *   - 0x57 - EEPROM
 *   - 0x5c - Temp+Humid
 *   - 0x68 - RTC
 *   - 0x68 - GY521
 *   - 0x76 - BME280
 */
int main(void)
{
    char uart_msg[10];
    uint8_t n_devices = 0;

    twi_init();

    // Initialize USART to asynchronous, 8-N-1, 115200 Bd
    uart_init(UART_BAUD_SELECT(115200, F_CPU));

    sei();  // Needed for UART

    uart_puts("Scanning I2C... ");
    for (uint8_t sla = 8; sla < 120; sla++) {
        if (twi_test_address(sla) == 0) {  // If ACK from Slave
            sprintf(uart_msg, "\r\n0x%02x", sla);
            uart_puts(uart_msg);
            n_devices++;
        }
        // _delay_ms(1);  // !!! Just for the simulation !!!
    }
    sprintf(uart_msg, "\r\n%u device(s) detected\r\n", n_devices);
    uart_puts(uart_msg);

    while (1) {
        // Infinite empty loop
    }

    // Will never reach this
    return 0;
}
