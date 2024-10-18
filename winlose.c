/**
 * @file winlose.c
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief This file contains the implementation for the win / lose phase within the game loop.
 * 
 * Handles the display of 'W' for a win and 'L' for a loss.
 * 
 * The main functions include:
 * - winlose_phase(): Runs the main loop for the win / lose phase of the game. Checks for a win or loss then displays 'W' or 'L'.
 * 
 * @note The file includes necessary headers for the win / lose phase of the game.
 */

// Game Modules
#include "winlose.h"
#include "game.h"
// Funkit Drivers
#include "tinygl.h"
#include "button.h"

/*
    The main loop for the win / lose phase within the game loop. Checks if a win and then draws a 'W' for a win and 'L' for loss.
    Player can then press the button to reset the game.
    Params:
            win: a boolean stating if the player won.
*/
void winlose_phase(bool win)
{
    if (win) {
        tinygl_draw_char('W',tinygl_point (0, 0));
    } else {
        tinygl_draw_char('L',tinygl_point (0, 0));
    }
    tinygl_update ();
    button_update();
    if (button_push_event_p (0)) {
        reset_game();
    }
}

/*
    Resets the game variables to the original value and sets the game state back to the setup phase.
 */
void reset_game(void)
{
    current_game_state = SETUP;
    game_turn = 1;
    opponent_parts_hit = 0;
    player_parts_hit = 0;
}