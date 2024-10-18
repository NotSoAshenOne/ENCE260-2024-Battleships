/**
 * @file game.h
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief The header file for the game module.
 *
 * @defgroup Handles the main game loop of the game.
 *
 * Handles the game loop and state changing.
 */

#ifndef GAME_H
#define GAME_H

#define START '*'
#define HIT '+'
#define MISS '-'

#include <stdint.h>

/*
    Defines the phases for the main game loop.
 */
typedef enum {
    SETUP,
    ATTACK,
    DEFEND,
    WINLOSE
} game_state_t;

// Initialises the global variable for the game phase state.
extern game_state_t current_game_state;
// Initialises the global counters for the parts hit.
extern uint8_t player_parts_hit;
extern uint8_t opponent_parts_hit;
// Initialises the global counter for the game turn.
extern uint8_t game_turn;

/*
    The main game loop. Checks the current_game_state and then calls the respective phase method
    then changes to the next state.
*/
void game_loop(void);

#endif // GAME_H