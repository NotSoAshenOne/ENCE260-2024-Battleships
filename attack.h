/**
 * @file attack.h
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief The header file for the attack module.
 *
 * @defgroup Handles the attack functionality of the game.
 *
 * Handles selecting and sending an attack.
 */

#ifndef ATTACK_H
#define ATTACK_H

#include "system.h"
#include "tinygl.h"

/*
    Runs the main attacking phase within the game loop.
    Calls the send_attack() method and then changes the game state to the next defending phase.
*/
void attack_phase(void);

/*
    Runs the main attacking phase within the game loop.
    Calls the send_attack() method and then changes the game state to the next defending phase.
*/
char encode_coordinate(uint8_t x, uint8_t y);

/*
    Function encodes an (x,y) co-ordinate pair and then transmits them with the IR transmitter.
    Params:
            x: the x co-ordinate to be encoded and transmitted.
            y: the y co-ordinate to be encoded and transmitted.
*/
void send_coordinate(uint8_t x, uint8_t y);

/*
    Controls the cursor navigation and select by using the navswitch.
    Displays the cursor and moves it by updating the select_position value.
    Params:
            select_position: the pointer to the position of the cursor.
            is_selected: the pointer to the bool stating if the cursor position has been selected.
*/
void navigation(tinygl_point_t* selectPosition, bool* isSelected);

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
void add_attack_coordinate(int row, int col);
void send_attack (void);

#endif // ATTACK_H