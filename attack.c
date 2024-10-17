/**
 * @file attack.c
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief This file contains the implementation of the attack phase in the game.
 * 
 * The attack phase includes functions for encoding and sending attack coordinates,
 * as well as handling different types of attacks (SINGLE, AREA, TORPEDO).
 * 
 * The main functions include:
 * - add_attack_coordinate(): Adds an attack coordinate to the list of attack coordinates.
 * - attack_phase(): Runs the main attacking phase within the game loop.
 * - encode_coordinate(): Encodes (x, y) coordinates into a single ASCII character.
 * - send_coordinate(): Encodes and transmits (x, y) coordinates using the IR transmitter.
 * - send_attack(): Displays a pointer on the screen, allows the player to select a point, 
 *   and transmits the selected attack coordinates.
 * 
 * The file also defines the attack_type_t enum and the Coordinate struct.
 * 
 * @note The file includes necessary headers and defines constants and global variables 
 * used in the attack phase.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
// Game Modules
#include "attack.h"
#include "game.h"
#include "ship.h"
// Funkit Drivers
#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"
#include "led.h"
#include "navswitch.h"

#define MAX_ATTACKS 10

/*
    Defines the different attack types.
 */
typedef enum {
    SINGLE,
    AREA,
    TORPEDO
} attack_type_t;

/*
    Defines the Coordinate struct to store (column,row) co-ordinate pairs.
*/
typedef struct {
    int row;
    int col;
} Coordinate;

// Initialise the arrays for attacking and storing the successful hits.
Coordinate attack_coordinates[MAX_ATTACKS];
ship_part_t opponent_parts[MAX_SHIP_PARTS];
int attack_count = 0;
// Initialise the starting position.
tinygl_point_t start_position;
// Initialise the received char for IR interaction and the attack counter.
char received_char = ' ';

/**
 * This function adds a new attack coordinate specified by the row and column
 * parameters to the attack_coordinates array, provided that the current number
 * of attacks is less than the maximum allowed (MAX_ATTACKS). If the maximum
 * number of attacks has been reached, the function does nothing.
 *
 * Params:
 *      row: The row coordinate of the attack.
 *      col: The column coordinate of the attack.
 */
void add_attack_coordinate(int row, int col) {
    if (attack_count < MAX_ATTACKS) {
        attack_coordinates[attack_count].row = row;
        attack_coordinates[attack_count].col = col;
        attack_count++;
    }
}

/*
    Runs the main attacking phase within the game loop.
    Calls the send_attack() method and then changes the game state to the next defending phase.
*/
void attack_phase(void)
{
    led_set(LED1, 0);
    send_attack();
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
    Displays a pointer on the screen which then can be controlled through the navigation() function. Every third turn the pointer is replaced by 3x3 box area attack
    and every sixth turn it is replaced by a column 'torpedo' attack.
    Once the player selects a point then it is transmitted until another character is received, that
    character is then checked and if it is '-' or '+' then the IR transmission is ended.
    If the attack hits an opponent ship then the opponent_parts[] array and opponent_parts_hit counter are updated.
*/
void send_attack(void)
{
    uint8_t ir_sends = 0;
    attack_type_t attack_type = SINGLE;
    if (game_turn != 0 && game_turn % 3 == 0 && game_turn % 6 != 0) {
        attack_type = AREA;
    }else if (game_turn != 0 && game_turn % 6 == 0) {
        attack_type = TORPEDO;
    }

    start_position = tinygl_point(2,3);
    bool is_selected = false; 
    while (is_selected == false) {
        if (attack_type == SINGLE) {
            tinygl_draw_point(start_position, 1);
        } else if (attack_type == AREA) {
            tinygl_draw_box(tinygl_point(start_position.x - 1, start_position.y - 1), tinygl_point(start_position.x + 1, start_position.y + 1), 1);
        } else if (attack_type == TORPEDO) {
            tinygl_draw_line(tinygl_point(start_position.x, 0), tinygl_point(start_position.x, 6), 1);
        }
        pacer_wait ();
        tinygl_update ();
        navigation(&start_position, &is_selected);
        draw_hit_parts();
    }

    if (attack_type == SINGLE) {
        add_attack_coordinate(start_position.y, start_position.x);
        ir_sends = 1;
    } else if (attack_type == AREA) {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                add_attack_coordinate(start_position.y + i, start_position.x + j);
                ir_sends++;
            }
        }
    } else if (attack_type == TORPEDO) {
        for (int i = 0; i < 7; i++) {
            add_attack_coordinate(i, start_position.x);
            ir_sends++;
        }
    }

    for (uint8_t i = 0; i < ir_sends; i++) {
        send_coordinate(attack_coordinates[i].col, attack_coordinates[i].row);
        while (1) {
            if (ir_uart_read_ready_p()) {
                received_char = ir_uart_getc(); 
                if (received_char == '-' || received_char == '+') {
                    if (received_char == '+') {
                        opponent_parts[opponent_parts_hit] = (ship_part_t){attack_coordinates[i].row, attack_coordinates[i].col, true};
                        opponent_parts_hit++;
                    }
                    break;
                }
                
            }
        }
    }
    attack_count = 0;
}

/*
    Controls the cursor navigation and select by using the navswitch.
    Displays the cursor and moves it by updating the select_position value.
    Params:
            select_position: the pointer to the position of the cursor.
            is_selected: the pointer to the bool stating if the cursor position has been selected.
*/
void navigation(tinygl_point_t* select_position, bool* is_selected) 
{
        tinygl_clear ();
        navswitch_update ();
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (select_position->y == 0) {
                select_position->y = 6;
            } else {
                select_position->y += -1;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (select_position->y == 6) {
                select_position->y = 0;
            } else {
                select_position->y += 1;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            if (select_position->x == 4) {
                select_position->x = 0;
            } else {
                select_position->x += 1;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            if (select_position->x == 0) {
                select_position->x = 4;
            } else {
                select_position->x += -1;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            (*is_selected) = true;
        }
        tinygl_draw_point((*select_position), 1); 
}