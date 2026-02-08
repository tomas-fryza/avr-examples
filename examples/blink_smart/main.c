/**
  ******************************************************************************
  * @file    main.c
  * @author  Tomas Fryza, Brno University of Technology, Czechia
  * @version V1.0
  * @date    Oct 06, 2018
  * @brief   Count button presses and set number of LED blinks.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "settings.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* Constants and macros ------------------------------------------------------*/
/**
  * @brief Binary pattern for debounce routine.
  */
#define PATTERN 0b00000111
#define FALSE 0
#define TRUE 1

/* Function prototypes -------------------------------------------------------*/
void setup(void);
void fsm_debounce_INT0(void);
void execute_INT0(void);

/* Global variables ----------------------------------------------------------*/
volatile uint8_t number_of_toggles;
volatile uint8_t number_of_overflows;
volatile uint8_t pattern = 0b10101010;
volatile uint8_t pressed = FALSE;

typedef enum {
    READ_INPUT_STATE = 1,
    LOW_STATE,
    HIGH_STATE
} state_t;
state_t state = READ_INPUT_STATE;

/* Functions -----------------------------------------------------------------*/
/**
  * @brief Main function.
  */
int main(void)
{
    /* Initializations */
    setup();

    /* Enables interrupts by setting the global interrupt mask */
    sei();

    /* Forever loop */
    while (1) {
        /* Cycle here, do nothing, and wait for an interrupt */
    }

    return 0;
}

/**
  * @brief Setup all peripherals.
  */
void setup(void)
{
    /* Set output pin 13 (PB5) */
    DDRB |= _BV(PB5);
    /* Turn LED off */
    PORTB &= ~_BV(PB5);


    /* Set input pin 2 (PD2) */
    DDRD &= ~_BV(PD2);
    /* Activate internal pull-up at pin 2 (PD2) */
    PORTD |= _BV(PD2);

    /* External Interrupt: enable External Interrupt by INT0 pin 2 (PD2) */
    /* Falling edge of INT0 generates an interrupt request */
    EICRA |= _BV(ISC01);
    /* Enable External Interrupt Request 0 */
    EIMSK |= _BV(INT0);


    /* Timer/Counter1: select clock and enable overflow */
    /* Clock prescaler 64 => overflows every 262 ms */
    TCCR1B |= _BV(CS11) | _BV(CS10);
    /* Overflow interrupt enable */
    TIMSK1 |= _BV(TOIE1);


    /* Timer/Counter0: debounce timer */
    /* Clock prescaler 1024 => overflows every 16 ms */
    TCCR0B |= _BV(CS02) | _BV(CS00);


    /* Reset number of LED toggles, i.e. press button times 2 */
    number_of_toggles = 0;
    /* Reset number of timer1 overflows */
    number_of_overflows = 0;
}

/**
  * @brief Increment number of LED blinks. Iniciate debouncing routine.
  */
ISR(INT0_vect)
{
    /* Timer/Counter0: debounce timer */
    /* Overflow interrupt enable */
    TIMSK0 |= _BV(TOIE0);
}

/**
  * @brief Call FSM debounce routine for INT0 signal.
  */
ISR(TIMER0_OVF_vect)
{
    fsm_debounce_INT0();
}

/**
  * @brief Update state of debounce finite state machine for INT0 pin
  */
void fsm_debounce_INT0(void)
{
    switch (state) {

    /* Read pin value */
    case READ_INPUT_STATE:
        /* Update pattern according to current INT0 signal value */
        pattern <<= 1;
        if (bit_is_set(PIND, PD2)) {
            pattern += 1;
        }
        if ((pressed == FALSE) && ((pattern & PATTERN) == 0x00)) {
            state = LOW_STATE;
        } else if ((pattern & PATTERN) == PATTERN) {
            state = HIGH_STATE;
        } else {
            state = READ_INPUT_STATE;
        }
        break;

    /* Button pressed */
    case LOW_STATE:
        /* Debounce routine is over. Execute user function */
        execute_INT0();
        pressed = TRUE;
        state = READ_INPUT_STATE;
        break;

    /* Button released */
    case HIGH_STATE:
        /* Timer/Counter0: debunce timer */
        /* Overflow interrupt disable */
        TIMSK0 &= ~_BV(TOIE0);
        pressed = FALSE;
        state = READ_INPUT_STATE;
        break;

    default:
        state = READ_INPUT_STATE;
    }
}

/**
  * @brief Increment number of LED blinks. Execute the routine after debouncing.
  */
void execute_INT0(void)
{
    /* Increase number of LED toggles */
    number_of_toggles += 2;

    /* Reset number of timer1 overflows */
    number_of_overflows = 0;
}

/**
  * @brief Blink LED according to number of button presses.
  */
ISR(TIMER1_OVF_vect)
{
    /* Increase number of overflows */
    number_of_overflows++;

    /* Wait for 8 overflows, i.e. 8 * 262 = 2 sec */
    if (number_of_overflows >= 8) {

        /* Are there blinks to show? */
        if (number_of_toggles > 0) {

            /* Toggle LED */
            PORTB ^= _BV(PB5);

            /* Decrease number of LED toggles */
            number_of_toggles--;
        }
    }
}

/* END OF FILE ****************************************************************/
