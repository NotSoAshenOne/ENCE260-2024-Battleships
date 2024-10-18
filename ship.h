/**
 * @file ship.h
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief The header file for the ship module.
 *
 * @defgroup Handles the ship display functionality of the game.
 *
 * Handles ship definitions, display, and storing.
 * Defines the lengths of ships.
 */

#ifndef SHIP_H
#define SHIP_H

#include <stdint.h>
#include <stdbool.h>
#include "tinygl.h"

#define ROWS 7
#define COLUMNS 5
#define MAX_SHIPS 3
#define MAX_SHIP_PARTS 9
#define SHIP_ONE_LENGTH 2
#define SHIP_TWO_LENGTH 3
#define SHIP_THREE_LENGTH 4
#define WHILE_LOOPS 5

/*
    Defines the orientation of a ship.
 */
typedef enum {
    HORIZONTAL,
    VERTICAL
} orientation_t;

/*
    Defines the locations and hit status of ship parts.
 */
typedef struct {
    uint8_t row;
    uint8_t col;
    bool hit;
} ship_part_t;

/*
    Defines the location, length, and orientation of ships.
 */
typedef struct {
    uint8_t row;
    uint8_t col;
    uint8_t length;
    orientation_t orientation;
    bool sunk;
} ship_t;

// Initialise the global arrays for the player ships, parts and opponent parts.
extern ship_t ships[MAX_SHIPS];
extern ship_part_t parts[MAX_SHIP_PARTS];
extern ship_part_t opponent_parts[MAX_SHIP_PARTS];

/*
    Draws a ship to the on the matrix screen, checks if the ship is horizontal or vertical and then increments from the ship origin
    until it reaches the ship end as determined by the origin plus the length.
    Params:
            row: the row co-ordinate of the ship's origin.
            col: the column co-ordinate of the ship's origin.
            length: the length of the ship.
            orientation: the orientation of the ship.
*/
void draw_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation);

/*
    Adds a ship_t to the ships[] array.
    Params:
            row: the row co-ordinate of the ship's origin.
            col: the column co-ordinate of the ship's origin.
            length: the length of the ship.
            orientation: the orientation of the ship.
            ship_num: the ship number from 0, 1, 2.
*/
void add_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation, uint8_t ship_num);

/*
    Adds the individual parts of a ship to the parts matrix.
    Checks if the ship is horizontal or a vertical and increments the column and row values respectively.
    Know the length of each ship so the index is set to the next non-ship position.
    Params:
            ship_num: the ship number from 0, 1, 2 that the player will place.
*/
void add_ship_part(uint8_t ship_num);

/*
    Draws the given ship part from the parts[] array.
    Params:
            part_num: the part number from 0, 1, 2, 3, 4, 5, 6, 7, 8 parts in the parts[] array.
            round: the round of the loop, used to only show the hit parts sometimes to cause flashing on the led matrix.
*/
void draw_part(uint8_t part_num, uint8_t round);

/*
    Draws all the ships in the ships array using the draw_ship function.
    Used to draw all the ships during the ship placement phase.
    Params:
            ship_num: the ship number from 0,1,2 that the player placed.
 */
void draw_all_ships(uint8_t ship_num);

/*
    Calls draw_part while in a loop to draw all the ship_part_t in parts[] array to draw all the ships.
    Params:
            part_num: the part number from 0, 1, 2, 3, 4, 5, 6, 7, 8 parts in the parts[] array to be drawn.
            round: the round of the loop, used to only show the hit parts sometimes to cause flashing on the led matrix.
*/
void display_ships(uint8_t part_num, uint8_t round_num);

/*
    Loops through the opponent_parts[] array to draw all hit parts.
*/
void draw_hit_parts(void);

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
void ship_navigation(tinygl_point_t* select_position, bool* is_selected, uint8_t length, orientation_t* orientation, uint8_t ship_num);

#endif // SHIP_H