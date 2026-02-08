
# Demo Project

#### Table of Contents

1. [Introduction](#introduction)
2. [Hardware](#hardware)
3. [Software](#software)
4. [References](#references)


## Introduction

TBD


## Hardware

![arduino-nano_pinout](../../docs/arduino-nano_pinout_foto.jpg)

![arduino-nano_pinout](../../docs/arduino-nano_pinout.png)

Arduino Nano:
--ATmega328P-32TQFP
30 [RxD] PD0 (RxD)                      ??
31 [TxD] PD1 (TxD)                      ??
32 [D2] PD2 (INT0, PCINT18)
1 [D3] PD3 (INT1, PCINT19, OC2B)
2 [D4] PD4 (T0, PCINT20, XCK)           SUPPLY_ESP
9 [D5] PD5 (T1, PCINT21, OC0B)
10 [D6] PD6 (AIN0, PCINT22, OC0A)
11 [D7] PD7 (AIN1, PCINT23)

12 [D8] PB0 (PCINT0, CLKO, ICP1)        ECHO
13 [D9] PB1 (PCINT1, OC1A)
14 [D10] PB2 (SS, PCINT2, OC1B)         TRIG
15 [D11] PB3 (MOSI, PCINT3, OC2A)
16 [D12] PB4 (MISO, PCINT4)             SUPPLY_ULTRASOUND
17 [D13] PB5 (SCK, PCINT5)
7 [--] PB6 (XTAL1)
8 [--] PB7 (XTAL2)

20 [REF] (AREF)
23 [A0] PC0 (ADC0, PCINT8)
24 [A1] PC1 (ADC1, PCINT9)
25 [A2] PC2 (ADC2, PCINT10)
26 [A3] PC3 (ADC3, PCINT11)
27 [A4] PC4 (ADC4, SDA, PCINT12)
28 [A5] PC5 (ADC5, SCL, PCINT13)
19 [A6] (ADC6)
22 [A7] (ADC7)
29 [RST] PC6 (RESET)


## Software

Sleep:
https://www.gammon.com.au/forum/?id=11497
https://gist.github.com/stojg/aec2c8c54c29c0fab407
http://www.bot-thoughts.com/2013/11/avr-watchdog-as-sleep-delay.html
https://www.avrfreaks.net/forum/how-utilize-watch-dog-timer-wdt-atmega8-newbie


## References

1. Microchip, [AVR 8-bit Toolchain for Windows, Linux, Mac OS X](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers)
