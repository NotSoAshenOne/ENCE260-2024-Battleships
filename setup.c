#include "pio.h"
#include "tinygl.h"
#include "pacer.h"
#include "game.h"

ship_t ships[MAX_SHIPS];
uint8_t ship_count = 0;

void setup_phase(void)
{
    // Add Ships to the game, The first parameter is the row, the second is the column, the third is the length of the ship, and the fourth is the orientation of the ship
    add_ship(3, 1, 3, VERTICAL);
    add_ship(1, 1, 2, HORIZONTAL);
    add_ship(5, 2, 4, VERTICAL);
    navswitch_init();
    tinygl_init(1000);
    tinygl_clear();

    for (uint8_t i = 0; i < ship_count; i++) {
        ship_t ship = ships[i];
        draw_ship(ship.row, ship.col, ship.length, ship.orientation);
    }

    tinygl_update();
    navswitch_update ();
}

void add_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation) {
    if (ship_count >= MAX_SHIPS) {
        // Handle error: too many ships
        return;
    }

    if (length < 1 || length > MAX_SHIP_LENGTH) {
        // Handle error: invalid ship length
        return;
    }

    ship_t ship = {row, col, length, orientation};

    if (orientation == HORIZONTAL) {
        int end_col = col + length - 1;

        if (end_col >= COLUMNS) {
            end_col = COLUMNS - 1;
            col = end_col - length + 1;
        }

        for (int i = 0; i < length; i++) {
            ship.parts[i] = (ship_part_t){row, col + i};
        }
    } else {
        int end_row = row + length - 1;

        if (end_row >= ROWS) {
            end_row = ROWS - 1;
            row = end_row - length + 1;
        }

        for (int i = 0; i < length; i++) {
            ship.parts[i] = (ship_part_t){row + i, col};
        }
    }

    ships[ship_count++] = ship;
}