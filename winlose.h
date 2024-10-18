/**
 * @file winlose.h
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief The header file for the winlose module.
 *
 * @defgroup Handles the win / lose phase of the main game loop.
 *
 * Handles the display of the win status.
 */

#ifndef WINLOSE_H
#define WINLOSE_H

#include <stdbool.h>

/*
    The main loop for the win / lose phase within the game loop. Checks if a win and then draws a 'W' for a win and 'L' for loss.
    Player can then press the button to reset the game.
    Params:
            win: a boolean stating if the player won.
*/
void winlose_phase(bool win);

/*
    Resets the game variables to the original value and sets the game state back to the setup phase.
 */
void reset_game(void);

#endif // WINLOSE_H