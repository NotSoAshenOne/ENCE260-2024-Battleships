/**
 * @file ship.c
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief This file contains the implementation for the ships in the game.
 * 
 * Controls the functionality of the ships. Handles the display and creation of the ships.
 * 
 * The main functions include:
 * - draw_ship(): Draws a single ship on the LED matrix from a given ship origin point.
 * - add_ship(): Adds a ship to the ships[] array.
 * - add_ship_part(): Adds a ship part to the player's parts[] array.
 * - draw_all_ships(): Draws all of the ships in the ship[] array using the draw_ship() function.
 * - draw_part(): Draws a single ship part from the parts[] array, making the part flash if it is hit.
 * - draw_hit_parts(): Draws the opponents parts that the player has hit.
 * - display_ships(): Draws the player's ships by drawing all the ship parts in the player's parts[] array. 
 * - ship_navigation(): Allows the player to move a ship around the screen to then place.
 * 
 * @note The file includes necessary headers and initialises global constants used for the ships in the game.
 */

// Game Modules
#include "ship.h"
#include "game.h"
// Funkit Drivers
#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "button.h"
#include "pacer.h"

/*
    Initialisation of variables
*/
uint8_t ship_positions[ROWS][COLUMNS] = {0};
orientation_t ship_orientation = HORIZONTAL;

/*
    Draws a ship to the on the matrix screen, checks if the ship is horizontal or vertical and then increments from the ship origin 
    until it reaches the ship end as determined by the origin plus the length.
    Params: 
            row: the row co-ordinate of the ship's origin.
            col: the column co-ordinate of the ship's origin.
            length: the length of the ship.
            orientation: the orientation of the ship.
*/
void draw_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation)
{
    // tinygl_init(1000);
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
    Adds a ship_t to the ships[] array.
    Params:
            row: the row co-ordinate of the ship's origin.
            col: the column co-ordinate of the ship's origin.
            length: the length of the ship.
            orientation: the orientation of the ship.
            ship_num: the ship number from 0, 1, 2.
*/
void add_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation, uint8_t ship_num) 
{
    ship_t ship_add = {.row = row, .col = col, .length = length, .orientation = orientation, .sunk = false};
    ships[ship_num] = ship_add;    
}

