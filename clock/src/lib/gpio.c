#include "gpio.h"

static volatile unsigned int *FSEL_BASE =  (unsigned int *)0x20200000;
//static volatile unsigned int *SET0  =  (unsigned int *)0x2020001c;
//static volatile unsigned int *CLR0  =  (unsigned int *)0x20200028;

void gpio_init(void) {
}

void gpio_set_function(unsigned int pin, unsigned int function) {
	// If `pin` or `function` is invalid, does nothing.
	if (!(pin >= GPIO_PIN_FIRST && pin <= GPIO_PIN_LAST)) return;
	if (!(function >= GPIO_FUNC_INPUT && function <= GPIO_FUNC_ALT5)) return; 

	// Get the FSEL based on the pin.
	unsigned int *FSEL = (unsigned int *) (FSEL_BASE + (pin / 10) * 4);

	// Settings for other pins should be unchanged.
	volatile unsigned int temp = *FSEL;

	// Set a GPIO function for GPIO pin number `pin`.
	int offset = (pin % 10) * 3;
	*FSEL = temp | (function << offset);
}

unsigned int gpio_get_function(unsigned int pin) {
	// If `pin` is invalid, does nothing.
	if (!(pin >= GPIO_PIN_FIRST && pin <= GPIO_PIN_LAST)) return -1;

	// Get the FSEL and offset based on the pin.
	unsigned int *FSEL = (unsigned int *) (FSEL_BASE + (pin / 10) * 4);
	int offset = (pin % 10) * 3;

	// Return the function of the given pin.
	return (*FSEL >> offset) & 0b111;
}

void gpio_set_input(unsigned int pin) {
    gpio_set_function(pin, GPIO_FUNC_INPUT);
}

void gpio_set_output(unsigned int pin) {
    gpio_set_function(pin, GPIO_FUNC_OUTPUT);
}

void gpio_write(unsigned int pin, unsigned int value) {
    // TODO: Your code goes here.
}

unsigned int gpio_read(unsigned int pin) {
    return 0;  // TODO: Your code goes here.
}