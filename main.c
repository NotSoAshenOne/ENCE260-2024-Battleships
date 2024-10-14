#include "system.h"
#include "game.h"
#include "pacer.h"
#include "ship.h"
#include "setup.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_1.h"



int main(void)
{
    system_init();
    // ir_uart_init ();
    button_init ();
    tinygl_init (1000);
    pacer_init (1000);
    // led_init();
    // led_set(LED1, 0);



    // tinygl_font_set (&font5x7_1);

    // game_loop();
    
    
    // tinygl_point_t selectedPosition;
    // tinygl_point_t startPosition = tinygl_point(2,3);
    
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
    placeShips();
    return 0;
}