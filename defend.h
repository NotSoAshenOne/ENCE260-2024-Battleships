#ifndef DEFEND_H
#define DEFEND_H
#include <stdint.h>
#include <stdbool.h>

void defend_phase(void);
void check_hit(uint8_t x, uint8_t y);
bool check_part_hit(uint8_t x, uint8_t y, uint8_t* partNum);
bool check_ship_sunk(uint8_t* partNum);
void all_ships_sunk(void);
bool all_parts_sunk(void);

#endif // DEFEND_H