#include "attack.h"
#include <stdint.h>
#include "ir_uart.h"
#include "tinygl.h"

void attack_phase(void)
{
    ir_uart_init ();
    tinygl_init(1000);
    pacer_init (300);

    send_coordinate(2, 3);
}

// Function to encode coordinates (x, y) into a single ASCII character
char encode_coordinate(uint8_t x, uint8_t y) {
    return 'a' + (y * 5 + x);
}

void send_coordinate(uint8_t x, uint8_t y)
{  
    char ch = encode_coordinate(x, y);
    ir_uart_putc (ch);

    tinygl_point_t point = tinygl_point(x, y);
    // Use point variable to avoid unused variable warning
    tinygl_draw_point(point, 1);
    tinygl_update();
}