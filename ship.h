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
    // bool hit;
} ship_part_t;

typedef struct {
    uint8_t row;
    uint8_t col;
    uint8_t length;
    orientation_t orientation;
} ship_t;

extern ship_t ships[MAX_SHIPS];
extern ship_part_t parts[MAX_SHIP_PARTS];
extern uint8_t ship_count;

void draw_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation);
void addShip(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation, uint8_t shipNum);
void addShipPart(uint8_t shipNum);
void drawAllParts(uint8_t partN);
void drawAllShips(uint8_t shipN);

#endif // SHIP_H