#include "ship.h"
#include "game.h"
#include "setup.h"
#include "attack.h"
#include "defend.h"
#include "winlose.h"
#include "system.h"
#include "pio.h"
#include "tinygl.h"
#include "pacer.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"

uint8_t ship_positions[ROWS][COLUMNS] = {0};

orientation_t ship_orientation = HORIZONTAL;

void draw_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation)
{
    tinygl_init(1000);
    // Clear the display
    tinygl_clear();

    if (orientation == HORIZONTAL) {
        // Calculate the end point of the ship
        int end_col = col + length - 1;

        // Ensure the ship stays within the display bounds
        if (end_col >= COLUMNS) {
            end_col = COLUMNS - 1;
            col = end_col - length + 1;
        }

        // Draw the ship horizontally
        for (int i = 0; i < length; i++) {
            tinygl_draw_point(tinygl_point(col + i, row), 1);
        }
    } else {
        // Calculate the end point of the ship
        int end_row = row + length - 1;

        // Ensure the ship stays within the display bounds
        if (end_row >= ROWS) {
            end_row = ROWS - 1;
            row = end_row - length + 1;
        }

        // Draw the ship vertically
        for (int i = 0; i < length; i++) {
            tinygl_draw_point(tinygl_point(col, row + i), 1);
        }
    }
    // Update the display to reflect the changes
    tinygl_update();
}

void addShip(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation, uint8_t shipNum) {
    ship_t shipAdd = {.row = row, .col = col, .length = length, .orientation = orientation};
    ships[shipNum] = shipAdd;
}

// void add_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation, uint8_t shipNum) {
//     // Don't need to have a handle for this. Can just specify the number of ships a player can have and then add them in a for loop.
//     // if (ship_count >= MAX_SHIPS) {
//     //     // Handle error: too many ships
//     //     return;
//     // }
//     // Same as the other one, we probs don't need this if we specify the lengths when allowing the player to draw up the ships.
//     if (length < 1 || length > MAX_SHIP_LENGTH) {
//         // Handle error: invalid ship length
//         return;
//     }
//     if (orientation == HORIZONTAL) {
//         int end_col = col + length - 1;

//         if (end_col >= COLUMNS) {
//             end_col = COLUMNS - 1;
//             col = end_col - length + 1;
//         }

//         for (int i = 0; i < length; i++) {
//             ship_part_t shipPart = {.row=row, .col=col+i, .hit=false};
//             parts[shipNum+i] = shipPart;
//         }
//     } else {
//         int end_row = row + length - 1;

//         if (end_row >= ROWS) {
//             end_row = ROWS - 1;
//             row = end_row - length + 1;
//         }

//         for (int i = 0; i < length; i++) {
//             ship_part_t shipPart = {.row=row+1, .col=col, .hit=false};
//             parts[shipNum+i] = shipPart;
//         }
//     }
    
//     //ships[ship_count++] = ship;

// }
