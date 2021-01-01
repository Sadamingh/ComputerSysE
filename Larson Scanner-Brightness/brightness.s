.equ DELAY, 0x010000
.equ AMOUNT, 8

.equ BRIGHT1, 0b1
.equ BRIGHT2, 0b111
.equ BRIGHT3, 0b111111

// set output to GPIO 20 to 27
ldr r0, FSEL2
ldr r1, =0x00249249
str r1, [r0]

// set the starting status
mov r1, #(1<<20) // current pin
mov r2, #DELAY
mov r3, #1
mov r4, #(1<<20)
mov r5, #(1<<18)
lsl r4, #AMOUNT
lsl r5, #AMOUNT

loop:
	// mid light
	ldr r0, SET0
	and r6, r2, #BRIGHT1
	cmp r6, #BRIGHT1
	streq r1, [r0]

	ldr r0, CLR0
	str r1, [r0]

	// 1st left light
	ldr r0, SET0
	lsl r1, #1
	and r6, r2, #BRIGHT2
	cmp r6, #BRIGHT2
	streq r1, [r0]

	ldr r0, CLR0
	str r1, [r0]

	// 2nd left light
	ldr r0, SET0
	lsl r1, #1
	and r6, r2, #BRIGHT3
	cmp r6, #BRIGHT3
	streq r1, [r0]

	ldr r0, CLR0
	str r1, [r0]

	// 1st right light
	ldr r0, SET0
	lsr r1, #3
	and r6, r2, #BRIGHT2
	cmp r6, #BRIGHT2
	streq r1, [r0]

	ldr r0, CLR0
	str r1, [r0]

	// 2nd right light
	ldr r0, SET0
	lsr r1, #1
	and r6, r2, #BRIGHT3
	cmp r6, #BRIGHT3
	streq r1, [r0]

	ldr r0, CLR0
	str r1, [r0]

	// reset r1
	lsl r1, #2

	// count until DELAY
	subs r2, #1
	bne loop

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

	// reset r2
	mov r2, #DELAY

	b loop


FSEL2: .word 0x20200008
SET0: .word 0x2020001c
CLR0: .word 0x20200028