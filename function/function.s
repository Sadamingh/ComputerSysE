		ldr		r0, =0x3f000000
		ldr		r1, =0x3f000008
		
		str		r1, [r0, #-4]!
		add		r1, r0, #0
		sub		r0, r1, #0
		ldr		r1, [r0], #4
