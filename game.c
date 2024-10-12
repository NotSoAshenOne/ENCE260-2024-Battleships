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
#include "../fonts/font5x7_1.h"

typedef enum {
    SETUP,
    ATTACK,
    DEFEND,
    WINLOSE
} GameState;

void game_loop(void)
{
    GameState state = SETUP;
    
    while (1)
    {
        switch (state)
        {
            case SETUP:
                setup_phase();
                state = ATTACK; // Transition to next state
                break;
            case ATTACK:
                attack_phase();
                state = DEFEND; // Transition to next state
                break;
            case DEFEND:
                defend_phase();
                state = WINLOSE; // Transition to next state
                break;
            case WINLOSE:
                winlose_phase();
                //state = SETUP; // Restart or end game
                state = ATTACK; // <- Don't need to setup again, just need to remember the ship positions and states.
                break;
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

void shipNavigation(tinygl_point_t* selectPosition, bool* isSelected, uint8_t length, orientation_t orientation) 
{
        /* TODO: Call the navswitch update function.  */
        tinygl_clear ();
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
        draw_ship((selectPosition->y),(selectPosition->x), length, orientation);
}