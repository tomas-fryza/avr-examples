/*
 * I2C/TWI library for AVR-GCC.
 * (c) 2018-2025 Tomas Fryza, MIT license
 *
 * Developed using PlatformIO and Atmel AVR platform.
 * Tested on Arduino Uno board and ATmega328P, 16 MHz.
 */

// -- Includes ---------------------------------------------
#include <twi.h>


// -- Functions --------------------------------------------
/*
 * Function: twi_init()
 * Purpose:  Initialize TWI unit, enable internal pull-ups, and set SCL
 *           frequency.
 * Returns:  none
 */
void twi_init(void)
{
    /* Enable internal pull-up resistors */
    DDR(TWI_PORT) &= ~((1<<TWI_SDA_PIN) | (1<<TWI_SCL_PIN));
    TWI_PORT |= (1<<TWI_SDA_PIN) | (1<<TWI_SCL_PIN);

    /* Set SCL frequency */
    TWSR &= ~((1<<TWPS1) | (1<<TWPS0));
    TWBR = TWI_BIT_RATE_REG;
}


/*
 * Function: twi_start()
 * Purpose:  Start communication on I2C/TWI bus.
 * Returns:  none
 */
void twi_start(void)
{
    /* Send Start condition */
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}


/*
 * Function: twi_write()
 * Purpose:  Write one byte to the I2C/TWI bus.
 * Input:    data Byte to be transmitted
 * Returns:  ACK/NACK received value
 */
uint8_t twi_write(uint8_t data)
{
    uint8_t twi_status;

    /* Send SLA+R, SLA+W, or data byte on I2C/TWI bus */
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);

    /* Check value of TWI status register */
    twi_status = TWSR & 0xf8;

    /* Status Code:
         - 0x18: SLA+W has been transmitted and ACK received
         - 0x28: Data byte has been transmitted and ACK has been received
         - 0x40: SLA+R has been transmitted and ACK received
    */
    if (twi_status == 0x18 || twi_status == 0x28 || twi_status == 0x40)
        return 0;   /* ACK received */
    else
        return 1;   /* NACK received */
}


/*
 * Function: twi_read()
 * Purpose:  Read one byte from the I2C/TWI bus and acknowledge
 *           it by ACK or NACK.
 * Input:    ack ACK/NACK value to be transmitted
 * Returns:  Received data byte
 */
uint8_t twi_read(uint8_t ack)
{
    if (ack == TWI_ACK)
        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
    else
        TWCR = (1<<TWINT) | (1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);

    return (TWDR);
}


/*
 * Function: twi_stop()
 * Purpose:  Generates Stop condition on I2C/TWI bus.
 * Returns:  none
 */
void twi_stop(void)
{
    TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}


/*
 * Function: twi_test_address()
 * Purpose:  Test presence of one I2C device on the bus.
 * Input:    addr Slave address
 * Returns:  ACK/NACK received value
 */
uint8_t twi_test_address(uint8_t addr)
{
    uint8_t ack;  // ACK response from Slave

    twi_start();
    ack = twi_write((addr<<1) | TWI_WRITE);
    twi_stop();

    return ack;
}


/*
 * Function: twi_readfrom_mem_into()
 * Purpose:  Read into buf from the peripheral starting from the memory address.
 * Input:    addr Slave address
 *           memaddr Starting address
 *           buf Buffer to be read into
 *           nbytes Number of bytes
 * Returns:  None
 */
void twi_readfrom_mem_into(uint8_t addr, uint8_t memaddr, volatile uint8_t *buf, uint8_t nbytes)
{
    twi_start();
    if (twi_write((addr<<1) | TWI_WRITE) == 0) {
        // Set starting address
        twi_write(memaddr);
        twi_stop();

        // Read data into the buffer
        twi_start();
        twi_write((addr<<1) | TWI_READ);
        if (nbytes >= 2) {
            for (uint8_t i=0; i<(nbytes-1); i++) {
                *buf++ = twi_read(TWI_ACK);
            }
        }
        *buf = twi_read(TWI_NACK);
        twi_stop();
    }
    else {
        twi_stop();
    }
}
