.equ DELAY, 0x3F0000

// configure GPIO 10 for input
ldr r0, FSEL1
mov r1, #0
str r1, [r0]

// configure GPIO 21 for output
ldr r0, FSEL2
mov r1, #8
str r1, [r0]

// bit 10 and 21
mov r2, #(1<<10)
mov r3, #(1<<21)

loop: 
    // read GPIO 10 
    ldr r0, LEV0
    ldr r1, [r0] 
    tst r1, r2
    beq on // when the button is pressed (goes LOW), turn on LED
    
    // set GPIO 21 low
    off:
        ldr r0, CLR0
        str r3, [r0]
        b loop

    // set GPIO 21 high
    on:
        // set GPIO 21 high
        ldr r0, SET0
        str r3, [r0]

        // delay a certain time
        mov r4, #DELAY
        wait1:
            subs r4, r4, #1
            bne wait1

        // clear GPIO 21 status
        ldr r0, CLR0
        str r3, [r0]

        // delay a certain time
        mov r4, #DELAY
        wait2:
            subs r4, r4, #1
            bne wait2

        b loop

FSEL1: .word 0x20200004
FSEL2: .word 0x20200008
SET0: .word 0x2020001C
CLR0: .word 0x20200028
LEV0:  .word 0x20200034