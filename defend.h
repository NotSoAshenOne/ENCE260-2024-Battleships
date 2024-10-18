/**
 * @file defend.h
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief The header file for the defend module.
 *
 * @defgroup Handles the defending functionality of the game.
 *
 * Handles receiving and confirming an attack with hit or miss.
 */

#ifndef DEFEND_H
#define DEFEND_H

#include "system.h"

/*
    Function to decode an ASCII character back into coordinates (x, y)
    Params:
            x: a pointer to the x co-ordinate received from IR transmission.
            y: a pointer to the y co-ordinate received from IR transmission.
            encoded_char: the char received from the IR transmission that has the encoded (x,y) co-ordinate pair.
*/
void decode_coordinate(uint8_t* x, uint8_t* y, char encoded_char);

/*
    The main defending phase within the game loop.
    Waits until it receives an encoded co-ordinate through the IR receiver then checks if that co-ordinate hits
    any of the player's ship parts. Then displays the current state of the player's ships with display_ships().
    Switches to the attacking phase when the player presses the button.
*/
void defend_phase(void);

/*
    Checks if any of the player's ship parts have been hit and then transmits
    either a '+' for a hit or a '-' for a miss.
    Params:
            x: the x co-ordinate of the position to check for a hit.
            y: the y co-ordinate of the position to check for a hit.
*/
void check_hit(uint8_t x, uint8_t y);

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
bool check_part_hit(uint8_t x, uint8_t y);

#endif // DEFEND_H