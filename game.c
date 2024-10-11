#include "game.h"
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

uint8_t ship_positions[ROWS][COLUMNS] = {0};

typedef enum {
    SETUP,
    ATTACK,
    DEFEND,
    WINLOSE
} GameState;

orientation_t ship_orientation = HORIZONTAL;

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

void draw_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation)
{
    tinygl_init(1000);
    // Clear the display
    tinygl_clear();

    if (orientation == HORIZONTAL) {
        // Calculate the end point of the ship
        int end_col = col + length - 1;

        // Ensure the ship stays within the display bounds
        if (end_col >= COLUMNS) {
            end_col = COLUMNS - 1;
            col = end_col - length + 1;
        }

        // Draw the ship horizontally
        for (int i = 0; i < length; i++) {
            tinygl_draw_point(tinygl_point(col + i, row), 1);
        }
    } else {
        // Calculate the end point of the ship
        int end_row = row + length - 1;

        // Ensure the ship stays within the display bounds
        if (end_row >= ROWS) {
            end_row = ROWS - 1;
            row = end_row - length + 1;
        }

        // Draw the ship vertically
        for (int i = 0; i < length; i++) {
            tinygl_draw_point(tinygl_point(col, row + i), 1);
        }
    }

    // Update the display to reflect the changes
    tinygl_update();
}

void navigation(void) 
{
    system_init ();
    tinygl_init (1000);
    tinygl_point_t selectPosition = tinygl_point(2,3);
    tinygl_draw_point(selectPosition, 1);

    pacer_init(1000);
    bool isSelected = false;
    while (!isSelected) {

        pacer_wait ();
        tinygl_update ();

        /* TODO: Call the navswitch update function.  */
        navswitch_update ();
        /* TODO: Increment character if NORTH is pressed.  */
        if (navswitch_push_event_p (0)) {
            tinygl_draw_point(selectPosition, 0);
            if (selectPosition.y == 0) {
                selectPosition.y = 6;
            } else {
                selectPosition.y--;

            }
        }
        /* TODO: Decrement character if SOUTH is pressed.  */
        else if (navswitch_push_event_p (2)) {
            tinygl_draw_point(selectPosition, 0);
            if (selectPosition.y == 6) {
                selectPosition.y = 0;
            } else {
                selectPosition.y++;

            }
        }
        else if (navswitch_push_event_p (1)) {
            tinygl_draw_point(selectPosition, 0);
            if (selectPosition.x == 4) {
                selectPosition.x = 0;
            } else {
                selectPosition.x++;

            }
        }
        else if (navswitch_push_event_p (3)) {
            tinygl_draw_point(selectPosition, 0);
            if (selectPosition.x == 0) {
                selectPosition.x = 4;
            } else {
            selectPosition.x--;
            }
        }
        tinygl_draw_point(selectPosition, 1);

    }
}