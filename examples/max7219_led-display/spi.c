/***********************************************************************
 * Title: SPI library for AVR-GCC
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


#include <avr/io.h>
#include "spi.h"


/*
 *  Constants and macros
 */
/* Address of data direction register of port x */
#define DDR(x) (*(&x - 1))


/***********************************************************************
 * Performs initialization of SPI master mode
 * param None
 * return None
 */
void spi_master_init(void)
{
    /* Set MOSI, SCK, and SS output, all others input */
    DDR(SPI_PORT) |= _BV(SPI_MOSI_PIN) | _BV(SPI_SCK_PIN) | _BV(SPI_SS_PIN);

    /* Enable SPI, Master mode, set clock rate fosc/16 */
    SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPR0);
}


/***********************************************************************
 * Master sends one byte on MOSI line
 * param data - One-byte data to send
 * return None
 */
void spi_send(uint8_t data)
{
    /* Start transmission */
    SPDR = data;

    /* Wait for transmission complete */
    while ((SPSR & _BV(SPIF)) == 0);
}


/***********************************************************************
 * Master sends one byte on MOSI line and receives one byte on MISO line
 * param data One-byte data to send
 * return Received one-byte data
 */
uint8_t spi_tranceiver(uint8_t data)
{
    /* Start transmission */
    SPDR = data;

    /* Wait for transmission complete */
    while ((SPSR & _BV(SPIF)) == 0);

    /* Return received data */
	return (SPDR);
}
