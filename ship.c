#include "ship.h"
#include "system.h"
#include "tinygl.h"
#include <stdbool.h>

/*
Initialisation of variables
*/
uint8_t ship_positions[ROWS][COLUMNS] = {0};
orientation_t ship_orientation = HORIZONTAL;

/*
Draws a ship to the on the matrix screen.
Checks if the ship is horizontal or vertical and then increments from the ship origin until it reaches the ship length.
*/
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

/*
Adds a ship_t to the ships array.
*/
void addShip(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation, uint8_t ship_num) 
{
    ship_t shipAdd = {.row = row, .col = col, .length = length, .orientation = orientation, .sunk = false};
    ships[ship_num] = shipAdd;    
}

/*
Adds the individual parts of a ship to the parts matrix.
Checks if the ship is horizontal or a vertical and increments the column and row values respectively.
params ship_num is the ship number from 0,1,2 that the player will place.
*/
void addShipPart(uint8_t ship_num)
{
    ship_t ship = ships[ship_num];
    uint8_t index;
    ship_part_t shipPart;
    if (ship_num == 0) {
        /* code */
        index = 0;
        for (size_t i = 0; i < 2; i++) {
            if (ship.orientation == HORIZONTAL) {
                parts[i+index] = (ship_part_t){ship.row, ((ship.col)+i), false};
            } else {
                parts[i+index] = (ship_part_t){((ship.row)+i), ship.col, false};
            }
        }
    } else if (ship_num == 1) {
        index = 2;
        for (size_t i = 0; i < 3; i++) {
            if (ship.orientation == HORIZONTAL) {
                parts[i+index] = (ship_part_t){ship.row, ((ship.col)+i), false};
            } else {
                parts[i+index] = (ship_part_t){((ship.row)+i), ship.col, false};
            }
        }
    } else if (ship_num ==2) {
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

/*
Draws all the ships in the ships array using the draw_ship function.
[Possibly redundant?] <- Used in the ship navigation.
 */
void drawAllShips(uint8_t shipN) 
{
    ship_t ship = ships[shipN];
    draw_ship(ship.row, ship.col, ship.length, ship.orientation);
}

/*
Draws all the parts in the parts array using tinygl.
Checks if a ship is hit and causes it to flash if it hit.
*/
void drawAllParts(uint8_t partN, uint8_t round) 
{   
    ship_part_t part = parts[partN];
    tinygl_point_t point = {.x = part.col, .y = part.row};
    if (part.hit == true) {
        tinygl_draw_point(point, 0);
        if (round%5 == 0) {     // Making it flash by only showing every 5 times through all the parts. Use the same number for % must be prime.
            tinygl_draw_point(point, 1);
        }
    } else {
        tinygl_draw_point(point, 1);
    }    
}

/*
Shows the parts of the ships on the screen to the user, lasts while the button is not pressed.
Uses drawAllParts function.
*/
void display_ships (void) 
{
    tinygl_clear();
    uint8_t roundN = 0;
    uint8_t partN = 0;
    bool isFinished = false;
    while (isFinished == false) {
        pacer_wait ();
        tinygl_update ();
        button_update();
        drawAllParts(partN, roundN);
        roundN = (roundN+1)%5;
        partN = (partN+1)%9;
        if (button_push_event_p (0)) {
            isFinished = true;
        }
    }
}
