/***********************************************************************
 * Title: Scanning of 3x3 matrix keypad
 * Author: Tomas Fryza, Brno University of Technology
 * Date: October 2017
 */


#include <avr/io.h>
/* Defines onboard clock frequency for delay library */
#define F_CPU 16000000UL
#include <util/delay.h>


/***********************************************************************
 * Main function
 */
int main(void)
{
    uint8_t i, j;
    uint8_t set_col[3] = {      /* Array of column addresses */
        0x7f, 0xbf, 0xdf
    };
    uint8_t disp[3][3] = {      /* Array of displaying binary values */
        {1<<4, 2<<4, 3<<4},
        {4<<4, 5<<4, 6<<4},
        {7<<4, 8<<4, 9<<4},
    };

    /* Set PB7:4 to output direction */
    DDRB = 0xf0;
    /* Enable pull-up resistors for input pins */
    PORTB = 0xff;

    /* Set PD7:4 to output direction */
    DDRD = 0xf0;
    /* Turn OFF all LEDs */
    PORTD = 0b11110000;

    /* Forever loop */
    while (1) {
        for (i = 0; i < 3; i++) {               /* Set columns */
             PORTB = set_col[i];
            _delay_ms(10);

            for (j = 3; j > 0; j--) {           /* Read rows */
                if (bit_is_clear(PINB, j)) {
                    PORTD = 0xff;               /* Turn off all LEDs */
                    PORTD &= ~disp[3-j][i];     /* Display binary value on LEDs */
                }
            }
        }
    }

    return 0;
}
