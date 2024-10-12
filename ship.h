#ifndef SHIP_H
#define SHIP_H

#include <stdint.h>
#include <stdbool.h>

#define ROWS 7
#define COLUMNS 5
#define MAX_SHIPS 10
#define MAX_SHIP_LENGTH 7

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
    ship_part_t parts[MAX_SHIP_LENGTH];
} ship_t;



ship_part_t parts[10];


extern ship_t ships[MAX_SHIPS];
extern uint8_t ship_count;

void draw_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation);

#endif // GAME_H