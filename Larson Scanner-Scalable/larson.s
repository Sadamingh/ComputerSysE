.equ DELAY, 0x3F0000
.equ AMOUNT, 4

// set output to GPIO 20 to 27
ldr r0, FSEL2
ldr r1, =0x00249249
str r1, [r0]

// set the starting status
mov r1, #(1<<20) // current pin
mov r3, #1
mov r4, #(1<<20)
mov r5, #(1<<18)
lsl r4, #AMOUNT
lsl r5, #AMOUNT

loop:
	ldr r0, SET0
	str r1, [r0]

	// delay a certain time
	mov r2, #DELAY
	wait1:
	    subs r2, r2, #1
	    bne wait1

	// clear GPIO status
	ldr r0, CLR0
	str r1, [r0]

	tst r3, #1
	bne forward
	beq backward
	
forward:
	lsl r1, #1
	b compar

backward:
	lsr r1, #1
	b compar

compar:
	cmp r1, r4
	moveq r1, r5
	moveq r3, #2

	cmp r1, #(1<<19)
	moveq r1, #(1<<21)
	moveq r3, #1

	b loop


FSEL2: .word 0x20200008
SET0: .word 0x2020001c
CLR0: .word 0x20200028