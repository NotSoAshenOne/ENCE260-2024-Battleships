#ifndef DEFEND_H
#define DEFEND_H

#include "system.h"

void decode_coordinate(uint8_t* x, uint8_t* y, char encoded_char);
void defend_phase(void);
void check_hit(uint8_t x, uint8_t y);
bool check_part_hit(uint8_t x, uint8_t y);

#endif // DEFEND_H