// game.h
#ifndef GAME_H
#define GAME_H

#include <stdint.h>

#define ROWS 7
#define COLUMNS 5

typedef enum {
    HORIZONTAL,
    VERTICAL
} orientation_t;

extern uint8_t ship_positions[ROWS][COLUMNS];

void game_loop(void);
void setup_phase(void);
void draw_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation);

#endif // GAME_H