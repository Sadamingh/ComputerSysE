#include "gpio.h"
#include "timer.h"

#define DELAY 0x3f0000

void displaydigit(int value);

unsigned int digit[] = {
    0x3f, // 0 0b00111111
    0x06, // 1 0b00000110
    0x5b, // 2 0b01011011
    0x4f, // 3 0b01001111
    0x66, // 4 0b01100110
    0x6d, // 5 0b01101101
    0x7d, // 6 0b01111101
    0x07, // 7 0b00000111
    0x7f, // 8 0b01111111
    0x6f, // 9 0b01101111
    0x77, // A 0b01110111
    0x7f, // B 0b01111111
    0x39, // C 0b00111001
    0x3f, // D 0b00111111
    0x79, // E 0b01111001
    0x71, // F 0b01110001
    0x40, // - 0b01000000
};

void main(void)
{
	// Set the output pins.
	for (int t = 10; t <= 13; t++) {
		gpio_set_output(t);
	}
	for (int t = 20; t <= 26; t++) {
		gpio_set_output(t);
	}

	// Set 1 to the GPIO 13 pin to display 
	// on the last digit.
	gpio_write(GPIO_PIN13, 1);

	// Display the digits.
	for (int i = 0; ; i++) {
		displaydigit(i);
		// Delay a certain time.
		for (int c = DELAY; c != 0; c--) ;
    	if (i == 16) i = -1;
	}

}

void displaydigit(int value) {
	// Check if the value is valid.
	if (value < 0 || value > 16) return;

	// Display the value by each bit.
	int toDisplay =  digit[value];
	for (int i = 20; i <= 26; i++) {
		if (toDisplay & 0b1) {
			gpio_write(i, 1);
		} else {
			gpio_write(i, 0);
		}
		toDisplay = toDisplay >> 1;
	}
}