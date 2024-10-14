#include "ship.h"
#include "system.h"
#include "tinygl.h"


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

void addShip(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation, uint8_t shipNum) 
{
    ship_t shipAdd = {.row = row, .col = col, .length = length, .orientation = orientation};
    ships[shipNum] = shipAdd;    
}


void addShipPart(uint8_t shipNum)
{
    ship_t ship = ships[shipNum];
    uint8_t index;
    ship_part_t shipPart;
    if (shipNum == 0) {
        /* code */
        index = 0;
        for (size_t i = 0; i < 2; i++) {
            if (ship.orientation == HORIZONTAL) {
                parts[i+index] = (ship_part_t){ship.row, ((ship.col)+i), false};
            } else {
                parts[i+index] = (ship_part_t){((ship.row)+i), ship.col, false};
            }
        }
    } else if (shipNum == 1) {
        index = 2;
        for (size_t i = 0; i < 3; i++) {
            if (ship.orientation == HORIZONTAL) {
                parts[i+index] = (ship_part_t){ship.row, ((ship.col)+i), false};
            } else {
                parts[i+index] = (ship_part_t){((ship.row)+i), ship.col, false};
            }
        }
    } else if (shipNum ==2) {
        index = 5;
        for (size_t i = 0; i < 4; i++) {
            if (ship.orientation == HORIZONTAL) {
                parts[i+index] = (ship_part_t){ship.row, ((ship.col)+i), false};
            } else {
                parts[i+index] = (ship_part_t){((ship.row)+i), ship.col, false};
            }
        }
    }
}

void drawAllShips(uint8_t shipN) 
{
    ship_t ship = ships[shipN];
    draw_ship(ship.row, ship.col, ship.length, ship.orientation);
}
void drawAllParts(uint8_t partN) 
{    
    ship_part_t part = parts[partN];
    tinygl_point_t point = {.x = part.col, .y = part.row};
    if (part.hit) {
        tinygl_draw_point(point, 1);
    } else {
        tinygl_draw_point(point, 1);
    }    
}
