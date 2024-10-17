#include "game.h"
#include "ship.h"
#include "setup.h"
#include "attack.h"
#include "defend.h"
#include "winlose.h"

#include "system.h"
#include "tinygl.h"
#include <stdbool.h>

// Initialise the game state to begin in the SETUP phase and the game_turn.
game_state_t current_game_state = SETUP;
uint8_t game_turn = 1;
bool is_player1;
// Initialise the number of ship parts hit for the player and the opponent.
uint8_t player_parts_hit = 0;
uint8_t opponent_parts_hit = 0;


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







