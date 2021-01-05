static volatile unsigned int *FSEL2 =  (unsigned int *)0x20200008;
static volatile unsigned int *SET0  =  (unsigned int *)0x2020001c;
static volatile unsigned int *CLR0  =  (unsigned int *)0x20200028;

#define DELAY 0x3f0000

void main(void) {
	// set GPIO 20-26 to output
    *FSEL2 = 0b1001001001001001001; 

    // assign the rules for displaying digits
    int digit0 = 0b111111;
    int digit1 = 0b110;
    int digit2 = 0b1011011;
    int digit3 = 0b1001111;
    int digit4 = 0b1100110;
    int digit5 = 0b1101101;
    int digit6 = 0b1111101;
    int digit7 = 0b111;
    int digit8 = 0b1111111;
    int digit9 = 0b1101111;

    while (1) {
        *SET0 = digit0 << 20; 
        for (int c = DELAY; c != 0; c--) ; 
        *CLR0 = digit0 << 20; 
 
    	*SET0 = digit1 << 20; 
        for (int c = DELAY; c != 0; c--) ; 
        *CLR0 = digit1 << 20; 

    	*SET0 = digit2 << 20; 
        for (int c = DELAY; c != 0; c--) ; 
        *CLR0 = digit2 << 20; 

    	*SET0 = digit3 << 20; 
        for (int c = DELAY; c != 0; c--) ; 
        *CLR0 = digit3 << 20; 

    	*SET0 = digit4 << 20; 
        for (int c = DELAY; c != 0; c--) ; 
        *CLR0 = digit4 << 20; 

    	*SET0 = digit5 << 20; 
        for (int c = DELAY; c != 0; c--) ; 
        *CLR0 = digit5 << 20;

    	*SET0 = digit6 << 20; 
        for (int c = DELAY; c != 0; c--) ; 
        *CLR0 = digit6 << 20; 

    	*SET0 = digit7 << 20; 
        for (int c = DELAY; c != 0; c--) ; 
        *CLR0 = digit7 << 20; 

    	*SET0 = digit8 << 20; 
        for (int c = DELAY; c != 0; c--) ; 
        *CLR0 = digit8 << 20; 

    	*SET0 = digit9 << 20; 
        for (int c = DELAY; c != 0; c--) ; 
        *CLR0 = digit9 << 20; 
    }
}

