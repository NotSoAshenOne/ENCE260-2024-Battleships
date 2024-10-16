#ifndef ATTACK_H
#define ATTACK_H

#include "system.h"

void attack_phase(void);
char encode_coordinate(uint8_t x, uint8_t y);
void send_coordinate(uint8_t x, uint8_t y);
void select_attack (void);

#endif // ATTACK_H