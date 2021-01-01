.equ DELAY, 0x3F0000

// configure GPIO 21 for output
ldr r0, GPFSEL2
mov r1, #8
str r1, [r0]
mov r1, #(1<<21)

loop:

	// set GPIO 21 high
	ldr r0, SET0
	str r1, [r0]

	// delay a certain time
	mov r2, #DELAY
	wait1:
	    subs r2, r2, #1
	    bne wait1

	// clear GPIO 21 status
	ldr r0, CLR0
	str r1, [r0]

	// delay a certain time
	mov r2, #DELAY
	wait2:
	    subs r2, r2, #1
	    bne wait2
	    
b loop

GPFSEL2: .word 0x20200008
SET0: .word 0x2020001C
CLR0: .word 0x20200028