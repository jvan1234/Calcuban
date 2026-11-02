#include "Puzzles.hpp"
#include <cstdint>
#include <graphx.h>

gfx_tilemap_t puzzle1_tilemap = {
    .map = puzzle1_map,
    .tiles = tileset_tiles,
    .tile_height = TILE_WIDTH, // Square is W * W so this is fine right?
    .tile_width = TILE_WIDTH,
    .draw_height = 7,
    .draw_width = 6,
    .type_width = gfx_tile_16_pixel,
    .type_height = gfx_tile_16_pixel,
    .height = 7,
    .width = 6,
    .y_loc = Y_OFF,
    .x_loc = X_OFF
};
uint8_t puzzle1_boxes_x[PUZZLE1_NUM_BOXES] = {1,3};
uint8_t puzzle1_boxes_y[PUZZLE1_NUM_BOXES] = {3, 4};
uint8_t puzzle1_player_x = 2;
uint8_t puzzle1_player_y = 3;

gfx_tilemap_t puzzle2_tilemap = {
    .map = puzzle2_map,
    .tiles = tileset_tiles,
    .tile_height = TILE_WIDTH,
    .tile_width = TILE_WIDTH,
    .draw_height = 7,
    .draw_width = 6,
    .type_width = gfx_tile_16_pixel,
    .type_height = gfx_tile_16_pixel,
    .height = 7,
    .width = 6,
    .y_loc = Y_OFF,
    .x_loc = X_OFF
};
uint8_t puzzle2_boxes_x[PUZZLE2_NUM_BOXES] = {2, 3, 3};
uint8_t puzzle2_boxes_y[PUZZLE2_NUM_BOXES] = {3, 3, 4};
uint8_t puzzle2_player_x = 3;
uint8_t puzzle2_player_y = 2;

gfx_tilemap_t puzzle3_tilemap = {
    .map = puzzle3_map,
    .tiles = tileset_tiles,
    .tile_height = TILE_WIDTH,
    .tile_width = TILE_WIDTH,
    .draw_height = 6,
    .draw_width = 9,
    .type_width = gfx_tile_16_pixel,
    .type_height = gfx_tile_16_pixel,
    .height = 6,
    .width = 9,
    .y_loc = Y_OFF,
    .x_loc = X_OFF
};
uint8_t puzzle3_boxes_x[PUZZLE3_NUM_BOXES] = {6, 6};
uint8_t puzzle3_boxes_y[PUZZLE3_NUM_BOXES] = {2, 3};
uint8_t puzzle3_player_x = 6;
uint8_t puzzle3_player_y = 4;

gfx_tilemap_t puzzle4_tilemap = {
    .map = puzzle4_map,
    .tiles = tileset_tiles,
    .tile_height = TILE_WIDTH,
    .tile_width = TILE_WIDTH,
    .draw_height = 6,
    .draw_width = 8,
    .type_width = gfx_tile_16_pixel,
    .type_height = gfx_tile_16_pixel,
    .height = 6,
    .width = 8,
    .y_loc = Y_OFF,
    .x_loc = X_OFF
};
uint8_t puzzle4_boxes_x[PUZZLE4_NUM_BOXES] = {3, 4, 5};
uint8_t puzzle4_boxes_y[PUZZLE4_NUM_BOXES] = {2, 2, 2};
uint8_t puzzle4_player_x = 6;
uint8_t puzzle4_player_y = 2;

gfx_tilemap_t puzzle5_tilemap = {
    .map = puzzle5_map,
    .tiles = tileset_tiles,
    .tile_height = TILE_WIDTH,
    .tile_width = TILE_WIDTH,
    .draw_height = 7,
    .draw_width = 8,
    .type_width = gfx_tile_16_pixel,
    .type_height = gfx_tile_16_pixel,
    .height = 7,
    .width = 8,
    .y_loc = Y_OFF,
    .x_loc = X_OFF
};
uint8_t puzzle5_boxes_x[PUZZLE5_NUM_BOXES] = {3, 4, 4, 5};
uint8_t puzzle5_boxes_y[PUZZLE5_NUM_BOXES] = {3, 2, 4, 3};
uint8_t puzzle5_player_x = 4;
uint8_t puzzle5_player_y = 3;

uint8_t puzzles_box_num[NUM_PUZZLES] = {PUZZLE1_NUM_BOXES, PUZZLE2_NUM_BOXES, PUZZLE3_NUM_BOXES, PUZZLE4_NUM_BOXES, PUZZLE5_NUM_BOXES};
uint8_t* puzzles_boxes_x[NUM_PUZZLES] = {puzzle1_boxes_x, puzzle2_boxes_x, puzzle3_boxes_x, puzzle4_boxes_x, puzzle5_boxes_x};
uint8_t* puzzles_boxes_y[NUM_PUZZLES] = {puzzle1_boxes_y, puzzle2_boxes_y, puzzle3_boxes_y, puzzle4_boxes_y, puzzle5_boxes_y};
uint8_t puzzles_player_x[NUM_PUZZLES] = {puzzle1_player_x, puzzle2_player_x, puzzle3_player_x, puzzle4_player_x, puzzle5_player_x};
uint8_t puzzles_player_y[NUM_PUZZLES] = {puzzle1_player_y, puzzle2_player_y, puzzle3_player_y, puzzle4_player_y, puzzle5_player_y};

uint8_t* BoxesPosX(uint8_t puzzle_num) {
    return puzzles_boxes_x[puzzle_num - 1];
}

uint8_t* BoxesPosY(uint8_t puzzle_num)
{
    return puzzles_boxes_y[puzzle_num - 1];
}

uint8_t BoxNum(uint8_t puzzle_num)
{
    return puzzles_box_num[puzzle_num - 1];
}

uint8_t PlayerX(uint8_t puzzle_num)
{
    return puzzles_player_x[puzzle_num - 1];
}

uint8_t PlayerY(uint8_t puzzle_num)
{
    return puzzles_player_y[puzzle_num - 1];
}

gfx_tilemap_t* Puzzle(uint8_t puzzle_num)
{
    switch (puzzle_num - 1)
    {
        case 0: return &puzzle1_tilemap;
        case 1: return &puzzle2_tilemap;
        case 2: return &puzzle3_tilemap;
        case 3: return &puzzle4_tilemap;
        case 4: return &puzzle5_tilemap;
        default: return nullptr;
    }
}
