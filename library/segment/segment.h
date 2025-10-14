#ifndef SEGMENT_H
#define SEGMENT_H

/*
 * Seven-segment display library for AVR-GCC.
 * (c) 2019-2025 Tomas Fryza, MIT license
 * 
 * Developed using PlatformIO and Atmel AVR platform.
 * Tested on Arduino Uno board and ATmega328P, 16 MHz.
 */

/**
 * @file 
 * @defgroup fryza_segment Seven-segment Library <segment.h>
 * @code #include <segment.h> @endcode
 *
 * @brief Seven-segment display library for AVR-GCC.
 *
 * The library contains functions for controlling the seven-segment 
 * display (SSD) using two shift registers 74HC595.
 *
 * @copyright (c) 2019-2025 Tomas Fryza, MIT license
 * @{
 */


// -- Includes ---------------------------------------------
#include <avr/io.h>


// -- Defines ----------------------------------------------
/**
 * @name  Definition of SSD interface
 * @note  Connection is based on Multi-function shield.
 */
#define SEG_LATCH   PD4
#define SEG_CLK     PD7
#define SEG_DATA    PB0


// --- Function prototypes ----------------------------------
/**
 * @brief  Configure SSD signals LATCH, CLK, and DATA as output.
 * @return none
 */
void seg_init(void);


/**
 * @brief  Display segments at one position of the SSD.
 * @param  segments Segments to be displayed (abcdefgDP, active low)
 * @param  position Position of the display where the segments are to 
 *                  be displayed (p3 p2 p1 p0 xxxx, active high)
 * @note   Two shift registers are connected in series, ie 16 bits are 
 *         transmitted.
 * @return none
 */
void seg_update_shift_regs(uint8_t segments, uint8_t position);


/* seg_clear */


/* seg_clk_2us */


/** @} */

#endif