/*
    Adds the individual parts of a ship to the parts matrix.
    Checks if the ship is horizontal or a vertical and increments the column and row values respectively.
    Know the length of each ship so the index is set to the next non-ship position.
    Params:
            ship_num: the ship number from 0, 1, 2 that the player will place.
*/
void add_ship_part(uint8_t ship_num)
{
    ship_t ship = ships[ship_num];
    uint8_t index;
    if (ship_num == 0) {
        index = 0;
        for (size_t i = 0; i < SHIP_ONE_LENGTH; i++) {
            if (ship.orientation == HORIZONTAL) {
                parts[i+index] = (ship_part_t){ship.row, ((ship.col)+i), false};
            } else {
                parts[i+index] = (ship_part_t){((ship.row)+i), ship.col, false};
            }
        }
    } else if (ship_num == 1) {
        index = SHIP_ONE_LENGTH;
        for (size_t i = 0; i < SHIP_TWO_LENGTH; i++) {
            if (ship.orientation == HORIZONTAL) {
                parts[i+index] = (ship_part_t){ship.row, ((ship.col)+i), false};
            } else {
                parts[i+index] = (ship_part_t){((ship.row)+i), ship.col, false};
            }
        }
    } else if (ship_num == 2) {
        index = SHIP_ONE_LENGTH + SHIP_TWO_LENGTH;
        for (size_t i = 0; i < SHIP_THREE_LENGTH; i++) {
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
    Used to draw all the ships during the ship placement phase.
    Params: 
            ship_num: the ship number from 0,1,2 that the player placed.
 */
void draw_all_ships(uint8_t ship_num) 
{
    ship_t ship = ships[ship_num];
    draw_ship(ship.row, ship.col, ship.length, ship.orientation);
}

/*
    Draws the given ship part from the parts[] array.
    Params:
            part_num: the part number from 0, 1, 2, 3, 4, 5, 6, 7, 8 parts in the parts[] array.
            round: the round of the loop, used to only show the hit parts sometimes to cause flashing on the led matrix.
*/
void draw_part(uint8_t part_num, uint8_t round) 
{   
    ship_part_t part = parts[part_num];
    tinygl_point_t point = {.x = part.col, .y = part.row};
    if (part.hit == true) {
        tinygl_draw_point(point, 0);
        if (round%WHILE_LOOPS == 0) {     // Making it flash by only showing every 5 times through all the parts. Use the same number for % must be prime.
            tinygl_draw_point(point, 1);
        }
    } else {
        tinygl_draw_point(point, 1);
    }    
}

/*
    Loops through the opponent_parts[] array to draw all hit parts.
*/
void draw_hit_parts(void)
{
    for (size_t i = 0; i < opponent_parts_hit; i++) {
            tinygl_draw_point(tinygl_point(opponent_parts[i].col, opponent_parts[i].row), 1);
        }
}

/*
    Calls draw_part while in a loop to draw all the ship_part_t in parts[] array to draw all the ships.
    Params:
            part_num: the part number from 0, 1, 2, 3, 4, 5, 6, 7, 8 parts in the parts[] array to be drawn.
            round: the round of the loop, used to only show the hit parts sometimes to cause flashing on the led matrix.
*/
void display_ships (uint8_t part_num, uint8_t round_num) 
{
     pacer_wait ();
     tinygl_update ();
     draw_part(part_num, round_num);
}

/*
    Controls the navigation of the ships on the screen during the setup phase by using the navswitch, allows the movement and rotation of the ships.
    Checks if the final part of the ship has reached the edge of the matrix screen and if it has then sends the other end of the ship to the other edge of the screen.
    Then displays the ships that have previously been placed.
    Params:
            select_position: the pointer to the position of the cursor.
            is_selected: the pointer to the bool stating if the cursor position has been selected.
            length: the length of the ship to be navigated around the screen.
            orientation: the pointer to the orientation of the ship displayed.
            ship_num: the previously placed ship to be displayed on the matrix screen.            
*/
void ship_navigation(tinygl_point_t* select_position, bool* is_selected, uint8_t length, orientation_t* orientation, uint8_t ship_num) 
{
        tinygl_clear ();
        navswitch_update ();
        button_update ();
        if (button_push_event_p (0)) {
            if ((*orientation) == HORIZONTAL) {
                if (select_position->y >(ROWS-length)) { 
                    select_position->y = (ROWS-length);
                }
                (*orientation) = VERTICAL;
            } else {
                if (select_position->x > (COLUMNS-length)) {
                    select_position->x = (COLUMNS-length);
                }
                (*orientation) = HORIZONTAL;
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (*orientation == VERTICAL) {
                if (select_position->y == 0) {
                    select_position->y = (ROWS-length);
                } else {
                    select_position->y += -1;
                }
            } else {
                if (select_position->y == 0) {
                    select_position->y = (ROWS - 1);
                } else {
                    select_position->y += -1;
                }
            }
        } 
        else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (*orientation == VERTICAL) {
                if (select_position->y == (ROWS-length)) {
                    select_position->y = 0;
                } else {
                    select_position->y += 1;
                }
            } else {
                if (select_position->y == (ROWS - 1)) {
                    select_position->y = 0;
                } else {
                    select_position->y += 1;
                }
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            if (*orientation == HORIZONTAL) {
                if (select_position->x == (COLUMNS-length)) {
                    select_position->x = 0;
                } else {
                    select_position->x += 1;
                }
            } else {
                if (select_position->x == (COLUMNS - 1)) {
                select_position->x = 0;
                } else {
                select_position->x += 1;
                }
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            if (*orientation == HORIZONTAL) {
                if (select_position->x == 0) {
                    select_position->x = (COLUMNS - length);
                } else {
                    select_position->x += -1;
                }
            } else {
                if (select_position->x == 0) {
                select_position->x = (COLUMNS - 1);
                } else {
                select_position->x += -1;
                }
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            (*is_selected) = true;
        }
        draw_ship((select_position->y),(select_position->x), length, (*orientation));
        if (ship_num != MAX_SHIPS) {
            draw_all_ships(ship_num);
        }
}