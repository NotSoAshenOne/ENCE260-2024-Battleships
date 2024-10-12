#include "attack.h"
#include <stdint.h>
#include "ir_uart.h"
#include "tinygl.h"

char received_char = ' ';

void attack_phase(void)
{
    while (1) {
        button_update();
        if (button_push_event_p(0)) {
            // Broadcast the coordinate until a character is received
                while (1) {
                    // Check if a character is ready to be received
                    if (ir_uart_read_ready_p()) {
                        // Extract the received character
                        received_char = ir_uart_getc(); 
                        // Check if the received character is '-' or '+'
                        if (received_char == '-' || received_char == '+') {
                            break; // Exit the loop if '-' or '+' is received
                        }
                    }
                    // Send the coordinate if the received character is not '-' or '+'
                    send_coordinate(1, 4);
                }
            
            if (received_char == '+') {
                led_set(LED1, 1);
            } else {
                led_set(LED1, 0);
            }
            break; // Exit the loop once a character is received and processed
        } else {
            break;
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