#include <stdint.h>

#include "attack.h"
#include "game.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    SINGLE,
    AREA,
    TORPEDO
} attack_type_t;

// Initialise the starting position.
tinygl_point_t start_position;
// Initialise the received char for IR interaction.
char received_char = ' ';

ship_part_t opponent_parts[MAX_SHIP_PARTS];

/*
    Runs the main attacking phase within the game loop.
    Calls the select_attack() method and then changes the game state to the next defending phase.
*/
void attack_phase(void)
{
    select_attack();
    current_game_state = DEFEND;
}

/*
    Function to encode co-ordinates (x, y) into a single ASCII character
    Params: 
            x: the x co-ordinate to be encoded.
            y: the y co-ordinate to be encoded.
    Returns:
            The encoded co-ordinate.
*/
char encode_coordinate(uint8_t x, uint8_t y) 
{
    return 'a' + (y * 5 + x);
}

/*
    Function encodes an (x,y) co-ordinate pair and then transmits them with the IR transmitter.
    Params:
            x: the x co-ordinate to be encoded and transmitted.
            y: the y co-ordinate to be encoded and transmitted.
*/
void send_coordinate(uint8_t x, uint8_t y)
{  
    char ch = encode_coordinate(x, y);
    if (ir_uart_write_ready_p()) {
        ir_uart_putc (ch);
    }
}

/*
    Displays a pointer on the screen which then can be controlled through the navigation() function.
    Once the player selects a point then it is transmitted until another character is received, that
    character is then checked and if it is '-' or '+' then the IR transmission is ended.
*/
void select_attack(void) // Maybe want to pass through a pointer to a uint8_t partNum instead of local partN
{
    attack_type_t attack_type = AREA; // <- Change this to the attack type selected by the player
    start_position = tinygl_point(2,3);
    bool is_selected = false; 
    while (is_selected == false) {
        if (attack_type == SINGLE) {
            tinygl_draw_point(start_position, 1);
        } else if (attack_type == AREA) {
            //Draw a 3x3 box around the start position
            tinygl_draw_box(tinygl_point(start_position.x - 1, start_position.y - 1), tinygl_point(start_position.x + 1, start_position.y + 1), 1);
        } else if (attack_type == TORPEDO) {
            //Take the start position, and on its column draw a line from top to bottom
            tinygl_draw_line(tinygl_point(start_position.x, 0), tinygl_point(start_position.x, 6), 1);
        }
        pacer_wait ();
        tinygl_update ();
        navigation(&start_position, &is_selected);
        for (size_t i = 0; i < opponent_parts_hit; i++) {
            tinygl_draw_point(tinygl_point(opponent_parts[i].col, opponent_parts[i].row), 1);
        }
    }
    attack_t attack = {.col = start_position.x, .row = start_position.y}; // <- Do we need this? Can't we just use start_position?
    // Broadcast the coordinate until a character is received
    // Check if a character is ready to be received
    send_coordinate(attack.col, attack.row);
    pacer_wait();
    while (1) {
        if (ir_uart_read_ready_p()) {
            // Extract the received character
            received_char = ir_uart_getc(); 
            // Check if the received character is '-' or '+'
            if (received_char == '-' || received_char == '+') {
                if (received_char == '+') {
                    led_set(LED1, 1);
                    opponent_parts[opponent_parts_hit] = (ship_part_t){attack.row, attack.col, true};
                    opponent_parts_hit++;
                }
                break;
            }
            
        }
    }
    // Send the coordinate if the received character is not '-' or '+'
}
