/***********************************************************************
 * 
 * Test of AVR sleep mode(s) and watchdog wake up.
 * ATmega328P (Arduino Nano), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2019 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 *
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>      // Power Management and Sleep Modes
#include <avr/power.h>      // Power Reduction Management
#include "timer.h"
#include "watchdog.h"

/* Define ------------------------------------------------------------*/
#define LED_GREEN   PB5

/* Variables ---------------------------------------------------------*/
volatile uint8_t timer1_ovf = 0;

/* Function prototypes -----------------------------------------------*/
/** @brief Enter ATmega328P into sleep mode. */
void sleep_1s(void);

/* Functions ---------------------------------------------------------*/
/* Enter ATmega328P into sleep mode. */
void sleep_1s(void) {

    power_timer1_disable();
    WDT_overflow_8s_noreset();
    set_sleep_mode (SLEEP_MODE_PWR_DOWN);
    sleep_enable ();
    sleep_cpu ();           // Now enter sleep mode

    // The program will continue from here after the WDT timeout

    sleep_disable ();       // First thing to do is disable sleep
    WDT_stop();

    power_timer1_enable();
}

/* Main --------------------------------------------------------------*/
/* Set up all hardware modules and perform FSM. */
int main(void) {

    // GPIO Port
    DDRB |= _BV(LED_GREEN);
    PORTB &= ~_BV(LED_GREEN);

    // Timer1
    TIM1_overflow_33ms();
    TIM1_overflow_interrupt_enable();

    // Disable unused modules
    power_twi_disable();
    power_timer0_disable();
    power_timer2_disable();
    power_spi_disable();
    power_usart0_disable();
    power_adc_disable();

    sei();

    for (;;) {
        if (timer1_ovf < 3) {
            sleep_1s();
        } else {
            ;
        }
    }

    return (0);
}

/* Interrupts --------------------------------------------------------*/
/* Timer/Counter1 overflow interrupt routine.
 * Toggle green LED. */
ISR(TIMER1_OVF_vect) {

    timer1_ovf++;
    PORTB ^= _BV(LED_GREEN);
}

/*--------------------------------------------------------------------*/
/* Watchdog overflow interrupt routine.
 * Wake up from sleep mode and toggle green LED. */
ISR (WDT_vect) {

    timer1_ovf++;
}
