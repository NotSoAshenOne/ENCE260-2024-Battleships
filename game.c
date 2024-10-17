#include "game.h"
#include "ship.h"
#include "setup.h"
#include "attack.h"
#include "defend.h"
#include "winlose.h"
#include "system.h"
#include "pio.h"
#include "tinygl.h"
#include "pacer.h"
#include "navswitch.h"
#include "button.h"
#include <stdbool.h>

// Initialise the game state to begin in the SETUP phase.
game_state_t current_game_state = SETUP;
// Initialise the number of ship parts for the player and the opponent.
uint8_t player_parts_hit = 0;
uint8_t opponent_parts_hit = 0;

/*
    The main game loop. Checks the current_game_state and then calls the respective phase method 
    then changes to the next state.
*/
void game_loop(void)
{
    while (1)
    {
        if (current_game_state == SETUP) {
            setup_phase();
        } else if (current_game_state == ATTACK) {
            tinygl_clear();
            attack_phase();
            if (opponent_parts_hit == MAX_SHIP_PARTS) {
                current_game_state = WINLOSE;
            }
        } else if (current_game_state == DEFEND) {
            tinygl_clear();
            defend_phase();
            if (player_parts_hit == MAX_SHIP_PARTS) {
                current_game_state = WINLOSE;
            }
        } else if (current_game_state == WINLOSE) {
            tinygl_clear();
            while (1) {
                winlose_phase((opponent_parts == MAX_SHIP_PARTS));    
            }
        }
    }
}

/*
    Controls the cursor navigation and select by using the navswitch.
    Displays the cursor and moves it by updating the select_position value.
    Params:
            select_position: the pointer to the position of the cursor.
            is_selected: the pointer to the bool stating if the cursor position has been selected.
*/
void navigation(tinygl_point_t* select_position, bool* is_selected) 
{
        tinygl_clear ();
        navswitch_update ();
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (select_position->y == 0) {
                select_position->y = 6;
            } else {
                select_position->y += -1;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (select_position->y == 6) {
                select_position->y = 0;
            } else {
                select_position->y += 1;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            if (select_position->x == 4) {
                select_position->x = 0;
            } else {
                select_position->x += 1;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            if (select_position->x == 0) {
                select_position->x = 4;
            } else {
                select_position->x += -1;
            }
        } else if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            (*is_selected) = true;
        }
        tinygl_draw_point((*select_position), 1);
        draw_hit_parts(part, round);        
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
                    select_position->y = 6;
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
                if (select_position->y == 6) {
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
                if (select_position->x == 4) {
                select_position->x = 0;
                } else {
                select_position->x += 1;
                }
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            if (*orientation == HORIZONTAL) {
                if (select_position->x == 0) {
                    select_position->x = (COLUMNS-length);
                } else {
                    select_position->x += -1;
                }
            } else {
                if (select_position->x == 0) {
                select_position->x = 4;
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
            drawAllShips(ship_num);
        }
}



