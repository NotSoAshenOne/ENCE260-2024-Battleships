#include "winlose.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_1.h"

#define LOOP_RATE 10
#define MESSAGE_RATE 10

typedef enum {
    WIN,
    LOSE
} winlose_t;

void winlose_phase(void)
{
    char c = ' ';
    winlose_t result = LOSE; // Example initialization, change as needed

    if (result == WIN) {
        c = 'W';
    } else if (result == LOSE) {
        c = 'L';
    }

    tinygl_init (LOOP_RATE);
    pacer_init (LOOP_RATE);

    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);

    if (c == 'W') {
        tinygl_draw_char('W',tinygl_point (0, 0));
    } else if (c == 'L') {
        tinygl_draw_char('L',tinygl_point (0, 0));
    } else {
        tinygl_draw_char(' ',tinygl_point (0, 0));
    }
    tinygl_update ();
}