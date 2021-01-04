static volatile unsigned int *FSEL2 =  (unsigned int *)0x20200008;
static volatile unsigned int *SET0  =  (unsigned int *)0x2020001c;
static volatile unsigned int *CLR0  =  (unsigned int *)0x20200028;

#define DELAY 0x3f0000

void main(void) {
   *FSEL2 = 8;  // configure GPIO 21 for output

   while (1) {
        *SET0 = 1 << 21;    // set GPIO 21
        for (int c = DELAY; c != 0; c--) ;  // wait
        *CLR0 = 1 << 21;    // clear GPIO 21
        for (int c = DELAY; c != 0; c--) ;  // wait
   }
}