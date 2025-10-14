;
; Assembly implementation of 4- and 8-bit pseudo-random generators based
; on LFSR (Linear Feedback Shift Register) with Fibonacci architecture.
; (c) 2017-2025 Tomas Fryza, MIT license
;
; Developed using PlatformIO and Atmel AVR platform.
; Tested on Arduino Uno board and ATmega328P, 16 MHz.
;
; Inspired by:
;   - http://www.physics.otago.ac.nz/reports/electronics/ETR2012-1.pdf
;   - http://courses.cse.tamu.edu/walker/csce680/lfsr_table.pdf
;   - https://repository.uobabylon.edu.iq/mirror/resources/paper_1_17528_649.pdf
;   - https://courses.cs.washington.edu/courses/cse369/15au/labs/xapp052_LFSRs.pdf
;

; -- Includes ----------------------------------------------
; Set offset for control register addresses (NEEDED FOR I/O REGISTERS)
#define __SFR_OFFSET    0
#include <avr/io.h>


; -- Defines -----------------------------------------------
#define in_out_reg r24
#define temp0      r26
#define temp1      r27
#define a          r22
#define b          r20



; -- Function definitions ----------------------------------
;
; Function: multiply_accumulate_asm
; Purpose:  Multiply-and-Accumulate operation: in_out_reg = in_out_reg + (a*b).
; Input(s): r24 - Current MAC value
;           r22 - Value A
;           r20 - Value B
; Return:   r24 - New MAC value
;
.global multiply_accumulate_asm
multiply_accumulate_asm:
    mul a, b            ; Multiply Unsigned, r1:0 = a * b
    add in_out_reg, r0  ; Accumulate just low product result
    ret                 ; Return from subroutine


;
; Function: lfsr4_fibonacci_asm
; Purpose:  LFSR-based 4-bit pseudo-random generator with Fibonacci
;           architecture. Taps are 4, 3.
;
;   in_out_reg:       3   2   1   0                 +-----+
;   +---+---+---+---+---+---+---+---+    +-----+    |     |-------+
;   | x | x | x | x | 4 | 3 |   |   |<---| NOT |<---| XOR |       |
;   +---+---+---+---+---+---+---+---+    +-----+    |     |---+   |
;                     |   |                         +-----+   |   |
;                     |   +-----------------------------------+   |
;                     |                                           |
;                     +-------------------------------------------+
;
; Input:    r24 - Current value of LFSR
; Return:   r24 - New value of LFSR
;
.global lfsr4_fibonacci_asm
lfsr4_fibonacci_asm:
    push temp0             ; Save used registers on Stack
    push temp1
    bst in_out_reg, 3      ; Copy FIRST tap to T-flag bit...
    bld temp0, 0           ; ...and then to temp0 at position 0
                           ; temp0:                        0
                           ; +---+---+---+---+---+---+---+---+
                           ; | x | x | x | x | x | x | x | 4 |
                           ; +---+---+---+---+---+---+---+---+

    bst in_out_reg, 2      ; Copy SECOND tap to T-flag bit...
    bld temp1, 0           ; ...and then to temp1 at position 0
                           ; temp1:                        0
                           ; +---+---+---+---+---+---+---+---+
                           ; | x | x | x | x | x | x | x | 3 |
                           ; +---+---+---+---+---+---+---+---+

    eor temp0, temp1       ; Xor both taps
    com temp0              ; Invert Xor
    ror temp0              ; Rotate register right and move bit0 to C-flag
                           ; temp0:
                           ; +---+---+---+---+---+---+---+---+
                           ; | x | x | x | x | x | x | x | x | --> C
                           ; +---+---+---+---+---+---+---+---+

    rol in_out_reg         ; Rotate register left and move C-flag to bit0
                           ; in_out_reg:       3   2   1   0
                           ; +---+---+---+---+---+---+---+---+
                           ; | x | x | x | 3 | 2 | 1 | 0 | C | <-- C
                           ; +---+---+---+---+---+---+---+---+
    andi in_out_reg, 0x0f  ; Need only 4-bit, so clear four upper bits
                           ; in_out_reg:       3   2   1   0
                           ; +---+---+---+---+---+---+---+---+
                           ; | 0 | 0 | 0 | 0 | 2 | 1 | 0 | C |
                           ; +---+---+---+---+---+---+---+---+

    pop temp1              ; Restore used registers from Stack
    pop temp0
    ret                    ; Return from subroutine
