#include "system.h"
#include "game.h"
#include "pacer.h"
#include "ship.h"
#include "setup.h"
#include "ir_uart.h"
#include "button.h"
#include "led.h"
#include "../fonts/font5x7_1.h"

int main(void)
{
    system_init();
    ir_uart_init ();
    button_init ();
    tinygl_init (500);
    pacer_init (500);
    led_init();
    led_set(LED1, 0);
    tinygl_font_set (&font5x7_1);

    game_loop();
    
    return 0;
}