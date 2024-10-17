#ifndef GAME_H
#define GAME_H

#define START '*';
#define HIT '+';
#define MISS '-';

#include <stdint.h>
#include "tinygl.h"
#include "ship.h"
#include <stdbool.h>

typedef struct {
    uint8_t row;
    uint8_t col;
} attack_t;

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
void navigation(tinygl_point_t* selectPosition, bool* isSelected);
void ship_navigation(tinygl_point_t* selectPosition, bool* isSelected, uint8_t length, orientation_t* orientation, uint8_t shipN);
void drawAllShips(uint8_t shipN);
// void setup_phase(void);

#endif // GAME_H