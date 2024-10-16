#include <stdint.h>

#include "attack.h"
#include "game.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"
#include <stdio.h>
#include <stdbool.h>

// Initialise the starting position.
tinygl_point_t start_position;
// Initialise the received char for IR interaction.
char received_char = ' ';

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
    ir_uart_putc (ch);
}

/*
    Displays a pointer on the screen which then can be controlled through the navigation() function.
    Once the player selects a point then it is transmitted until another character is received, that
    character is then checked and if it is '-' or '+' then the IR transmission is ended.
*/
void select_attack(void) // Maybe want to pass through a pointer to a uint8_t partNum instead of local partN
{
    start_position = tinygl_point(2,3);
    bool is_selected = false; 
    while (is_selected == false) {
        pacer_wait ();
        tinygl_update ();
        navigation(&start_position, &is_selected);
        //drawAllParts(partN);
    }
    attack_t attack = {.col = start_position.x, .row = start_position.y}; // <- Do we need this? Can't we just use start_position?
    while(1) {
        led_set(LED1, 0);
        // Broadcast the coordinate until a character is received
        while (1) {
            // Check if a character is ready to be received
            if (ir_uart_read_ready_p()) {
                // Extract the received character
                received_char = ir_uart_getc(); 
                // Check if the received character is '-' or '+'
                if (received_char == '-' || received_char == '+') {
                    led_set(LED1, 1);
                    if (received_char == '+') {
                        opponent_parts--;
                    }
                    break; // Exit the loop if '-' or '+' is received
                }
            }
            // Send the coordinate if the received character is not '-' or '+'
            send_coordinate(attack.col, attack.row);
            pacer_wait();
        }
        break; // Exit the loop once a character is received and processed
    }
}
