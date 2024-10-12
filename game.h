#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "tinygl.h"
#include "ship.h"

// tinygl_point_t navigation(void);
void navigation(tinygl_point_t* selectPosition, bool* isSelected);
void shipNavigation(tinygl_point_t* selectPosition, bool* isSelected, uint8_t length, orientation_t orientation);

void setup_phase(void);

#endif // GAME_H