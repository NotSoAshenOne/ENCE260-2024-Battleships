#include "pio.h"
#include "tinygl.h"
#include "pacer.h"
#include "navswitch.h"
#include "ship.h"
#include "game.h"
#include <stdbool.h>
#include "setup.h"

ship_t ships[MAX_SHIPS];
uint8_t ship_count = 0;

//void add_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation);
void update_ship(ship_t *ship, uint8_t row, uint8_t col);
void rotate_ship(ship_t *ship);

void setup_phase(void)
{
    tinygl_init(1000);
    navswitch_init();
    pacer_init(1000);

    //add_ship(3, 1, 3, VERTICAL);

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
            //ship->part[i] = (ship_part_t){row, col + i};
        }
    } else {
        for (int i = 0; i < ship->length; i++) {
            //ship->part[i] = (ship_part_t){row + i, col};
        }
    }
}

void rotate_ship(ship_t *ship) {
//     for (size_t i = 0; i < 9; i++) {
//         tinygl_point_t part = tinygl_point(parts[i].col, parts[i].row);
//         tinygl_draw_point(part, 1);
//     }
// }
    if (ship->orientation == HORIZONTAL) {
        ship->orientation = VERTICAL;
    } else {
        ship->orientation = HORIZONTAL;
    }
    update_ship(ship, ship->row, ship->col);
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

void placeShips() 
{
    bool isSelected;
    orientation_t ship_orientation;
    tinygl_point_t startPosition;
    uint8_t length;

    for (size_t i = 0; i < 3; i++) {
        isSelected = false; 
        ship_orientation = HORIZONTAL;
        startPosition = tinygl_point(2,3);
        length = (i+2);

        while (isSelected == false) {
            pacer_wait ();
            tinygl_update ();
            shipNavigation(&startPosition, &isSelected, length, &ship_orientation);    
        }

        addShip(startPosition.y, startPosition.x, length, ship_orientation, i);
        addShipPart(i);
    }
    startPosition = tinygl_point(2,3);
    isSelected = false; 
    uint8_t shipN = 0;
    uint8_t partN = 0;
    while (1) {
        //draw_ship((startPosition.y), (startPosition.x), 4, (ship_orientation));
        
        pacer_wait ();
        tinygl_update ();

        // drawAllShips();
        // drawAllParts(partN);
        navigation(&startPosition, &isSelected, shipN, partN);
        
        shipN = (shipN+1)%3;
        partN = (partN+1)%2;
        // drawAllParts();
    }
}