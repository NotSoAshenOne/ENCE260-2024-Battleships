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
#include "ship.h"
// Funkit Drivers
#include "tinygl.h"
#include "button.h"

/*
    The main loop for the win / lose phase within the game loop. Checks if a win and then draws a 'W' for a win and 'L' for loss.
    Params:
            win: a boolean stating if the player won.
*/
void winlose_phase(bool win)
{
    // char c = ' ';
    if (win) {
        // c = 'W';
        tinygl_draw_char('W',tinygl_point (0, 0));
    } else {
        // c = 'L';
        tinygl_draw_char('L',tinygl_point (0, 0));
    }
    // if (c == 'W') {
    //     tinygl_draw_char('W',tinygl_point (0, 0));
    // } else if (c == 'L') {
    //     tinygl_draw_char('L',tinygl_point (0, 0));
    // } else {
    //     tinygl_draw_char(' ',tinygl_point (0, 0));
    // }
    tinygl_update ();
    if (button_push_event_p (0)) {
        current_game_state = SETUP;
        game_turn = 1;
        opponent_parts_hit = 0;
        player_parts_hit = 0;
    }
}