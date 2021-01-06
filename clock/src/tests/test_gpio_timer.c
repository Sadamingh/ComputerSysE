#include "assert.h"
#include "gpio.h"
#include "timer.h"

void test_gpio_set_get_function(void) {
    gpio_init();

    // Test get pin function (pin2 defaults to input)
    assert( gpio_get_function(GPIO_PIN2) == GPIO_FUNC_INPUT );

    // Test set pin to output
    gpio_set_output(GPIO_PIN2);

    // Test get pin function after setting
    assert( gpio_get_function(GPIO_PIN2) == GPIO_FUNC_OUTPUT );

    // Confirm setting a GPIO pin to alternate function modes, 
    // not just input or output
    // test 1
    gpio_set_function(GPIO_PIN2, GPIO_FUNC_INPUT);
    assert( gpio_get_function(GPIO_PIN2) == GPIO_FUNC_INPUT );
    // test 2
    gpio_set_function(GPIO_PIN2, GPIO_FUNC_ALT5);
    assert( gpio_get_function(GPIO_PIN2) == GPIO_FUNC_ALT5 );
    // test 3
    gpio_set_function(GPIO_PIN2, GPIO_FUNC_ALT0);
    assert( gpio_get_function(GPIO_PIN2) == GPIO_FUNC_ALT0 );
    // test 4
    gpio_set_function(GPIO_PIN2, GPIO_FUNC_ALT3);
    assert( gpio_get_function(GPIO_PIN2) == GPIO_FUNC_ALT3 );

    // Confirm can configure a GPIO pin in each of the different
    // FSEL registers
    gpio_set_output(GPIO_PIN12);
    assert( gpio_get_function(GPIO_PIN12) == GPIO_FUNC_OUTPUT );

    gpio_set_output(GPIO_PIN22);
    assert( gpio_get_function(GPIO_PIN22) == GPIO_FUNC_OUTPUT );

    gpio_set_output(GPIO_PIN32);
    assert( gpio_get_function(GPIO_PIN32) == GPIO_FUNC_OUTPUT );

    gpio_set_output(GPIO_PIN42);
    assert( gpio_get_function(GPIO_PIN42) == GPIO_FUNC_OUTPUT );

    gpio_set_output(GPIO_PIN52);
    assert( gpio_get_function(GPIO_PIN52) == GPIO_FUNC_OUTPUT );

    // Confirm no interference when configuring multiple GPIO 
    // pins within the same FSEL register
    gpio_set_output(GPIO_PIN12);
    gpio_set_output(GPIO_PIN13);
    gpio_set_output(GPIO_PIN14);
    assert( gpio_get_function(GPIO_PIN12) == GPIO_FUNC_OUTPUT );
    assert( gpio_get_function(GPIO_PIN13) == GPIO_FUNC_OUTPUT );
    assert( gpio_get_function(GPIO_PIN14) == GPIO_FUNC_OUTPUT );

    // Confirm that improper requests are gracefully handled
    assert( gpio_get_function(70) == GPIO_INVALID_REQUEST );
    assert( gpio_get_function(-10) == GPIO_INVALID_REQUEST );

    // Random tests
    gpio_set_function(GPIO_PIN31, GPIO_FUNC_ALT5);
    gpio_set_function(GPIO_PIN24, GPIO_FUNC_ALT3);
    gpio_set_function(GPIO_PIN50, GPIO_FUNC_ALT2);
    assert( gpio_get_function(GPIO_PIN31) == GPIO_FUNC_ALT5 );
    assert( gpio_get_function(GPIO_PIN24) == GPIO_FUNC_ALT3 );
    assert( gpio_get_function(GPIO_PIN50) == GPIO_FUNC_ALT2 );
    gpio_set_function(GPIO_PIN11, GPIO_FUNC_ALT5);
    gpio_set_function(GPIO_PIN12, GPIO_FUNC_ALT3);
    gpio_set_function(GPIO_PIN13, GPIO_FUNC_ALT2);
    gpio_set_function(GPIO_PIN16, GPIO_FUNC_ALT4);
    gpio_set_function(GPIO_PIN17, GPIO_FUNC_OUTPUT);
    assert( gpio_get_function(GPIO_PIN11) == GPIO_FUNC_ALT5 );
    assert( gpio_get_function(GPIO_PIN12) == GPIO_FUNC_ALT3 );
    assert( gpio_get_function(GPIO_PIN13) == GPIO_FUNC_ALT2 );
    assert( gpio_get_function(GPIO_PIN16) == GPIO_FUNC_ALT4 );
    assert( gpio_get_function(GPIO_PIN17) == GPIO_FUNC_OUTPUT );

}

void test_gpio_read_write(void) {
    gpio_init();
    gpio_set_function(GPIO_PIN20, GPIO_FUNC_OUTPUT);

    // Test gpio_write low, then gpio_read
    gpio_write(GPIO_PIN20, 0);
    assert( gpio_read(GPIO_PIN20) ==  0 );gpio_set_function(GPIO_PIN31, GPIO_FUNC_ALT5);
    gpio_set_function(GPIO_PIN24, GPIO_FUNC_ALT3);
    gpio_set_function(GPIO_PIN50, GPIO_FUNC_ALT2);
    assert( gpio_get_function(GPIO_PIN31) == GPIO_FUNC_ALT5 );
    assert( gpio_get_function(GPIO_PIN24) == GPIO_FUNC_ALT3 );
    assert( gpio_get_function(GPIO_PIN50) == GPIO_FUNC_ALT2 );
    //many pins in same register
    gpio_set_function(GPIO_PIN11, GPIO_FUNC_ALT5);
    gpio_set_function(GPIO_PIN12, GPIO_FUNC_ALT3);
    gpio_set_function(GPIO_PIN13, GPIO_FUNC_ALT2);
    gpio_set_function(GPIO_PIN16, GPIO_FUNC_ALT4);
    gpio_set_function(GPIO_PIN17, GPIO_FUNC_OUTPUT);
    assert( gpio_get_function(GPIO_PIN11) == GPIO_FUNC_ALT5 );
    assert( gpio_get_function(GPIO_PIN12) == GPIO_FUNC_ALT3 );
    assert( gpio_get_function(GPIO_PIN13) == GPIO_FUNC_ALT2 );
    assert( gpio_get_function(GPIO_PIN16) == GPIO_FUNC_ALT4 );
    assert( gpio_get_function(GPIO_PIN17) == GPIO_FUNC_OUTPUT );

   // Test gpio_write high, then gpio_read
    gpio_write(GPIO_PIN20, 1);
    assert( gpio_read(GPIO_PIN20) ==  1 );
}

void test_timer(void) {
    timer_init();

    // Test timer tick count incrementing
    unsigned int start = timer_get_ticks();
    for( int i=0; i<10; i++ ) { /* Spin */ }
    unsigned int finish = timer_get_ticks();
    assert( finish > start );

    // Test timer delay
    int usecs = 100;
    start = timer_get_ticks();
    timer_delay_us(usecs);
    finish = timer_get_ticks();
    assert( finish >= start + usecs );
}

// Uncomment each call below when you have implemented the functions
// and are ready to test them

void main(void) {
    test_gpio_set_get_function();
    // test_gpio_read_write();
    // test_timer();
}
