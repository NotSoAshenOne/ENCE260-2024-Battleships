#include <stdint.h>

#include "attack.h"
#include "game.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"
#include <stdio.h>
#include <stdbool.h>

tinygl_point_t startPosition;

char received_char = ' ';

bool attack_phase(void)
{
    return selectAttack();
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

bool selectAttack(void) // Maybe want to pass through a pointer to a uint8_t partNum instead of local partN
{
    // tinygl_point_t selectPosition = tinygl_point(2,3);
    startPosition = tinygl_point(2,3);
    bool isSelected = false; 
    uint8_t shipN = 0;
    uint8_t partN = 0;
    while (isSelected == false) {
        //draw_ship((startPosition.y), (startPosition.x), 4, (ship_orientation));
        pacer_wait ();
        tinygl_update ();
        navigation(&startPosition, &isSelected, shipN, partN);
        //drawAllParts(partN);
        shipN = (shipN+1)%3;
        partN = (partN+1)%9;
    }
    attack_t attack = {.col = startPosition.x, .row = startPosition.y};
    uint8_t part_num;
    return check_part_hit(attack.col, attack.row, &part_num); // Made a bool checking if the attack was successful just while no multiplayer.
    // while (1) {
    //     tinygl_draw_point(tinygl_point(attack.col, attack.row), 1);
    // }
    
    
    // while(1) {
    //     // Broadcast the coordinate until a character is received
    //     while (1) {
    //         // Check if a character is ready to be received
    //         if (ir_uart_read_ready_p()) {
    //             // Extract the received character
    //             received_char = ir_uart_getc(); 
    //             // Check if the received character is '-' or '+'
    //             if (received_char == '-' || received_char == '+') {
    //                 break; // Exit the loop if '-' or '+' is received
    //             }
    //         }
    //         // Send the coordinate if the received character is not '-' or '+'
    //         send_coordinate(attack.col, attack.row);
    //     }
        
    //     // Is it a hit or a miss?
    //     if (received_char == '+') {
    //         led_set(LED1, 1);
    //     } else {
    //         led_set(LED1, 0);
    //     }
    //     break; // Exit the loop once a character is received and processed
    // }
}
