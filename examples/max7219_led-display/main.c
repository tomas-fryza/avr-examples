/***********************************************************************
 * Title: Led matrix display with MAX7219 via SPI
 * Author: Tomas Fryza, Brno University of Technology
 * Date: December 2017
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>         /* For itoa function */
#include "spi.h"
#include "uart.h"


/*
 *  Constants and macros
 */
 #define UART_BAUD_RATE  9600
 #define MAX7219_MODE_DECODE     0x09
 #define MAX7219_MODE_INTENSITY  0x0a
 #define MAX7219_MODE_SCAN_LIMIT 0x0b
 #define MAX7219_MODE_POWER      0x0c
 #define MAX7219_MODE_TEST       0x0f


/*
 *  Function prototypes
 */
void setup(void);
void set_state(void);
void max7219_init(void);
void max7219_write(uint8_t high_byte, uint8_t low_byte);
void max7219_clear(void);
void update_display(void);
void set_pixel(uint8_t r, uint8_t c, uint8_t value);


/*
 *  Global variables
 */
typedef enum {
    STATE_IDLE = 1,
    STATE_SPI_WRITE
} state_t;

state_t state = STATE_IDLE;
uint8_t display[8] = {0};


/***********************************************************************
 * Main function
 */
int main(void)
{
    setup();
    sei();
    uart_puts("\n\r");
    uart_puts("---SPI LED display with MAX7219 driver---");

    while (1) {
    }

    return 0;
}


/***********************************************************************
 * Setup all peripherals
 * param None
 * return None
 */
void setup(void)
{
    /* Update FSM state every 262 ms */
    TCCR1B |= _BV(CS11) | _BV(CS10);  /* Clock prescaler 64 */
    TIMSK1 |= _BV(TOIE1);   /* Overflow interrupt enable; ATmega328P */
//    TIMSK |= _BV(TOIE1);   /* Overflow interrupt enable; ATmega16 */

    /*
     * Initialize UART
     * Frame format: asynchronous, 8-bit data, no parity, 1-bit stop
     */
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    /* Initialize SPI */
    spi_master_init();

    /* Initialize MAX7219 display */
    max7219_init();
}


/***********************************************************************
 * Timer1 overflows every 262 ms (fcpu=16e6, 16-bit, N=64)
 * param None
 * return None
 */
ISR(TIMER1_OVF_vect)
{
    set_state();
}


/***********************************************************************
 * MAX7219 LED display state machine
 * param None
 * return None
 */
void set_state(void)
{
    char buffer[3];
    static uint8_t data = 0;

    switch (state) {
    case STATE_IDLE:
        uart_puts("\n\r\033[32mIDLE\033[0m ");
        state = STATE_SPI_WRITE;
        break;

    case STATE_SPI_WRITE:
        uart_puts("\n\r\033[32mSPI_WRITE\033[0m ");
//        set_pixel(data / 8, data % 8, 2);
        set_pixel(7, 1, 2);
	    update_display();
        itoa(data++, buffer, 16);
        uart_puts(buffer);
        if (data >= 64) {
            data = 0;
        }
        state = STATE_SPI_WRITE;
        break;

    default:
        uart_puts("\n\r\033[31mDEFAULT\033[0m ");
        state = STATE_IDLE;
    }
}


/***********************************************************************
 * Performs initialization of MAX7219 device
 * param None
 * return None
 */
void max7219_init(void)
{
    /* Decode mode: none */
    max7219_write(MAX7219_MODE_DECODE, 0);

    /* Intensity: 0 (0-15) */
    max7219_write(MAX7219_MODE_INTENSITY, 0);

    /* Scan limit: All "digits" (rows) on */
    max7219_write(MAX7219_MODE_SCAN_LIMIT, 7);

    /* Shutdown register: Display on */
    max7219_write(MAX7219_MODE_POWER, 1);

    /* Display test: off */
    max7219_write(MAX7219_MODE_TEST, 0);

    /* Clear display */
    max7219_clear();
}


/***********************************************************************
 * Sends two-byte data to MAX7219 device via SPI
 * param high_byte
 * param low_byte
 * return None
 */
void max7219_write(uint8_t high_byte, uint8_t low_byte)
{
    /* Set SPI slave select pin to low */
    SPI_SS_LOW();

    /* Send two-byte data to MAX7219 device */
    spi_send(high_byte);
    spi_send(low_byte);

    /* Set SPI slave select pin to high */
    SPI_SS_HIGH();
 }


/***********************************************************************
 * Clears display
 * param None
 * return None
 */
 void max7219_clear(void)
 {
     uint8_t i;

     for (i = 0; i < 8; i++) {
 	       max7219_write(i+1, 0);
     }
 }


/***********************************************************************
 * Update display
 * param None
 * return None
 */
void update_display(void)
{
     uint8_t i;

     for (i = 0; i < 8; i++) {
         max7219_write(i+1, display[i]);
     }
}


/***********************************************************************
 * Set one pixel value
 * param r - Row
 * param c - Column
 * param value - 0: Clear pixel; 1: Set pixel; Other: toggle pixel
 * return None
 *     (0, 0)           (0, 7)
 *         o o o o o o o o
 *  +---+  o o o o o o o o
 *  | M |  o o o o o o o o
 *  | A |  o o o o o o o o
 *  | X |  o o o o o o o o
 *  |   |  o o o o o o o o
 *  +---+  o o o o o o o o
 *         o o o o o o o o
 *     (7, 0)           (7, 7)
 */
void set_pixel(uint8_t r, uint8_t c, uint8_t value)
{
    switch (value) {
    case 0:     /* Clear pixel */
	   display[r] &= ~(0x80 >> c);
       break;

    case 1:     /* Set pixel */
	   display[r] |= (0x80 >> c);
       break;

    default:    /* XOR pixel */
	   display[r] ^= (0x80 >> c);
	   break;
    }
}
