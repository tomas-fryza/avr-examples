/**
 *  @file main.c
 *  @author Tomas Fryza, Brno University of Technology, Czechia
 *  @version V1.0
 *  @date Oct 29, 2018
 *
 *  @brief Read humidity/temperature values from DHT12 sensor and transmit data
 *         to ThingSpeak.com via ESP8266 Wi-Fi module.
 *  @warning Size of UART circular transmit buffer, must be increased to 128
 *           (see uart.h)
 */


/* Includes ------------------------------------------------------------------*/
#include "settings.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>          /* sprintf() function */
#include <stdlib.h>         /* itoa() function */
#include "twi.h"
#include "uart.h"


/* Constants and macros ------------------------------------------------------*/
/**
 *  @brief Define UART buad rate.
 */
#define UART_BAUD_RATE 115200


/**
 *  @brief Address of TWI slave device (humidity/temperature DHT12 sensor).
 */
#define TWI_DHT12 0x5c


/**
 *  @brief Parameters for Wi-Fi connection.
 */
#define SSID "UREL-SC661-V-2.4G"
#define PSW "TomFryza"
#define URL_ADDR "api.thingspeak.com"
#define WRITE_API_KEY "I5GHICIN7DUJSFNF"


/**
 *  @brief Number of Timer/Counter1 overflows between humidity/temperature
 *         measurements.
 *  @note  Value must be between 5 and 255 and minimal Timer/Counter1 overflow
 *         must occur after 500 ms.
 */
#define INTERVAL_BETWEEN_MEASUREMENTS 255


/* Function prototypes -------------------------------------------------------*/
/**
 *  @brief Initialize UART, ESP8266 Wi-Fi module, TWI, and Timer/Counter1.
 */
void setup(void);


/**
 *  @brief Initialize ESP8266 module, connect to SSID, and ask for IP address.
 */
void esp8266_init(void);


/**
 *  @brief FSM reads humidity/temperature values and transmits data via Wi-Fi.
 */
void fsm_meteo(void);


/* Global variables ----------------------------------------------------------*/
typedef enum {
    IDLE_STATE = 1,
    DHT12_STATE,
    ESP8266_START_STATE,
    ESP8266_SEND_LENGTH_STATE,
    ESP8266_SEND_DATA_STATE
} state_t;
/* FSM for communication with DHT12 sensor and ESP8266 Wi-Fi module */
state_t meteo_state = IDLE_STATE;

struct Values {
    uint8_t humidity_integer;
    uint8_t humidity_decimal;
    uint8_t temperature_integer;
    uint8_t temperature_decimal;
};
/* Data structure for humidity and temperature values */
struct Values Meteo_values;

volatile uint8_t number_of_overflows = 0;


/* Functions -----------------------------------------------------------------*/
int main(void)
{
    /* Enables interrupts by setting the global interrupt mask */
    sei();

    /* Initializations */
    setup();

    /* Forever loop */
    while (1) {
        /* Cycle here, do nothing, and wait for an interrupt */
    }

    return 0;
}


/*******************************************************************************
 * Function: setup()
 * Purpose:  Initialize UART, ESP8266 Wi-Fi module, TWI, and Timer/Counter1.
 * Input:    None
 * Returns:  None
 ******************************************************************************/
void setup(void)
{
    /* Initialize UART: asynchronous, 8-bit data, no parity, 1-bit stop */
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    /* Initialize ESP8266 Wi-Fi module */
    esp8266_init();

    /* Initialize TWI: DHT12 module */
    twi_init();

    /* Timer/Counter1: update FSM state */
    /* Clock prescaler 256 => overflows every second */
    TCCR1B |= _BV(CS12);
    /* Overflow interrupt enable */
    TIMSK1 |= _BV(TOIE1);
}


/*******************************************************************************
 * Function: esp8266_init()
 * Purpose:  Initialize ESP8266 module, connect to SSID, and ask for IP address.
 * Input:    None
 * Returns:  None
 ******************************************************************************/
void esp8266_init(void)
{
_delay_ms(3000);
    /* Test if AT system works correctly */
    uart_puts("AT\r\n");
    _delay_ms(3);
    /* Set mode to STA */
    uart_puts("AT+CWMODE=1\r\n");
    _delay_ms(20);
    /* Login to SSID and ask for IP address */
    uart_puts("AT+CWJAP=\"" SSID "\",\"" PSW "\"\r\n");
    _delay_ms(10000);
}


