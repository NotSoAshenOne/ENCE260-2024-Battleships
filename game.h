#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "tinygl.h"

// tinygl_point_t navigation(void);
void navigation(tinygl_point_t* selectPosition, bool* isSelected);
void setup_phase(void);

#endif // GAME_H