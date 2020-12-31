// configure GPIO 21 for output
ldr r0, GPFSEL2
mov r1, #8
str r1, [r0]

mov r1, #(1<<21)

// set GPIO 21 high
ldr r0, SET0
str r1, [r0] 

GPFSEL2: .word 0x20200008
SET0:  .word 0x2020001C
