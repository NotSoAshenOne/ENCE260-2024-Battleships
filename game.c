#include "game.h"
#include "setup.h"
#include "attack.h"
#include "defend.h"
#include "winlose.h"
#include "system.h"
#include "pio.h"
#include "tinygl.h"
#include "pacer.h"

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
                state = SETUP; // Restart or end game
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
        // Calculate the start and end points of the ship
        int start_col = col - length / 2;
        int end_col = col + length / 2;

        // Ensure the ship stays within the display bounds
        if (start_col < 0) {
            start_col = 0;
            end_col = length - 1;
        }
        if (end_col >= COLUMNS) {
            end_col = COLUMNS - 1;
            start_col = end_col - length + 1;
        }

        // Draw the ship horizontally
        tinygl_draw_line(tinygl_point(start_col, row), tinygl_point(end_col, row), 1);
    } else {
        // Calculate the start and end points of the ship
        int start_row = row - length / 2;
        int end_row = row + length / 2;

        // Ensure the ship stays within the display bounds
        if (start_row < 0) {
            start_row = 0;
            end_row = length - 1;
        }
        if (end_row >= ROWS) {
            end_row = ROWS - 1;
            start_row = end_row - length + 1;
        }

        // Draw the ship vertically
        tinygl_draw_line(tinygl_point(col, start_row), tinygl_point(col, end_row), 1);
    }

    // Update the display to reflect the changes
    tinygl_update();
}