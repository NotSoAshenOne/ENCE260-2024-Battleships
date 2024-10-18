/**
 * @file attack.h
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief The header file for the setup module.
 *
 * @defgroup Handles the setup functionality of the game.
 *
 * Handles selecting players and placing ships.
 */

#ifndef SETUP_H
#define SETUP_H

tinygl_point_t start_position;

/*
    Initialises the players for the beginning of the game. If the player presses the button then sets the player to player1
    then if the button is not being pressed, the IR receiver checks for a character and if it receives then sets the player to player1
    Returns:
            is_device_1: a bool saying true if the player is set as device one or false if not.
*/
bool handshake(void);

/*
    Runs the main setup phase for the game, allows the player to place their ships then initialise the game.
    If the player is player1 then they will go to the attack phase otherwise the player will go to the defend phase.
    Params:
            is_player1: the pointer to the value denoting whether the player is player1 or not.
*/
void setup_phase(bool* is_player1);

/*
    Controls the placement of player ships. Loops through the ships and calls shipNavigation for each one.
    Once each is placed then it will add the ship to ships[] and then add the ship parts to the parts[] array.
*/
void place_ships (void);

#endif // SETUP_H