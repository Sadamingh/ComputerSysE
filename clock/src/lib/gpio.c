#include "gpio.h"

static volatile unsigned int *FSEL_BASE =  (unsigned int *)0x20200000;
static volatile unsigned int *SET_BASE  =  (unsigned int *)0x2020001c;
static volatile unsigned int *CLR_BASE  =  (unsigned int *)0x20200028;
static volatile unsigned int *LEV_BASE  =  (unsigned int *)0x20200034 ;

void gpio_init(void) {
}

void gpio_set_function(unsigned int pin, unsigned int function) {
	// If `pin` or `function` is invalid, does nothing.
	if (!(pin >= GPIO_PIN_FIRST && pin <= GPIO_PIN_LAST)) return;
	if (!(function >= GPIO_FUNC_INPUT && function <= GPIO_FUNC_ALT3)) return; 

	// Get the FSEL based on the pin.
	volatile unsigned int *FSEL = FSEL_BASE + (pin / 10);

	// Settings foar other pins should be unchanged. 
	// Use a mask to clear the set value.
	int offset = (pin % 10) * 3;
	*FSEL = *FSEL & ~(0b111 << offset);

	// Set a GPIO function for GPIO pin number `pin`.
	*FSEL = *FSEL | (function << offset);
}

unsigned int gpio_get_function(unsigned int pin) {
	// If `pin` is invalid, returns GPIO_INVALID_REQUEST.
	if (!(pin >= GPIO_PIN_FIRST && pin <= GPIO_PIN_LAST)) return GPIO_INVALID_REQUEST;

	// Get the FSEL and offset based on the pin.
	volatile unsigned int *FSEL = FSEL_BASE + (pin / 10);
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
	// If `pin` is invalid, does nothing.
	if (!(pin >= GPIO_PIN_FIRST && pin <= GPIO_PIN_LAST)) return;

	// Get the offset based on the pin.
	int offset = pin % 32;

	// Find out whether to set or to clear and then assign the value.
	if (value) {
		volatile unsigned int *reg = SET_BASE + (pin / 32);
		// Set the level value for GPIO pin number `pin`.
		*reg = (1 << offset);
	}
	else {
		volatile unsigned int *reg = CLR_BASE + (pin / 32);
		// Set the level value for GPIO pin number `pin`.
		*reg = (1 << offset);
	}
}

unsigned int gpio_read(unsigned int pin) {
	// If `pin` is invalid, returns GPIO_INVALID_REQUEST.
	if (!(pin >= GPIO_PIN_FIRST && pin <= GPIO_PIN_LAST)) return GPIO_INVALID_REQUEST;

	// Get the LEV registor and offset based on the pin.
	volatile unsigned int *LEV = LEV_BASE + (pin / 32);
	int offset = pin % 32;

	// Return current level (1 for high, 0 for low) for GPIO pin.
	return (*LEV >> offset) & 0b1;
}