#include "Puzzles.hpp"
#include <cstdint>
#include <graphx.h>

uint8_t Puzzle::num_puzzles = 0;
uint8_t* Puzzle::puzzles_box_num = new uint8_t[MAX_PUZZLES];
uint8_t** Puzzle::puzzles_box_pos_x = new uint8_t*[MAX_PUZZLES];
uint8_t** Puzzle::puzzles_box_pos_y = new uint8_t*[MAX_PUZZLES];
uint8_t* Puzzle::puzzles_player_pos_x = new uint8_t[MAX_PUZZLES];
uint8_t* Puzzle::puzzles_player_pos_y = new uint8_t[MAX_PUZZLES];
gfx_tilemap_t** Puzzle::puzzles_tilemaps = new gfx_tilemap_t*[MAX_PUZZLES];

void Puzzle::CreatePuzzle(gfx_tilemap_t *tilemap, const uint8_t& box_c, uint8_t *boxes_x, uint8_t* boxes_y, const uint8_t& player_x, const uint8_t& player_y)
{
    if (num_puzzles >= MAX_PUZZLES) return;
    // Set a new tilemap
    puzzles_box_num[num_puzzles] = box_c;
    puzzles_box_pos_x[num_puzzles] = boxes_x;
    puzzles_box_pos_y[num_puzzles] = boxes_y;
    puzzles_tilemaps[num_puzzles] = tilemap;
    puzzles_player_pos_x[num_puzzles] = player_x;
    puzzles_player_pos_y[num_puzzles] = player_y;
    // State the new number of puzzles
    num_puzzles++;
    return;
}

uint8_t* Puzzle::GetBoxesX(uint8_t puzzle_num)
{
    if ((puzzle_num - 1) < 0 || (puzzle_num - 1) >= num_puzzles) return nullptr;

    return puzzles_box_pos_x[puzzle_num - 1];
}

uint8_t* Puzzle::GetBoxesY(uint8_t puzzle_num)
{
    if ((puzzle_num - 1) < 0 || (puzzle_num - 1) >= num_puzzles) return nullptr;
    return puzzles_box_pos_y[puzzle_num - 1];
}

uint8_t Puzzle::GetBoxCount(uint8_t puzzle_num)
{
    if ((puzzle_num - 1) < 0 || (puzzle_num - 1) >= num_puzzles) return 0;
    return puzzles_box_num[puzzle_num - 1];
}

uint8_t Puzzle::GetPlayerX(uint8_t puzzle_num)
{
    if ((puzzle_num - 1) < 0 || (puzzle_num - 1) >= num_puzzles) return 0;
    return puzzles_player_pos_x[puzzle_num - 1];
}

uint8_t Puzzle::GetPlayerY(uint8_t puzzle_num)
{
    if ((puzzle_num - 1) < 0 || (puzzle_num - 1) >= num_puzzles) return 0;
    return puzzles_player_pos_y[puzzle_num - 1];
}

gfx_tilemap_t* Puzzle::GetTilemap(uint8_t puzzle_num)
{
    if ((puzzle_num - 1) < 0 || (puzzle_num - 1) >= num_puzzles) return nullptr;
    return puzzles_tilemaps[puzzle_num - 1];
}

uint8_t Puzzle::GetPuzzleCount() {
    return num_puzzles;
}

void Puzzle::End() {
    delete[] puzzles_box_num;
    puzzles_box_num = nullptr;

    delete[] puzzles_tilemaps;
    puzzles_tilemaps = nullptr;

    delete[] puzzles_box_pos_x;
    puzzles_box_pos_x = nullptr;

    delete[] puzzles_box_pos_y;
    puzzles_box_pos_y = nullptr;

    delete[] puzzles_player_pos_x;
    puzzles_player_pos_x = nullptr;

    delete [] puzzles_player_pos_y;
    puzzles_player_pos_y = nullptr;
}

// Raw init
uint8_t puzzle1_boxes_x[PUZZLE1_NUM_BOXES] = {1,3};
uint8_t puzzle1_boxes_y[PUZZLE1_NUM_BOXES] = {3, 4};
uint8_t puzzle1_player_x = 2;
uint8_t puzzle1_player_y = 3;

uint8_t puzzle2_boxes_x[PUZZLE2_NUM_BOXES] = {2, 3, 3};
uint8_t puzzle2_boxes_y[PUZZLE2_NUM_BOXES] = {3, 3, 4};
uint8_t puzzle2_player_x = 3;
uint8_t puzzle2_player_y = 2;


uint8_t puzzle3_boxes_x[PUZZLE3_NUM_BOXES] = {6, 6};
uint8_t puzzle3_boxes_y[PUZZLE3_NUM_BOXES] = {2, 3};
uint8_t puzzle3_player_x = 6;
uint8_t puzzle3_player_y = 4;

uint8_t puzzle4_boxes_x[PUZZLE4_NUM_BOXES] = {3, 4, 5};
uint8_t puzzle4_boxes_y[PUZZLE4_NUM_BOXES] = {2, 2, 2};
uint8_t puzzle4_player_x = 6;
uint8_t puzzle4_player_y = 2;


uint8_t puzzle5_boxes_x[PUZZLE5_NUM_BOXES] = {3, 4, 4, 5};
uint8_t puzzle5_boxes_y[PUZZLE5_NUM_BOXES] = {3, 2, 4, 3};
uint8_t puzzle5_player_x = 4;
uint8_t puzzle5_player_y = 3;

uint8_t puzzle6_boxes_x[PUZZLE6_NUM_BOXES] = {2, 3, 2};
uint8_t puzzle6_boxes_y[PUZZLE6_NUM_BOXES] = {2, 2, 3};
uint8_t puzzle6_player_x = 10;
uint8_t puzzle6_player_y = 2;

uint8_t puzzle7_boxes_x[PUZZLE7_NUM_BOXES] = {3, 2, 4, 3, 2, 4};
uint8_t puzzle7_boxes_y[PUZZLE7_NUM_BOXES] = {2, 3, 3, 4, 5, 5};
uint8_t puzzle7_player_x = 3;
uint8_t puzzle7_player_y= 5;

uint8_t puzzle8_boxes_x[PUZZLE8_NUM_BOXES] = {4, 5};
uint8_t puzzle8_boxes_y[PUZZLE8_NUM_BOXES] = {2, 2};
uint8_t puzzle8_player_x = 6;
uint8_t puzzle8_player_y = 1;

uint8_t puzzle9_boxes_x[PUZZLE9_NUM_BOXES] = {2, 3};
uint8_t puzzle9_boxes_y[PUZZLE9_NUM_BOXES] = {2, 2};
uint8_t puzzle9_player_x = 1;
uint8_t puzzle9_player_y = 2;

uint8_t puzzle10_boxes_x[PUZZLE10_NUM_BOXES] = {4, 6, 8};
uint8_t puzzle10_boxes_y[PUZZLE10_NUM_BOXES] = {4, 4, 4};
uint8_t puzzle10_player_x = 2;
uint8_t puzzle10_player_y = 4;
