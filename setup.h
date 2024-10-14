#ifndef SETUP_H
#define SETUP_H


void add_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation, uint8_t shipNum);
void setup_phase(void);
void placeShips (void);
void selectAttack (void);

#endif // SETUP_H