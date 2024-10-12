#include "defend.h"
#include "tinygl.h"
#include "ir_uart.h" // Include the header for ir_uart functions
#include "pacer.h"   // Include the header for pacer functions
#include <stdint.h>

uint8_t x = 0, y = 0;
uint8_t data = 0; // Initialize data to avoid undeclared variable error

// Function to decode an ASCII character back into coordinates (x, y)
void decode_coordinate(uint8_t* x, uint8_t* y, char encoded_char) {
    *y = (uint8_t)((encoded_char - 'a') / 5);
    *x = (uint8_t)((encoded_char - 'a') % 5);
}

void defend_phase(void)
{
    ir_uart_init();
    pacer_init(300);
    tinygl_init(1000);
    tinygl_clear();

    if (ir_uart_read_ready_p())
    {
        led_init();
        data = ir_uart_getc();
        decode_coordinate(&x, &y, data);
    }
    tinygl_point_t point = tinygl_point(x, y);
    // Use point variable to avoid unused variable warning
    tinygl_draw_point(point, 1);
    tinygl_update();
}