#ifndef GAME_H
#define GAME_H

#include <stdint.h>

#define ROWS 7
#define COLUMNS 5

extern uint8_t ship_positions[ROWS][COLUMNS];

void game_loop(void);

#endif // GAME_H