#ifndef ATTACK_H
#define ATTACK_H

#include "system.h"
#include "tinygl.h"

void attack_phase(void);
char encode_coordinate(uint8_t x, uint8_t y);
void send_coordinate(uint8_t x, uint8_t y);
void navigation(tinygl_point_t* selectPosition, bool* isSelected);
void add_attack_coordinate(int row, int col);
void send_attack (void);

#endif // ATTACK_H