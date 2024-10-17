#ifndef SHIP_H
#define SHIP_H

#include <stdint.h>
#include <stdbool.h>

#define ROWS 7
#define COLUMNS 5
#define MAX_SHIPS 3
#define MAX_SHIP_LENGTH 7
#define MAX_SHIP_PARTS 9

typedef enum {
    HORIZONTAL,
    VERTICAL
} orientation_t;

typedef struct {
    uint8_t row;
    uint8_t col;
    bool hit;
} ship_part_t;

typedef struct {
    uint8_t row;
    uint8_t col;
    uint8_t length;
    orientation_t orientation;
    bool sunk;
} ship_t;

extern ship_t ships[MAX_SHIPS];
extern ship_part_t parts[MAX_SHIP_PARTS];
extern uint8_t ship_count;
extern ship_part_t opponent_parts[MAX_SHIP_PARTS];

void draw_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation);
void addShip(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation, uint8_t shipNum);
void addShipPart(uint8_t shipNum);
void drawAllParts(uint8_t partN, uint8_t round);
void drawAllShips(uint8_t shipN);
void display_ships(uint8_t part_num, uint8_t round_num);

#endif // SHIP_H