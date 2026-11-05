#ifndef PUZZLES_HPP
#define PUZZLES_HPP

#include <cstdint>
#include <graphx.h>

#define WALL_TILE 1
#define WIN_TILE 2
#define MAX_PUZZLES 255

class Puzzle {
    private:
        static uint8_t num_puzzles;
        static uint8_t* puzzles_box_num;
        static uint8_t** puzzles_box_pos_x;
        static uint8_t** puzzles_box_pos_y;
        static uint8_t* puzzles_player_pos_x;
        static uint8_t* puzzles_player_pos_y;
        static gfx_tilemap_t** puzzles_tilemaps;
    public:
        // TODO: function for making puzzles
        static void CreatePuzzle(gfx_tilemap_t* tilemap, const uint8_t& box_c, uint8_t* boxes_x, uint8_t* boxes_y, const uint8_t& player_x, const uint8_t& player_y);
        static uint8_t* GetBoxesX(uint8_t puzzle_num);
        static uint8_t* GetBoxesY(uint8_t puzzle_num);
        static uint8_t GetPlayerX(uint8_t puzzle_num);
        static uint8_t GetPlayerY(uint8_t puzzle_num);
        static uint8_t GetBoxCount(uint8_t puzzle_num);
        static gfx_tilemap_t* GetTilemap(uint8_t puzzle_num);
        static uint8_t GetPuzzleCount();
        static void End();
};

#define TILE_WIDTH 16
#define Y_OFF 0
#define X_OFF 0

#define NUM_PUZZLES 7

#define PUZZLE1_NUM_BOXES 2
extern uint8_t puzzle1_boxes_x[PUZZLE1_NUM_BOXES];
extern uint8_t puzzle1_boxes_y[PUZZLE1_NUM_BOXES];
extern uint8_t puzzle1_player_x;
extern uint8_t puzzle1_player_y;

// Puzzle 2

#define PUZZLE2_NUM_BOXES 3
extern uint8_t puzzle2_boxes_x[PUZZLE2_NUM_BOXES];
extern uint8_t puzzle2_boxes_y[PUZZLE2_NUM_BOXES];
extern uint8_t puzzle2_player_x;
extern uint8_t puzzle2_player_y;

// Puzzle 3
#define PUZZLE3_NUM_BOXES 2
extern uint8_t puzzle3_boxes_x[PUZZLE3_NUM_BOXES];
extern uint8_t puzzle3_boxes_y[PUZZLE3_NUM_BOXES];
extern uint8_t puzzle3_player_x;
extern uint8_t puzzle3_player_y;

// Puzzle 4
#define PUZZLE4_NUM_BOXES 3
extern uint8_t puzzle4_boxes_x[PUZZLE4_NUM_BOXES];
extern uint8_t puzzle4_boxes_y[PUZZLE4_NUM_BOXES];
extern uint8_t puzzle4_player_x;
extern uint8_t puzzle4_player_y;

// Puzzle 5
#define PUZZLE5_NUM_BOXES 4
extern uint8_t puzzle5_boxes_x[PUZZLE5_NUM_BOXES];
extern uint8_t puzzle5_boxes_y[PUZZLE5_NUM_BOXES];
extern uint8_t puzzle5_player_x;
extern uint8_t puzzle5_player_y;

// Puzzle 6
#define PUZZLE6_NUM_BOXES 3
extern uint8_t puzzle6_boxes_x[PUZZLE6_NUM_BOXES];
extern uint8_t puzzle6_boxes_y[PUZZLE6_NUM_BOXES];
extern uint8_t puzzle6_player_x;
extern uint8_t puzzle6_player_y;

// Puzzle 7
#define PUZZLE7_NUM_BOXES 6
extern uint8_t puzzle7_boxes_x[PUZZLE7_NUM_BOXES];
extern uint8_t puzzle7_boxes_y[PUZZLE7_NUM_BOXES];
extern uint8_t puzzle7_player_x;
extern uint8_t puzzle7_player_y;

// Puzzle 8
#define PUZZLE8_NUM_BOXES 2
extern uint8_t puzzle8_boxes_x[PUZZLE8_NUM_BOXES];
extern uint8_t puzzle8_boxes_y[PUZZLE8_NUM_BOXES];
extern uint8_t puzzle8_player_x;
extern uint8_t puzzle8_player_y;
// Do not put more puzzles below:
#endif
