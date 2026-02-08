#ifndef SPI_H_INCLUDED
#define SPI_H_INCLUDED
/***********************************************************************
 * Title: SPI library
 * Author: Tomas Fryza, Brno University of Technology
 * Software: avr-gcc, tested with avr-gcc 4.9.2
 * Hardware: any AVR with built-in SPI
 *
 * MIT License
 *
 * Copyright (c) 2017 Tomas Fryza
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 ***********************************************************************
 * @mainpage
 * SPI library for AVR-GCC
 * @author Tomas Fryza, Brno University of Technology
 * @copyright (c) 2017 Tomas Fryza, MIT License
 *
 * @file
 * @code #include <spi.h> @endcode
 *
 * @brief SPI library for AVR-GCC
 *
 * The library defines functions for the SPI communication between AVR
 * microcontroller and SPI slave device.
 *
 * @note Based on Atmel ATmega328P manual
 * @author Tomas Fryza, Brno University of Technology
 * @version 1.0
 * @copyright (c) 2017 Tomas Fryza, MIT License
 */


/*
 *  Constants and macros
 */
/**
 ***********************************************************************
 * @brief MCU port for SPI communication
 */
#define SPI_PORT PORTB


/**
 ***********************************************************************
 * @brief SCK clock pin of SPI communication
 */
#define SPI_SCK_PIN 5       /**< Arduino Uno pin 13 */
//#define SPI_SCK_PIN 7       /**< Sebesta AVR board */


/**
 ***********************************************************************
 * @brief MISO data pin of SPI communication
 */
#define SPI_MISO_PIN 4      /**< Arduino Uno pin 12 */
//#define SPI_MISO_PIN 6      /**< Sebesta AVR board */


/**
 ***********************************************************************
 * @brief MOSI data pin of SPI communication
 */
#define SPI_MOSI_PIN 3      /**< Arduino Uno pin 11 */
//#define SPI_MOSI_PIN 5      /**< Sebesta AVR board */


/**
 ***********************************************************************
 * @brief SS control pin of SPI communication
 */
#define SPI_SS_PIN 2        /**< Arduino Uno pin 10 */
//#define SPI_SS_PIN 4        /**< Sebesta AVR board */


#define SPI_SS_HIGH()   SPI_PORT |= _BV(SPI_SS_PIN)
#define SPI_SS_LOW()    SPI_PORT &= ~(_BV(SPI_SS_PIN))


/*
 *  Function prototypes
 */
/**
 ***********************************************************************
 * @brief Performs initialization of SPI master mode
 * @return None
 * @par Implementation notes:
 *     - Enables SPI master mode
 *     - SPI clock is set to fosc/16
 */
extern void spi_master_init(void);


/**
 ***********************************************************************
 * @brief Master sends one byte on MOSI line
 * @param data One-byte data to send
 * @return None
 * @par Implementation notes:
 *     - SPI slave select pin is not changed
 */
extern void spi_send(uint8_t data);


/**
 ***********************************************************************
 * @brief Master sends one byte on MOSI line and receives one byte on MISO line
 * @param data One-byte data to send
 * @return Received one-byte data
 * @par Implementation notes:
 *     - SPI slave select pin is not changed
 */
extern uint8_t spi_tranceiver(uint8_t data);


#endif /* SPI_H_INCLUDED */
