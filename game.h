#ifndef GAME_H
#define GAME_H

#define START '*';
#define HIT '+';
#define MISS '-';

// #define remainingShips 3

#include <stdint.h>
#include "tinygl.h"
#include "ship.h"
#include <stdbool.h>

typedef struct {
    uint8_t row;
    uint8_t col;
} attack_t;

extern uint8_t remaining_ships;

// tinygl_point_t navigation(void);
void navigation(tinygl_point_t* selectPosition, bool* isSelected, uint8_t shipN, uint8_t partN);
void shipNavigation(tinygl_point_t* selectPosition, bool* isSelected, uint8_t length, orientation_t* orientation, uint8_t shipN);

void drawAllShips(uint8_t shipN);

void setup_phase(void);

#endif // GAME_H