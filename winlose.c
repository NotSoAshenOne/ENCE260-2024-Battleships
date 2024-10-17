#include "winlose.h"
#include "tinygl.h"

/*
    The main loop for the win / lose phase within the game loop. Checks if a win and then draws a 'W' for a win and 'L' for loss.
    Params:
            win: a boolean stating if the player won.
*/
void winlose_phase(bool win)
{
    // char c = ' ';
    if (win) {
        // c = 'W';
        tinygl_draw_char('W',tinygl_point (0, 0));
    } else {
        // c = 'L';
        tinygl_draw_char('L',tinygl_point (0, 0));
    }
    // if (c == 'W') {
    //     tinygl_draw_char('W',tinygl_point (0, 0));
    // } else if (c == 'L') {
    //     tinygl_draw_char('L',tinygl_point (0, 0));
    // } else {
    //     tinygl_draw_char(' ',tinygl_point (0, 0));
    // }
    tinygl_update ();
}