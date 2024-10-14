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
void navigation(tinygl_point_t* selectPosition, bool* isSelected);
void shipNavigation(tinygl_point_t* selectPosition, bool* isSelected, uint8_t length, orientation_t* orientation);

void drawAllShips(void);
void setup_phase(void);

#endif // GAME_H