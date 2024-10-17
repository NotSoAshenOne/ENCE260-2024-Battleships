#ifndef SETUP_H
#define SETUP_H

tinygl_point_t start_position;

bool handshake(void);
void add_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation, uint8_t shipNum);
void setup_phase(bool* is_player1);
void placeShips (void);

#endif // SETUP_H