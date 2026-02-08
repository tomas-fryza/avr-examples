/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2019-10-25
 * Last update: 2019-10-25
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Example of FSM usage.
 * 
 * Note:
 * https://codeandlife.com/2013/10/06/tutorial-state-machines-with-c-callbacks/
 * http://users.ece.utexas.edu/~valvano/Volume1/E-Book/C10_FiniteStateMachines.htm
 * https://arduining.com/2015/09/18/traffic-light-states-machine-with-arduino/
 * https://gist.github.com/nmandery/1717405
 * https://www.embedded.com/an-introduction-to-function-pointers-part-1/
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "gpio.h"
#include "timer.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
//typedef void *(*StateFunc)();
struct State {
    void (*fp)(void);
    uint16_t Time;
    uint8_t Next[2];
};
typedef const struct State SType;

/* Define ------------------------------------------------------------*/
#define LED_GREEN   PB5
#define SON     0
#define SOFF    1
#define SBLINK  2

/* Function prototypes -----------------------------------------------*/
void led_on(void);     //0
void led_off(void);    //1
void led_blink(void);  //2

/* Variables ---------------------------------------------------------*/
SType FSM[] = {
    {&led_on,     5, {SOFF, SOFF}},
    {&led_off,    2, {SBLINK, SBLINK}},
    {&led_blink, 10, {SON, SOFF}}
};
volatile uint8_t timer1_ovf = 0;

/* Functions ---------------------------------------------------------*/
/** 
 *  Brief:  State LED on.
 */
void led_on(void)
{
    PORTB |= _BV(LED_GREEN);
}

/**
 *  Brief:  State LED off.
 */
void led_off(void)
{
    PORTB &= ~_BV(LED_GREEN);
}

/**
 *  Brief:  Toggle LED and delay.
 */
void led_blink(void)
{
    PORTB ^= _BV(LED_GREEN);
    _delay_ms(50);
    PORTB ^= _BV(LED_GREEN);
    _delay_ms(50);
    PORTB ^= _BV(LED_GREEN);
    _delay_ms(50);
    PORTB ^= _BV(LED_GREEN);
}

/**
 *  Brief:  Main program. Using function pointers.
 *  Input:  None
 *  Return: None
 */
int main(void) {
    uint8_t S = SON;

    // LED_GREEN
    GPIO_config_output(&DDRB, LED_GREEN);
    GPIO_write(&PORTB, LED_GREEN, PIN_LOW);

    /* Set Timer1
     * Configure Timer1 clock source and enable overflow  interrupt */
    TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(9600, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    for (;;) {
        (FSM[S].fp)();
        timer1_ovf = FSM[S].Time;

        while (timer1_ovf > 0);

        S = FSM[S].Next[0];
    }

    return (0);
}

/**
 *  Brief: Timer/Counter1 overflow interrupt routine.
 */
ISR(TIMER1_OVF_vect)
{
    char uart_string[4];

    timer1_ovf--;
    itoa(timer1_ovf, uart_string, 10);
    uart_puts(uart_string);
    uart_puts("\r\n");
}
