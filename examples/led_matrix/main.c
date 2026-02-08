/***********************************************************************
 * Title: Usage of M23088C LED display (8x8 LED matrix)
 * Author: Tomas Fryza, Brno University of Technology
 * Date: November 2017
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"


/*
 *  Constants and macros
 */
#define GREEN PORTA
#define RED PORTC
#define LINE PORTB
#define UART_BAUD_RATE 9600


/*
 *  Function prototypes
 */
void setup(void);


/***********************************************************************
 * Main function
 */
int main(void)
{
    setup();
    sei();


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
    /* Green LEDs: PORTA */
    DDRA = 0xff;
    GREEN = 255;    /* Turn off */

    /* Red LEDs: PORTC */
    DDRC = 0xff;
    RED = 255;      /* Turn off */

    /* Line select: PORTB2:0 */
    DDRB = 0x07;
    LINE = 0b111;

    /*
     * Initialize UART
     * Frame format: asynchronous, 8-bit data, no parity, 1-bit stop
     */
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    /* Overflow every 262 ms */
    TCCR1B |= _BV(CS11) | _BV(CS10);    /* Clock prescaler 64 */
    TIMSK |= _BV(TOIE1);        /* Overflow interrupt enable */
}


/***********************************************************************
 * Timer1 overflows every 262 ms (fcpu=16e6, 16-bit, N=64)
 * param None
 * return None
 */
ISR(TIMER1_OVF_vect)
{
    uart_puts("\n\rtimer1 OVF");

    /* Green */
//    GREEN = 0;      /* Turn on */
//    RED = 255;      /* Turn off */
    GREEN = 0b11000000;      /* Turn on */
    RED = 0b00111111;      /* Turn off */

    /* Red */
//    GREEN = 255;    /* Turn off */
//    RED = 0;        /* Turn on */

    /* Orange */
//    GREEN = 0;      /* Turn on */
//    RED = 0;        /* Turn on */
//    LINE++;
}
