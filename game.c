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
    // system_init ();
    // tinygl_init (1000);
    // tinygl_point_t selectPosition = tinygl_point(2,3);
    // tinygl_draw_point(selectPosition, 1);

    // pacer_init(1000);
    // //bool isSelected = false;
    // while (!(*isSelected)) {

        // pacer_wait ();
        // tinygl_update ();

        /* TODO: Call the navswitch update function.  */
        navswitch_update ();
        /* TODO: Increment character if NORTH is pressed.  */
        if (navswitch_push_event_p (0)) {
            tinygl_draw_point((*selectPosition), 0);
            if (selectPosition->y == 0) {
                selectPosition->y = 6;
            } else {
                selectPosition->y += -1;

            }
        }
        /* TODO: Decrement character if SOUTH is pressed.  */
        else if (navswitch_push_event_p (2)) {
            tinygl_draw_point((*selectPosition), 0);
            if (selectPosition->y == 6) {
                selectPosition->y = 0;
            } else {
                selectPosition->y += 1;

            }
        }
        else if (navswitch_push_event_p (1)) {
            tinygl_draw_point((*selectPosition), 0);
            if (selectPosition->x == 4) {
                selectPosition->x = 0;
            } else {
                selectPosition->x += 1;

            }
        }
        else if (navswitch_push_event_p (3)) {
            tinygl_draw_point((*selectPosition), 0);
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
    // }
    // return selectPosition;
}