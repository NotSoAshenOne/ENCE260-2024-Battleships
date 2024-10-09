#include "system.h"
#include "game.h"

int main(void)
{
    system_init();
    game_loop();
    return 0;
}