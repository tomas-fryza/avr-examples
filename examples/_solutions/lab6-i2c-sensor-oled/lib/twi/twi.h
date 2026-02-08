#ifndef TWI_H
#define TWI_H

/*
 * I2C/TWI library for AVR-GCC.
 * (c) 2018-2025 Tomas Fryza, MIT license
 *
 * Developed using PlatformIO and Atmel AVR platform.
 * Tested on Arduino Uno board and ATmega328P, 16 MHz.
 */

/**
 * @file 
 * @defgroup fryza_twi TWI Library <twi.h>
 * @code #include <twi.h> @endcode
 *
 * @brief I2C/TWI library for AVR-GCC.
 *
 * This library defines functions for the TWI (I2C) communication between
 * AVR and Slave device(s). Functions use internal TWI module of AVR.
 *
 * @note Only Master transmitting and Master receiving modes are implemented. Based on Microchip Atmel ATmega16 and ATmega328P manuals.
 * @copyright (c) 2018-2025 Tomas Fryza, MIT license
 * @{
 */

// -- Includes ---------------------------------------------
 #include <avr/io.h>


// -- Defines ----------------------------------------------
/**
 * @name Definition of frequencies 
 */
#ifndef F_CPU
#define F_CPU 16000000 /**< @brief CPU frequency in Hz required TWI_BIT_RATE_REG */
#endif
#define F_SCL 100000 /**< @brief I2C/TWI bit rate. Must be greater than 31000 */
#define TWI_BIT_RATE_REG ((F_CPU/F_SCL - 16) / 2) /**< @brief TWI bit rate register value */


/**
 * @name Definition of ports and pins
 */
#define TWI_PORT PORTC /**< @brief Port of TWI unit */
#define TWI_SDA_PIN 4 /**< @brief SDA pin of TWI unit */
#define TWI_SCL_PIN 5 /**< @brief SCL pin of TWI unit */


/**
 * @name Other definitions
 */
#define TWI_WRITE 0 /**< @brief Mode for writing to I2C/TWI device */
#define TWI_READ 1 /**< @brief Mode for reading from I2C/TWI device */
#define TWI_ACK 0 /**< @brief ACK value for writing to I2C/TWI bus */
#define TWI_NACK 1 /**< @brief NACK value for writing to I2C/TWI bus */
#define DDR(_x) (*(&_x - 1)) /**< @brief Address of Data Direction Register of port _x */
#define PIN(_x) (*(&_x - 2)) /**< @brief Address of input register of port _x */


// -- Function prototypes ----------------------------------
/**
 * @brief  Initialize TWI unit, enable internal pull-ups, and set SCL frequency.
 * @par    Implementation notes:
 *           - AVR internal pull-up resistors at pins TWI_SDA_PIN and
 *             TWI_SCL_PIN are enabled
 *           - TWI bit rate register value is calculated as follows
 *             fscl = fcpu/(16 + 2*TWBR)
 * @return none
 */
void twi_init(void);


/**
 * @brief  Start communication on I2C/TWI bus.
 * @return none
 */
void twi_start(void);


/**
 * @brief  Write one byte to the I2C/TWI bus.
 * @param  data Byte to be transmitted
 * @return ACK/NACK received value
 * @retval 0 - ACK has been received
 * @retval 1 - NACK has been received
 * @note   Function returns 0 if 0x18, 0x28, or 0x40 status code is detected\n
 *           - 0x18: SLA+W has been transmitted and ACK has been received\n
 *           - 0x28: Data byte has been transmitted and ACK has been received\n
 *           - 0x40: SLA+R has been transmitted and ACK has been received\n
 */
uint8_t twi_write(uint8_t data);


/**
 * @brief  Read one byte from the I2C/TWI bus and acknowledge
 *         it by ACK or NACK.
 * @param  ack - ACK/NACK value to be transmitted
 * @return Received data byte
 */
uint8_t twi_read(uint8_t ack);


/**
 * @brief  Generates Stop condition on I2C/TWI bus.
 * @return none
 */
void twi_stop(void);


/**
 * @brief  Test presence of one I2C device on the bus.
 * @param  addr Slave address
 * @return ACK/NACK received value
 * @retval 0 - ACK has been received
 * @retval 1 - NACK has been received
 */
uint8_t twi_test_address(uint8_t addr);


/**
 * @brief  Read into buf from the peripheral, starting from the memory address.
 * @param  addr Slave address
 * @param  memaddr Starting address
 * @param  buf Buffer to be read into
 * @param  nbytes Number of bytes
 * @return none
 */
void twi_readfrom_mem_into(uint8_t addr, uint8_t memaddr, volatile uint8_t *buf, uint8_t nbytes);

/** @} */

#endif
