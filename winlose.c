#include "winlose.h"
#include "tinygl.h"
#include "pacer.h"

typedef enum {
    WIN,
    LOSE
} winlose_t;

void winlose_phase(bool win)
{
    char c = ' ';
    winlose_t result;
    if (win){
        result = WIN;
    } else {
        result = LOSE;
    }
    //winlose_t result = LOSE; // Example initialization, change as needed

    if (result == WIN) {
        c = 'W';
    } else if (result == LOSE) {
        c = 'L';
    }

    if (c == 'W') {
        tinygl_draw_char('W',tinygl_point (0, 0));
    } else if (c == 'L') {
        tinygl_draw_char('L',tinygl_point (0, 0));
    } else {
        tinygl_draw_char(' ',tinygl_point (0, 0));
    }
    tinygl_update ();
}

void check_end() {
    if 1
    putc 'E';
    while (!ready to receive) {
        putc 'E'
    }
    get 

    if 2
    //put 'E'
    while(not ready) {

    }

    
}