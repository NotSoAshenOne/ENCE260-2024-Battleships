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

void defend_phase(void);
void check_hit(uint8_t x, uint8_t y);
bool check_part_hit(uint8_t x, uint8_t y);

#endif // DEFEND_H