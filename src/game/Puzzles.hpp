#ifndef PUZZLES_HPP
#define PUZZLES_HPP

#include <cstdint>
#include <graphx.h>
#include "gfx/tileset.h"
#include "tilemap/tilemap.h"

#define WALL_TILE 1
#define WIN_TILE 2

#define TILE_WIDTH 16
#define Y_OFF 0
#define X_OFF 0

#define NUM_PUZZLES 5

extern gfx_tilemap_t puzzle1_tilemap;

#define PUZZLE1_NUM_BOXES 2
extern uint8_t puzzle1_boxes_x[PUZZLE1_NUM_BOXES];
extern uint8_t puzzle1_boxes_y[PUZZLE1_NUM_BOXES];
extern uint8_t puzzle1_player_x;
extern uint8_t puzzle1_player_y;

// Puzzle 2
extern gfx_tilemap_t puzzle2_tilemap;
#define PUZZLE2_NUM_BOXES 3
extern uint8_t puzzle2_boxes_x[PUZZLE2_NUM_BOXES];
extern uint8_t puzzle2_boxes_y[PUZZLE2_NUM_BOXES];
extern uint8_t puzzle2_player_x;
extern uint8_t puzzle2_player_y;

// Puzzle 3
extern gfx_tilemap_t puzzle3_tilemap;
#define PUZZLE3_NUM_BOXES 2
extern uint8_t puzzle3_boxes_x[PUZZLE3_NUM_BOXES];
extern uint8_t puzzle3_boxes_y[PUZZLE3_NUM_BOXES];
extern uint8_t puzzle3_player_x;
extern uint8_t puzzle3_player_y;

// Puzzle 4
extern gfx_tilemap_t puzzle4_tilemap;
#define PUZZLE4_NUM_BOXES 3
extern uint8_t puzzle4_boxes_x[PUZZLE4_NUM_BOXES];
extern uint8_t puzzle4_boxes_y[PUZZLE4_NUM_BOXES];
extern uint8_t puzzle4_player_x;
extern uint8_t puzzle4_player_y;

// Puzzle 5
extern gfx_tilemap_t puzzle5_tilemap;
#define PUZZLE5_NUM_BOXES 4
extern uint8_t puzzle5_boxes_x[PUZZLE5_NUM_BOXES];
extern uint8_t puzzle5_boxes_y[PUZZLE5_NUM_BOXES];
extern uint8_t puzzle5_player_x;
extern uint8_t puzzle5_player_y;
// Do not put more puzzles below:
extern uint8_t puzzles_box_num[NUM_PUZZLES];
extern uint8_t* puzzles_boxes_x[NUM_PUZZLES];
extern uint8_t* puzzles_boxes_y[NUM_PUZZLES];
extern uint8_t puzzles_player_x[NUM_PUZZLES];
extern uint8_t puzzles_player_y[NUM_PUZZLES];
// Gives Box Info:
extern uint8_t* BoxesPosX(uint8_t puzzle_num);
extern uint8_t* BoxesPosY(uint8_t puzzle_num);
extern uint8_t BoxNum(uint8_t puzzle_num);
extern uint8_t PlayerX(uint8_t puzzle_num);
extern uint8_t PlayerY(uint8_t puzzle_num);
extern gfx_tilemap_t* Puzzle(uint8_t puzzle_num);
#endif
