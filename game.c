#include "game.h"
#include "setup.h"
#include "attack.h"
#include "defend.h"
#include "winlose.h"

uint8_t ship_positions[ROWS][COLUMNS] = {0};

typedef enum {
    SETUP,
    ATTACK,
    DEFEND,
    WINLOSE
} GameState;

void game_loop(void)
{
    GameState state = SETUP;

    while (1)
    {
        switch (state)
        {
            case SETUP:
                setup_phase();
                state = ATTACK; // Transition to next state
                break;
            case ATTACK:
                attack_phase();
                state = DEFEND; // Transition to next state
                break;
            case DEFEND:
                defend_phase();
                state = WINLOSE; // Transition to next state
                break;
            case WINLOSE:
                winlose_phase();
                state = SETUP; // Restart or end game
                break;
        }
    }
}