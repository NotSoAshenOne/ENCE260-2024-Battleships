
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

#define HANDSHAKE_CHAR '*'
#define TIMEOUT 1000 // Timeout value in milliseconds

bool handshake(void) {
    char received_char = '\0';
    bool is_device_1 = true;
    int timeout_counter = 0;

    while (1) {
        // Send handshake character
        ir_uart_putc(HANDSHAKE_CHAR);

        // Check if a character is received
        if (ir_uart_read_ready_p()) {
            received_char = ir_uart_getc();
            if (received_char == HANDSHAKE_CHAR) {
                is_device_1 = false; // This device becomes number 2
                break;
            }
        }

        // Increment the timeout counter
        timeout_counter++;
        if (timeout_counter > TIMEOUT) {
            is_device_1 = true; // This device becomes number 1
            break;
        }

        // Small delay to avoid busy-waiting (adjust as needed)
        pacer_wait();
    }

    // Confirm the role assignment
    if (is_device_1) {
        tinygl_draw_char('1', tinygl_point(0, 0));
        while (1) {
            pacer_wait();
            tinygl_update();
        }
    } else {
        tinygl_draw_char('2', tinygl_point(0, 0));
        while (1) {
            pacer_wait();
            tinygl_update();
        }
    }

    return is_device_1;
}

void setup_phase(void) {
    char received_char = ' ';
    placeShips();
    bool is_device_1 = handshake();
    // Use the is_device_1 variable as needed
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
        startPosition = tinygl_point(0,0);
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
