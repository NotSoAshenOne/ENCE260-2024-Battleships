/**
 * @file setup.c
 * @authors Morgan Lee (mle150) and Kaden Adlington (kad112)
 * @brief This file contains the implementation of the setup phase in the game.
 * 
 * Handles the initialisation of players, assigning player 1 and player 2. Also handles the placement of player ships on the board.
 * 
 * The main functions include:
 * - handshake(): Initialises the game by assigning player 1 and player 2.
 * - setup_phase(): Runs the main setup phase within the game.
 * - place_ships(): Allows the player to place three ships, of length 2, 3, and 4, on the board, also gives the ability to rotate the ships.
 * 
 * @note The file includes necessary headers and initialises global constants used within the setup phase of the game.
 */

// Game Modules
#include "ship.h"
#include "game.h"
#include "setup.h"
// Funkit Drivers
#include "system.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pacer.h"
#include "button.h"
#include "led.h"

ship_t ships[MAX_SHIPS];
ship_part_t parts[MAX_SHIP_PARTS];
uint8_t ship_count = 0;
int count = 0;
bool is_device_1 = false;
char received = ' ';

#define HANDSHAKE_CHAR '*'
#define TIMEOUT 5000 // Timeout value in milliseconds

/*
    Initialises the players for the beginning of the game. If the player presses the button then sets the player to player1
    then if the button is not being pressed, the IR receiver checks for a character and if it receives then sets the player to player1
    Returns:
            is_device_1: a bool saying true if the player is set as device one or false if not.
*/
bool handshake(void) 
{
    tinygl_clear();
    tinygl_update();
    while (1) {
        button_update();
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

/*
    Runs the main setup phase for the game, allows the player to place their ships then initialise the game.
    If the player is player1 then they will go to the attack phase otherwise the player will go to the defend phase.
    Params:
            is_player1: the pointer to the value denoting whether the player is player1 or not.
*/
void setup_phase(bool* is_player1) 
{
    place_ships();
    is_device_1 = handshake();
    if (is_device_1) {
        current_game_state = ATTACK;
    } else {
        current_game_state = DEFEND;
    }
    (*is_player1) = is_device_1;
}

/*
    Controls the placement of player ships. Loops through the ships and calls shipNavigation for each one.
    Once each is placed then it will add the ship to ships[] and then add the ship parts to the parts[] array.
*/
void place_ships() 
{
    bool isSelected;
    orientation_t ship_orientation;
    uint8_t length;
    for (size_t i = 0; i < MAX_SHIPS; i++) {
        isSelected = false; 
        ship_orientation = HORIZONTAL;
        start_position = tinygl_point(0,0);
        length = (i+2);
        uint8_t ship = MAX_SHIPS;
        while (isSelected == false) {
            pacer_wait ();
            tinygl_update ();
            ship_navigation(&start_position, &isSelected, length, &ship_orientation, ship);
            if (i > 0) {
                ship = (ship+1)%i;   
            }
        }
        add_ship(start_position.y, start_position.x, length, ship_orientation, i);
        add_ship_part(i);
    }
}
