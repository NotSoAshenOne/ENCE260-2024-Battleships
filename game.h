#ifndef GAME_H
#define GAME_H

#define START '*';
#define HIT '+';
#define MISS '-';

#include <stdint.h>

typedef enum {
    SETUP,
    ATTACK,
    DEFEND,
    WINLOSE
} game_state_t;

extern game_state_t current_game_state;
extern uint8_t player_parts_hit;
extern uint8_t opponent_parts_hit;
extern uint8_t game_turn;

void game_loop(void);

#endif // GAME_H