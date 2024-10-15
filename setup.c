
#include "tinygl.h"
#include "pacer.h"
#include "navswitch.h"
#include "ship.h"
#include "game.h"
#include "system.h"
#include "setup.h"

ship_t ships[MAX_SHIPS];
ship_part_t parts[MAX_SHIP_PARTS];
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
    if (ship->orientation == HORIZONTAL) {
        ship->orientation = VERTICAL;
    } else {
        ship->orientation = HORIZONTAL;
    }
    update_ship(ship, ship->row, ship->col);
}

void placeShips() 
{
    bool isSelected;
    orientation_t ship_orientation;
    
    uint8_t length;

    for (size_t i = 0; i < 3; i++) {
        isSelected = false; 
        ship_orientation = HORIZONTAL;
        startPosition = tinygl_point(2,3);
        length = (i+2);
        uint8_t shipN = 10;
        while (isSelected == false) {
            pacer_wait ();
            tinygl_update ();
            shipNavigation(&startPosition, &isSelected, length, &ship_orientation, shipN);
            if (i > 0) {
                shipN = (shipN+1)%i;   
            }
        }
        addShip(startPosition.y, startPosition.x, length, ship_orientation, i);
        addShipPart(i);
    }
}
