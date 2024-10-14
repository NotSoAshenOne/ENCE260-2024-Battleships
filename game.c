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


typedef enum {
    SETUP,
    ATTACK,
    DEFEND,
    WINLOSE
} GameState;

void game_loop(void)
{
    GameState state = ATTACK;
    
    while (1)
    {
        if (state == SETUP)
        {
            setup_phase();
        }
        else if (state == ATTACK)
        {
            attack_phase();
        }
        else if (state == DEFEND)
        {
            defend_phase();
        }
        else if (state == WINLOSE)
        {
            winlose_phase();
        }
    }
}

void navigation(tinygl_point_t* selectPosition, bool* isSelected) 
{
        /* TODO: Call the navswitch update function.  */
        tinygl_draw_point((*selectPosition), 0);
        navswitch_update ();
        /* TODO: Increment character if NORTH is pressed.  */
        if (navswitch_push_event_p (0)) {
            if (selectPosition->y == 0) {
                selectPosition->y = 6;
            } else {
                selectPosition->y += -1;
            }
        }
        /* TODO: Decrement character if SOUTH is pressed.  */
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

void shipNavigation(tinygl_point_t* selectPosition, bool* isSelected, uint8_t length, orientation_t* orientation) 
{
        /* TODO: Call the navswitch update function.  */
        tinygl_clear ();
        navswitch_update ();
        button_update ();
        if (button_push_event_p (0)) {
            if ((*orientation) == HORIZONTAL) {
                (*orientation) = VERTICAL;
            } else {
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
}

void drawAllShips() {
    for (size_t i = 0; i < 3; i++) {
        ship_t ship = ships[i];
        draw_ship(ship.row, ship.col, ship.length, ship.orientation);
    }
}