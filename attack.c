#include "attack.h"
#include <stdint.h>
#include "ir_uart.h"
#include "tinygl.h"


void attack_phase(void)
{
    while (1) {
        button_update();
    
        if (button_push_event_p(0)) {
            led_set(LED1, 1);
            // Broadcast the coordinate until a character is received
            while (!ir_uart_read_ready_p()) {
                send_coordinate(2, 3);
            }
            
            // Extract the received character
            char received_char = ir_uart_getc();
            
            // Determine if it's a hit or a miss
            if (received_char == '+') {
                led_init();
                tinygl_draw_char('H', tinygl_point(0, 0));
            } else if (received_char == '-') {
                tinygl_draw_char('M', tinygl_point(0, 0));
            } 
            led_set(LED1, 0);
            tinygl_update();
            break; // Exit the loop once a character is received and processed
        }
    }
}

// Function to encode coordinates (x, y) into a single ASCII character
char encode_coordinate(uint8_t x, uint8_t y) {
    return 'a' + (y * 5 + x);
}

void send_coordinate(uint8_t x, uint8_t y)
{  
    char ch = encode_coordinate(x, y);
    ir_uart_putc (ch);
}