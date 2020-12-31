ldr r0, GPFSEL1
mov r1, #(1<<18)
str r1, [r0]

mov r1, #(1<<16)
ldr r0, SET0
str r1, [r0]


GPFSEL1: .word 0x20200004
SET0: .word 0x2020001c