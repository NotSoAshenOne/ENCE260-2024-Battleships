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

game_state_t current_game_state = SETUP;
uint8_t player_parts = 9;
uint8_t opponent_parts = 9;

void game_loop(void)
{
    
    while (1)
    {
        if (current_game_state == SETUP)
        {
            setup_phase();
        }
        else if (current_game_state == ATTACK)
        {
            tinygl_clear();
            attack_phase();
            if (opponent_parts == 0) {
                current_game_state = WINLOSE;
            }
        }
        else if (current_game_state == DEFEND)
        {
            tinygl_clear();
            defend_phase();
            if (player_parts == 0) {
                current_game_state = WINLOSE;
            }
        }
        else if (current_game_state == WINLOSE)
        {
            tinygl_clear();
            while (1) {
                winlose_phase((opponent_parts == 0));    
            }
            
        }
    }
}

void navigation(tinygl_point_t* selectPosition, bool* isSelected) 
{
        tinygl_clear ();
        navswitch_update ();
        button_update ();

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (selectPosition->y == 0) {
                selectPosition->y = 6;
            } else {
                selectPosition->y += -1;
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (selectPosition->y == 6) {
                selectPosition->y = 0;
            } else {
                selectPosition->y += 1;
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            if (selectPosition->x == 4) {
                selectPosition->x = 0;
            } else {
                selectPosition->x += 1;
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            if (selectPosition->x == 0) {
                selectPosition->x = 4;
            } else {
                selectPosition->x += -1;
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            (*isSelected) = true;
        }

        tinygl_draw_point((*selectPosition), 1);        
}

void shipNavigation(tinygl_point_t* selectPosition, bool* isSelected, uint8_t length, orientation_t* orientation, uint8_t shipN) 
{
        /* TODO: Call the navswitch update function.  */
        tinygl_clear ();
        navswitch_update ();
        button_update ();
        if (button_push_event_p (0)) {
            if ((*orientation) == HORIZONTAL) {
                if (selectPosition->y >(7-length)) {
                    selectPosition->y = (7-length);
                }
                (*orientation) = VERTICAL;
            } else {
                if (selectPosition->x > (5-length)) {
                    selectPosition->x = (5-length);
                }
                (*orientation) = HORIZONTAL;
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (*orientation == VERTICAL) {
                if (selectPosition->y == 0) {
                    selectPosition->y = (7-length);
                } else {
                    selectPosition->y += -1;
                }
            } else {
                if (selectPosition->y == 0) {
                    selectPosition->y = 6;
                } else {
                    selectPosition->y += -1;
                }
            }
        } 
        else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (*orientation == VERTICAL) {
                if (selectPosition->y == (7-length)) {
                    selectPosition->y = 0;
                } else {
                    selectPosition->y += 1;
                }
            } else {
                if (selectPosition->y == 6) {
                    selectPosition->y = 0;
                } else {
                    selectPosition->y += 1;
                }
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_EAST)) {
            if (*orientation == HORIZONTAL) {
                if (selectPosition->x == (5-length)) {
                    selectPosition->x = 0;
                } else {
                    selectPosition->x += 1;
                }
            } else {
                if (selectPosition->x == 4) {
                selectPosition->x = 0;
                } else {
                selectPosition->x += 1;
                }
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_WEST)) {
            if (*orientation == HORIZONTAL) {
                if (selectPosition->x == 0) {
                    selectPosition->x = (5-length);
                } else {
                    selectPosition->x += -1;
                }
            } else {
                if (selectPosition->x == 0) {
                selectPosition->x = 4;
                } else {
                selectPosition->x += -1;
                }
            }
        }
        else if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            (*isSelected) = true;
        }
        draw_ship((selectPosition->y),(selectPosition->x), length, (*orientation));
        if (shipN != 10) {
            drawAllShips(shipN);
        }
}



