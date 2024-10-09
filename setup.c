// setup.c
#include "setup.h"
#include "game.h"
#include "system.h"
#include "pio.h"
#include "tinygl.h"
#include "pacer.h"

void setup_phase(void)
{
    // Example usage: Draw a ship of length 3 centered at row 3, column 2
    draw_ship(3, 2, 4, VERTICAL);
}