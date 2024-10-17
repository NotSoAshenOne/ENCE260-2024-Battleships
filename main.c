// Game Modules
#include "game.h"
// Funkit Drivers
#include "ir_uart.h"
#include "button.h"
#include "led.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x7_1.h"
#include "system.h"

#define PACER_RATE 500
#define TINYGL_RATE 500

int main(void)
{
    system_init();
    ir_uart_init ();
    button_init ();

    pacer_init (PACER_RATE);

    tinygl_init (TINYGL_RATE);
    tinygl_font_set (&font5x7_1);

    led_init();
    led_set(LED1, 0);

    game_loop();
}