#include "gpio.h"

static volatile unsigned int *FSEL_BASE =  (unsigned int *)0x20200000;
//static volatile unsigned int *SET0  =  (unsigned int *)0x2020001c;
//static volatile unsigned int *CLR0  =  (unsigned int *)0x20200028;

void gpio_init(void) {
}

void gpio_set_function(unsigned int pin, unsigned int function) {
	// TODO: Your code goes here.
}

unsigned int gpio_get_function(unsigned int pin) {
	return 0;  // TODO: Your code goes here.
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