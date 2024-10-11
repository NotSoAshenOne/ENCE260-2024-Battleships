#include "system.h"
#include "game.h"
#include "pacer.h"
#include "ship.h"


int main(void)
{
    // //system_init();
    // //game_loop();
    bool* isSelected;
    // tinygl_point_t selectedPosition;
    // tinygl_point_t startPosition = tinygl_point(2,3);
    orientation_t ship_orientation = HORIZONTAL;
    // // navigation();
    // system_init ();
    // tinygl_init (1000);
    // pacer_init(1000);
    // while(1) {
    //     pacer_wait ();
    //     tinygl_update ();

    //     if (!(*isSelected)){
    //         selectedPosition = navigation(startPosition, isSelected);
    //     } else {
    //         draw_ship(selectedPosition.y, selectedPosition.x, 2, ship_orientation);
    //     }
    // }

    system_init ();
    tinygl_init (1000);
    tinygl_point_t startPosition = tinygl_point(2,3);
    tinygl_draw_point((startPosition), 1);

    pacer_init(1000);
    //bool isSelected = false;
    while (1) {
        pacer_wait ();
        tinygl_update ();
        if (!(*isSelected)) {
            navigation(&startPosition, isSelected);
        } else {
            draw_ship((startPosition.y), (startPosition.x), 2, ship_orientation);
        }
        
    }
    return 0;
}