/*******************************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Update state of TWI Finite State Machine.
 ******************************************************************************/
ISR(TIMER1_OVF_vect)
{
    /* Increase number of overflows */
    number_of_overflows++;

    /* Read humidity/temperature values after MEASUREMENT_INTERVAL overflows */
    if (number_of_overflows == 1) {
        meteo_state = DHT12_STATE;
    }
    /* Start communication with ESP8266 Wi-Fi module */
    else if (number_of_overflows == 2) {
        meteo_state = ESP8266_START_STATE;
    }
    /* Send number of bytes to be transmitted via ESP8266 Wi-Fi module */
    /* Make sure, transition between all ESP8266 states is at least 500 ms */
    else if (number_of_overflows == 3) {
        meteo_state = ESP8266_SEND_LENGTH_STATE;
    }
    /* Send values via ESP8266 Wi-Fi module */
    /* Make sure, transition between all ESP8266 states is at least 500 ms */
    else if (number_of_overflows == 4) {
        meteo_state = ESP8266_SEND_DATA_STATE;
    }
    /* Start measuring/transmitting process again */
    else if (number_of_overflows == INTERVAL_BETWEEN_MEASUREMENTS) {
        meteo_state = IDLE_STATE;
        number_of_overflows = 0;
    }
    /* Do nothing */
    else {
        meteo_state = IDLE_STATE;
    }

    fsm_meteo();
}


/*******************************************************************************
 * Function: fsm_meteo()
 * Purpose:  FSM reads humidity/temperature values and transmits data via Wi-Fi.
 * Input:    None
 * Returns:  None
 ******************************************************************************/
void fsm_meteo(void)
{
    uint8_t twi_status;
    char http_get_request[80];
    uint8_t length;
    char http_cipsend[50];

    switch (meteo_state) {
    /* Do nothing */
    case IDLE_STATE:
        break;

    /* Read humidity/temperature values */
    case DHT12_STATE:
        twi_status = twi_start((TWI_DHT12<<1) + TWI_WRITE);
        if (twi_status == 0) {  /* Slave device accessible */
            /* Set pointer to address 0x00: Humidity integer part */
            twi_write(0x00);
            twi_stop();
            /* Read humidity and temperature values from addresses 0x00:0x03 */
            twi_start((TWI_DHT12<<1) + TWI_READ);
            Meteo_values.humidity_integer = twi_read_ack();     /* Addr 0x00 */
            Meteo_values.humidity_decimal = twi_read_ack();     /* Addr 0x01 */
            Meteo_values.temperature_integer = twi_read_ack();  /* Addr 0x02 */
            Meteo_values.temperature_decimal = twi_read_nack(); /* Addr 0x03 */
            twi_stop();
        }
        else {                  /* Failed to access slave device */
            twi_stop();
        }
        break;

    /* Start communication with ESP8266 Wi-Fi module */
    case ESP8266_START_STATE:
        /* Start communication with server ThingSpeak.com */
        uart_puts("AT+CIPSTART=\"TCP\",\"" URL_ADDR "\",80\r\n");
        break;

    /* Send number of bytes to be transmitted via ESP8266 Wi-Fi module */
    case ESP8266_SEND_LENGTH_STATE:
        /* Prepare HTTP request for server, including humidity/temperature data */
        length = sprintf(http_get_request,
                "GET /update?api_key=" WRITE_API_KEY "&field1=%d.%d&field2=%d.%d\r\n",
                Meteo_values.humidity_integer, Meteo_values.humidity_decimal,
                Meteo_values.temperature_integer, Meteo_values.temperature_decimal);

        /* Send number of bytes you are going to transmit */
        sprintf(http_cipsend, "AT+CIPSEND=%d\r\n", length);
        uart_puts(http_cipsend);
        break;

    /* Send values via ESP8266 Wi-Fi module */
    case ESP8266_SEND_DATA_STATE:
        /* Send HTTP request */
        uart_puts(http_get_request);
        break;

    default:
        meteo_state = IDLE_STATE;
    } /* End of switch (meteo_state) */
}


/* END OF FILE ****************************************************************/
