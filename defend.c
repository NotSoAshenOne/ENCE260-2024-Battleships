#include "defend.h"
#include "tinygl.h"
#include "ir_uart.h" // Include the header for ir_uart functions
#include "pacer.h"   // Include the header for pacer functions
#include <stdint.h>
#include <stdbool.h>
#include "ship.h"
#include "game.h"

// Initialise the (x,y) co-ordinates for IR receiving.
uint8_t x = 0, y = 0;
// Initialise the number of ships that have not been sunk.
uint8_t remaining_ships = 3;


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
        if (ir_uart_read_ready_p()) {
            led_init();
            data = ir_uart_getc();
            decode_coordinate(&x, &y, data);
            check_hit(x, y);
        }
        display_ships(part, round);
        round = (round+1)%5;
        part = (part+1)%9;
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
    uint8_t part_num;
    if (check_part_hit(x, y, &part_num)) {
        ir_uart_putc('+');
        led_set(LED1, 1);
    } else {
        ir_uart_putc('-');
    }
}

/*
    Loops through all of the player's ship parts and sees if the given (x,y) co-ordinates match with the
    (x,y) co-ordinates of the ship part. Then sets the part to be hit if there is a match.
    Params:
            x: the x co-ordinate to check for a match.
            y: the y co-ordinate to check for a match.
            part: the pointer to the value of the part that has been hit.
    Returns:
            true: if the given (x,y) co-ordinates match a ship part.
            false: if there is no match.

*/
bool check_part_hit(uint8_t x, uint8_t y, uint8_t* part)
{
    for (size_t i = 0; i < MAX_SHIP_PARTS; i++) {
        if (parts[i].col == x && parts[i].row == y) {
            parts[i].hit = true;
            (*part) = i;
            player_parts_hit++;
            return true;
        }
    }
    return false;
}

/*
    Checks if a player's ship has been sunk. Checks the other ship parts in the ship decided by the part_num of the given part.
    Params:
            part_num: a pointer to the number of the part that has been hit.
    Returns:
            true: if all the parts in a ship have been hit.
            false: if not all the parts in a ship have been hit.
*/
bool check_ship_sunk(uint8_t* part_num) 
{
    if ((*part_num) < 2) {
        if (parts[0].hit == true && parts[1].hit == true) {
            ships[0].sunk = true;
            remaining_ships += -1;
            return true;
        }
    } else if ((*part_num) >= 2 && (*part_num) < 5) {
        if (parts[2].hit == true && parts[3].hit == true && parts[4].hit == true) {
            ships[1].sunk = true;
            remaining_ships += -1;
            return true;
        }
    } else if ((*part_num) >= 5) {
        if (parts[5].hit == true && parts[6].hit == true && parts[7].hit == true && parts[8].hit == true) {
            ships[2].sunk = true;
            remaining_ships += -1;
            return true;
        }
    }
    return false;
}

/*
    Loops through parts[] to check if all the ship parts have been hit.
    Returns:
            true: if all ship parts have been hit.
            false: if not every ship part has been hit.
*/
bool all_parts_sunk(void) 
{
    bool all_sunk = true; // Do we need this? Can just have return true at the end as the false will leave the method.
    for (size_t i = 0; i <MAX_SHIP_PARTS; i++) {
        if (parts[i].hit == false) {
            return false;
        }
    }
    return all_sunk;
}