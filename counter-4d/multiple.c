static volatile unsigned int *FSEL1 =  (unsigned int *)0x20200004;
static volatile unsigned int *FSEL2 =  (unsigned int *)0x20200008;
static volatile unsigned int *SET0  =  (unsigned int *)0x2020001c;
static volatile unsigned int *CLR0  =  (unsigned int *)0x20200028;

#define DELAY 0x3f00
#define DELAY_LONG 0x3f

void main(void) {
    // set GPIO 10-13 to output
    *FSEL1 = 0b1001001001;
    // set GPIO 20-26 to output
    *FSEL2 = 0b1001001001001001001; 

    int digit[] = {
        0b111111,
        0b110,
        0b1011011,
        0b1001111,
        0b1100110,
        0b1101101,
        0b1111101,
        0b111,
        0b1111111,
        0b1101111};

    int value = 0;
    int digits[4];

    while (1) {
        digits[0] = (value - value % 1000) / 1000;
        digits[1] = value % 1000 / 100;
        digits[2] = value % 100 / 10;
        digits[3] = value % 10;
        // keep the value for a time
        for (int t = DELAY_LONG; t != 0; t--) {
            for(int i = 0; i < 4; i++){
                *SET0 = (digit[digits[i]] << 20) + (1 << (10+i)); 
                // delay a short time to produce pov
                for (int c = DELAY; c != 0; c--) ;
                *CLR0 = (digit[digits[i]] << 20) + (1 << (10+i)); 
            }
        }
        value++;
        if (value == 10000) value = 0;
    }

}