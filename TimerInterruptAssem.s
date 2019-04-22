#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
  name isr_asm
  section .text:CODE
  extern sentActual                ; counter for the number of ISR triggers
  public isr_asm_start             ; req for use outside this file
isr_asm_start:                     ; start of the ISR
    MOVS R2, #1                    ; Moves the immiediate 1 into R1
    MOV32 R0, #0x40031024          ; loads the timeout address into R0
    STR R2, [R0]                   ; clear the timer interrupt
    MOV32 R0, sentActual           ; get the address of sentActual
    LDR R1, [R0]                   ; load the value into r1
    ADD R1, R1, R2                 ; increment
    STR R1, [R0]                   ; store r1 at r0
    BX LR                          ; pop the PC back onto the stack
 end                               ; end the routine