/**
 * @file game.c
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief This file contains the implementation of the main game loop.
 * 
 * Loops through the main phases of the game, the setup phase, attacking phase, defending phase, and the win / lose phase.
 * 
 * The main functions include:
 * - main(): The main function that initialises the game loop.
 * - game_loop(): The main game loop. 
 * 
 * @note The file includes necessary headers and initialises global constants used within the game loop.
 */

// Game Modules
#include "game.h"
#include "ship.h"
#include "setup.h"
#include "attack.h"
#include "defend.h"
#include "winlose.h"
// Funkit Drivers
#include "system.h"
#include "ir_uart.h"
#include "button.h"
#include "led.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"
#include <stdbool.h>

// Initialise the game state to begin in the SETUP phase and the game_turn.
game_state_t current_game_state = SETUP;
uint8_t game_turn = 1;
bool is_player1;

// Initialise the number of ship parts hit for the player and the opponent.
uint8_t player_parts_hit = 0;
uint8_t opponent_parts_hit = 0;

// Initialize the PACER and TINYGL rates.
#define PACER_RATE 500
#define TINYGL_RATE 500

/*
 * This file contains the main function which initializes the system,
 * sets up the necessary peripherals, and starts the game loop.
*/
int main(void)
{
    system_init();
    ir_uart_init ();
    button_init ();

    pacer_init (PACER_RATE);

    tinygl_init (TINYGL_RATE);
    tinygl_font_set (&font5x7_1);

    led_init();
    led_set(LED1, 0);

    game_loop();
}


/*
    The main game loop. Checks the current_game_state and then calls the respective phase method 
    then changes to the next state.
*/
void game_loop(void)
{
    while (1)
    {
        if (current_game_state == SETUP) {
            setup_phase(&is_player1);
        } else if (current_game_state == ATTACK) {
            tinygl_clear();
            attack_phase();
            if (opponent_parts_hit == MAX_SHIP_PARTS) {
                current_game_state = WINLOSE;
            }
            if(!is_player1) {
                game_turn++;
            }
        } else if (current_game_state == DEFEND) {
            tinygl_clear();
            defend_phase();
            if (player_parts_hit == MAX_SHIP_PARTS) {
                current_game_state = WINLOSE;
            }
            if (is_player1) {
                game_turn++;
            }
        } else if (current_game_state == WINLOSE) {
            tinygl_clear();
            bool win;
            if (opponent_parts_hit == MAX_SHIP_PARTS) {
                win = true;
            } else {
                win = false;
            }
            winlose_phase(win);    
        }
    }
}







