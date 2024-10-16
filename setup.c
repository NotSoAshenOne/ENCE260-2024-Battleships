
#include "tinygl.h"
#include "pacer.h"
#include "navswitch.h"
#include "ship.h"
#include "game.h"
#include "system.h"
#include "setup.h"
#include <stdlib.h>
#include <avr/io.h>   

ship_t ships[MAX_SHIPS];
ship_part_t parts[MAX_SHIP_PARTS];
uint8_t ship_count = 0;
int count = 0;
bool is_device_1 = false;
char received = ' ';

//void add_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation);
void update_ship(ship_t *ship, uint8_t row, uint8_t col);
void rotate_ship(ship_t *ship);

#define HANDSHAKE_CHAR '*'
#define TIMEOUT 5000 // Timeout value in milliseconds


//Game Functionallity at start
handshake(void) {
    tinygl_clear();
    while (1) {
        button_update();
        //When a player pushes the navswitch button, they are deemed the defender, and the other player is the attacker 
        if (button_down_p(0)) {
            led_set(LED1, 1);
            ir_uart_putc(HANDSHAKE_CHAR);
            is_device_1 = false;
            break;
        } else if (ir_uart_read_ready_p() && ir_uart_getc() == HANDSHAKE_CHAR) {
            is_device_1 = true;
            break;
        }
    }
    return is_device_1;
}


void setup_phase(void) {
    placeShips();
    is_device_1 = handshake();
    if (is_device_1) {
        current_game_state = ATTACK;
    } else {
        current_game_state = DEFEND;
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
        start_position = tinygl_point(0,0);
        length = (i+2);
        uint8_t shipN = 10;
        while (isSelected == false) {
            pacer_wait ();
            tinygl_update ();
            ship_navigation(&start_position, &isSelected, length, &ship_orientation, shipN);
            if (i > 0) {
                shipN = (shipN+1)%i;   
            }
        }
        addShip(start_position.y, start_position.x, length, ship_orientation, i);
        addShipPart(i);
    }
}
