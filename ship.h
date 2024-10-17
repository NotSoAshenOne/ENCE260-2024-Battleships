#ifndef SHIP_H
#define SHIP_H

#include <stdint.h>
#include <stdbool.h>
#include "tinygl.h"

#define ROWS 7
#define COLUMNS 5
#define MAX_SHIPS 3
#define MAX_SHIP_LENGTH 4
#define MAX_SHIP_PARTS 9
#define SHIP_ONE_LENGTH 2
#define SHIP_TWO_LENGTH 3
#define SHIP_THREE_LENGTH 4

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
void add_ship(uint8_t row, uint8_t col, uint8_t length, orientation_t orientation, uint8_t ship_num);
void add_ship_part(uint8_t ship_num);
void draw_part(uint8_t part_num, uint8_t round);
void draw_all_ships(uint8_t ship_num);
void display_ships(uint8_t part_num, uint8_t round_num);
void draw_hit_parts(void);
void ship_navigation(tinygl_point_t* selectPosition, bool* isSelected, uint8_t length, orientation_t* orientation, uint8_t ship_num);

#endif // SHIP_H