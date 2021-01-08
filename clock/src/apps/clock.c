#include "gpio.h"
#include "timer.h"

#define DELAY 0x3f0000

void displaydigit(int value);
void displaytime(int value);
void displaydashes(void);

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

	// set the input pin
	gpio_set_input(2);

	// initial the time
	int ctime = 0;

	// Display the digits.
	while (1) {
		while (gpio_read(GPIO_PIN2) == 0) displaydashes();
		displaydashes();
		if (gpio_read(GPIO_PIN2) == 0) {
			while (gpio_read(GPIO_PIN2) == 0) {
				displaytime(0);
			};
			while (1) {
				displaytime(ctime);
				ctime++;
				if (ctime > 9999) ctime = 0;
				if (gpio_read(GPIO_PIN2) == 0) {
					ctime = 0;
					break;
				}
			}
		}
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

void displaydashes(void) {
	// Set a four-digit array.
	int digits[4];

	// If given -1, display four dashes.
	digits[0] = 16;
	digits[1] = 16;
	digits[2] = 16;
	digits[3] = 16;

	for (int i = 0; i < 4; i++) {
		gpio_write(10+i, 1);
		displaydigit(digits[i]);
		timer_delay_us(2500);
		gpio_write(10+i, 0);
	}
}

void displaytime(int value) {
	// Set a four-digit array.
	int digits[4];

	// If given -1, display four dashes.
	if (value == -1) {
		digits[0] = 16;
		digits[1] = 16;
		digits[2] = 16;
		digits[3] = 16;
	} else {
		digits[0] = (value - value % 1000) / 1000;
		digits[1] = value % 1000 / 100;
		digits[2] = value % 100 / 10;
		digits[3] = value % 10;
	}
	unsigned long start_time = timer_get_ticks();
	while ((timer_get_ticks() - start_time) / 1000000 == 0) {
		for (int i = 0; i < 4; i++) {
			gpio_write(10+i, 1);
			displaydigit(digits[i]);
			timer_delay_us(2500);
			gpio_write(10+i, 0);
		}	
	}
}