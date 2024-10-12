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
        else if (navswitch_push_event_p (2)) {
            if (selectPosition->y == 6) {
                selectPosition->y = 0;
            } else {
                selectPosition->y += 1;
            }
        }
        else if (navswitch_push_event_p (1)) {
            if (selectPosition->x == 4) {
                selectPosition->x = 0;
            } else {
                selectPosition->x += 1;
            }
        }
        else if (navswitch_push_event_p (3)) {
            if (selectPosition->x == 0) {
                selectPosition->x = 4;
            } else {
            selectPosition->x += -1;
            }
        }
        else if (navswitch_push_event_p (4)) {
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
        /* TODO: Increment character if NORTH is pressed.  */
        if (navswitch_push_event_p (0)) {
            if (*orientation == VERTICAL) {
                if (selectPosition->y == 0) {
                    selectPosition->y = (6-length+1);
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
        /* TODO: Decrement character if SOUTH is pressed.  */
        else if (navswitch_push_event_p (2)) {
            //if ((selectPosition->y == (6-length) && (*orientation == VERTICAL))||(selectPosition->y == 6 && (*orientation == HORIZONTAL)))  {
            if (*orientation == VERTICAL) {
                if (selectPosition->y == (6-length+1)) {
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
        else if (navswitch_push_event_p (1)) {
            //if ((selectPosition->x == 4 && (*orientation == VERTICAL)) || (selectPosition->x == (4-length) && (*orientation == HORIZONTAL))) {
            if (*orientation == HORIZONTAL) {
                if (selectPosition->x == (4-length+1)) {
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
        else if (navswitch_push_event_p (3)) {
            if (*orientation == HORIZONTAL) {
                if (selectPosition->x == 0) {
                    selectPosition->x = (4-length+1);
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
        else if (navswitch_push_event_p (4)) {
            if ((*orientation) == HORIZONTAL) {
                (*orientation) = VERTICAL;
            } else {
                (*orientation) = HORIZONTAL;
            }
        }
        else if (button_push_event_p (0)) {
            (*isSelected) = true;
        }
        draw_ship((selectPosition->y),(selectPosition->x), length, (*orientation));
}