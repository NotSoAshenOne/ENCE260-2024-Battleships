#ifndef GAME_H
#define GAME_H

#define START '*';
#define HIT '+';
#define MISS '-';

#define remainingShips 5

#include <stdint.h>
#include "tinygl.h"
#include "ship.h"
#include <stdbool.h>

// tinygl_point_t navigation(void);
void navigation(tinygl_point_t* selectPosition, bool* isSelected, uint8_t shipN, uint8_t partN);
void shipNavigation(tinygl_point_t* selectPosition, bool* isSelected, uint8_t length, orientation_t* orientation, uint8_t shipN);

void drawAllShips(uint8_t shipN);

void setup_phase(void);

#endif // GAME_H