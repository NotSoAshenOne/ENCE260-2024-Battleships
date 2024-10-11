#include "pio.h"
#include "tinygl.h"
#include "pacer.h"
#include "navswitch.h"
#include "ship.h"
#include "game.h"

ship_t ships[MAX_SHIPS];
uint8_t ship_count = 0;

void add_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation);
void update_ship(ship_t *ship, uint8_t row, uint8_t col);
void rotate_ship(ship_t *ship);

void setup_phase(void)
{
    tinygl_init(1000);
    navswitch_init();
    pacer_init(1000);

    add_ship(3, 1, 3, VERTICAL);

    tinygl_clear();
    for (uint8_t i = 0; i < ship_count; i++) {
        ship_t ship = ships[i];
        draw_ship(ship.row, ship.col, ship.length, ship.orientation);
    }
    tinygl_update();

    tinygl_update();
    navswitch_update();
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        tinygl_clear();
        rotate_ship(&ships[ship_count - 1]);
    }
}

void update_ship(ship_t *ship, uint8_t row, uint8_t col) {
    ship->row = row;
    ship->col = col;

    if (ship->orientation == HORIZONTAL) {
        for (int i = 0; i < ship->length; i++) {
            ship->parts[i] = (ship_part_t){row, col + i};
        }
    } else {
        for (int i = 0; i < ship->length; i++) {
            ship->parts[i] = (ship_part_t){row + i, col};
        }
    }
}

void rotate_ship(ship_t *ship) {
    if (ship->orientation == HORIZONTAL) {
        ship->orientation = VERTICAL;
    } else {
        ship->orientation = HORIZONTAL;
    }
    update_ship(ship, ship->row, ship->col);
}

void add_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation) {
    // Don't need to have a handle for this. Can just specify the number of ships a player can have and then add them in a for loop.
    if (ship_count >= MAX_SHIPS) {
        // Handle error: too many ships

        return;
    }
    // Same as the other one, we probs don't need this if we specify the lengths when allowing the player to draw up the ships.
    if (length < 1 || length > MAX_SHIP_LENGTH) {
        // Handle error: invalid ship length
        return;
    }

    ship_t ship = {row, col, length, orientation, {{0, 0}}};
    // Could probably simplify by specifying the orientation they appear in as default and then the player can change.
    // Same as draw ship??
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