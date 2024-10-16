#include "defend.h"
#include "tinygl.h"
#include "ir_uart.h" // Include the header for ir_uart functions
#include "pacer.h"   // Include the header for pacer functions
#include <stdint.h>
#include <stdbool.h>
#include "ship.h"
#include "game.h"

uint8_t x = 0, y = 0;
uint8_t data = 0; // Initialize data to avoid undeclared variable error
uint8_t remaining_ships = 3;

// Function to decode an ASCII character back into coordinates (x, y)
void decode_coordinate(uint8_t* x, uint8_t* y, char encoded_char) {
    *y = (uint8_t)((encoded_char - 'a') / 5);
    *x = (uint8_t)((encoded_char - 'a') % 5);
}

void defend_phase(void)
{
    uint8_t roundN = 0;
    uint8_t partN = 0;
    // tinygl_clear();
    while(1) {
        button_update();
        if (ir_uart_read_ready_p())
        {
            led_init();
            data = ir_uart_getc();
            decode_coordinate(&x, &y, data);
            check_hit(x, y);
        }
        // tinygl_point_t point = tinygl_point(x, y);
        // Use point variable to avoid unused variable warning
        // tinygl_draw_point(point, 1);
        // tinygl_update();
        led_set(LED1, 0);
        // pacer_wait ();
        // tinygl_update ();
        // button_update();
        // drawAllParts(partN, roundN);
        display_ships(partN, roundN);
        roundN = (roundN+1)%5;
        partN = (partN+1)%9;
        // display_ships();
        if (button_push_event_p (0)) {
            //isFinished = true;
            current_game_state = ATTACK;
            break;
        }
    }
}

void check_hit(uint8_t x, uint8_t y) {
    uint8_t partNum;
    if (check_part_hit(x, y, &partNum)) {
        ir_uart_putc('+');
        led_set(LED1, 1);
    } else {
        ir_uart_putc('-');
    }
}

bool check_part_hit(uint8_t x, uint8_t y, uint8_t* partNum)
{
    for (size_t i = 0; i < MAX_SHIP_PARTS; i++) {
        if (parts[i].col == x && parts[i].row == y) {
            parts[i].hit = true;
            (*partNum) = i;
            return true;
        }
    }
    return false;
}

bool check_ship_sunk(uint8_t* partNum) 
{
    if ((*partNum) < 2) {
        if (parts[0].hit == true && parts[1].hit == true) {
            ships[0].sunk = true;
            remaining_ships += -1;
            return true;
        }
    } else if ((*partNum) >= 2 && (*partNum) < 5) {
        if (parts[2].hit == true && parts[3].hit == true && parts[4].hit == true) {
            ships[1].sunk = true;
            remaining_ships += -1;
            return true;
        }
    } else if ((*partNum) >= 5) {
        if (parts[5].hit == true && parts[6].hit == true && parts[7].hit == true && parts[8].hit == true) {
            ships[2].sunk = true;
            remaining_ships += -1;
            return true;
        }
    }
    return false;
}

// void ship_sunk (uint8_t* shipNum) 
// {
//     // send ship sunk to other funkit.
// }

void all_ships_sunk(void) 
{
    if (remaining_ships == 0) {
        // Send win lose
    }
}

/*
Checks if all the ship_parts have been hit.
Using while the all ships is not implemented.
Returns a bool, true if all sunk and false if not.
*/
bool all_parts_sunk(void) {
    bool all_sunk = true;
    for (size_t i = 0; i <MAX_SHIP_PARTS; i++) {
        if (parts[i].hit == false) {
            return false;
        }
    }
    return all_sunk;
}