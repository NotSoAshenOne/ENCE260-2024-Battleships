/**
 * @file defend.c
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief This file contains the implementation of the defending phase in the game.
 * 
 * The defend phase includes functions for decoding and receiving attack coordinates,
 * as well as displaying the current state of the player's fleet.
 * 
 * The main functions include:
 * - decode_coordinate(): Decodes a single ASCII character into (x,y) co-ordinates.
 * - defend_phase(): Runs the main defending phase within the game loop.
 * - check_hit(): Transmits a '+' if a ship part was hit by the received attack and '-' if not.
 * - check_part_hit(): Loops through all the player's ship parts to see if the received co-ordinates match with any of the ship parts.
 * 
 * 
 * @note The file includes necessary headers used in the defend phase.
 */

#include <stdint.h>
#include <stdbool.h>
// Game modules
#include "defend.h"
#include "ship.h"
#include "game.h"
// Funkit drivers.
#include "tinygl.h"
#include "ir_uart.h"
#include "button.h"
#include "led.h"

// Initialise the (x,y) co-ordinates for IR receiving.
uint8_t x = 0, y = 0;

/*
    Function to decode an ASCII character back into coordinates (x, y)
    Params:
            x: a pointer to the x co-ordinate received from IR transmission.
            y: a pointer to the y co-ordinate received from IR transmission.
            encoded_char: the char received from the IR transmission that has the encoded (x,y) co-ordinate pair.
*/
void decode_coordinate(uint8_t* x, uint8_t* y, char encoded_char) 
{
    *y = (uint8_t)((encoded_char - 'a') / 5);
    *x = (uint8_t)((encoded_char - 'a') % 5);
}

/*
    The main defending phase within the game loop.
    Waits until it receives an encoded co-ordinate through the IR receiver then checks if that co-ordinate hits
    any of the player's ship parts. Then displays the current state of the player's ships with display_ships().
    Switches to the attacking phase when the player presses the button.
*/
void defend_phase(void)
{
    uint8_t data = 0;
    uint8_t round = 0;
    uint8_t part = 0;
    while(1) {
        button_update();
        tinygl_update();
        if (ir_uart_read_ready_p()) {
            led_init();
            data = ir_uart_getc();
            decode_coordinate(&x, &y, data);
            check_hit(x, y);
        }
        // display_ships(part, round);
        draw_part(part, round);
        round = (round+1)%5;
        part = (part+1)%MAX_SHIP_PARTS;
        if (button_push_event_p (0) && data != 0) {
            led_set(LED1, 1);
            current_game_state = ATTACK;
            break;
        }
    }
}

/*
    Checks if any of the player's ship parts have been hit and then transmits
    either a '+' for a hit or a '-' for a miss.
    Params:
            x: the x co-ordinate of the position to check for a hit.
            y: the y co-ordinate of the position to check for a hit.
*/
void check_hit(uint8_t x, uint8_t y) 
{
    if (check_part_hit(x, y)) {
        ir_uart_putc('+');
        led_set(LED1, 1);
    } else {
        ir_uart_putc('-');
    }
}

/*
    Loops through all of the player's ship parts and sees if the given (x,y) co-ordinates match with the
    (x,y) co-ordinates of the ship part. Then sets the part to be hit and increases the player_parts_hit counter if there is a match.
    Params:
            x: the x co-ordinate to check for a match.
            y: the y co-ordinate to check for a match.
            part: the pointer to the value of the part that has been hit.
    Returns:
            true: if the given (x,y) co-ordinates match a ship part.
            false: if there is no match.

*/
bool check_part_hit(uint8_t x, uint8_t y)
{
    for (size_t i = 0; i < MAX_SHIP_PARTS; i++) {
        if (parts[i].col == x && parts[i].row == y) {
            parts[i].hit = true;
            player_parts_hit++;
            return true;
        }
    }
    return false;
}