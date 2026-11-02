#include <cstdint>
#include <graphx.h>
#include <keypadc.h>
#include <debug.h>
#include <tice.h>
// Compiled Graphics
#include "gfx/box.h"
#include "gfx/global_palette.h"
#include "gfx/player.h"
// Class + Other info
#include "game/Game.hpp"
#include "object/Object.hpp"
#include "game/Puzzles.hpp"

uint8_t on_puzzle = 1;
Object** Boxes;
Object* Player = nullptr;
gfx_tilemap_t* cur_tilemap;

/**
 * TODO:
 * I found a bug that I've been looking for forever by now. Heres how I replicated it:
 * - Start by undoing a move where you push a box
 * - Without letting go of the undo button, hold a direction
 * - Release Undo, letting your character move
 * - Undo back to when you pushed the box, the box will undo incorrectly!!
 */

void InitPuzzle(uint8_t puzzle_on)
{
    // Allocate memory for Boxes
    Boxes = new Object*[BoxNum(puzzle_on)];
    // Set the tilemap pointer to the appropriate tilemap
    cur_tilemap = Puzzle(puzzle_on);
    // Add all boxes to the puzzle tilemap
    for (int i = 0; i < BoxNum(puzzle_on); i++)
    {
        Boxes[i] = new Object(box, box_width);
        Boxes[i]->SetSpawn(BoxesPosX(puzzle_on)[i], BoxesPosY(puzzle_on)[i]);
    }
    // FAILSAFE, if the Player is not NULL
    if (Player != nullptr)
    {
        // Place the player on the tilemap, reset it from the original puzzle
        Player->SetSpawn(PlayerX(puzzle_on), PlayerY(puzzle_on));
        Player->Reset();
    }

}

int main()
{
    gfx_Begin();
    // INIT SETTIGNS
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(0);
    gfx_SetDrawBuffer();

    // Input centric
    kb_key_t arrow_keys;
    kb_key_t special_keys_1;
    kb_key_t special_keys_2;
    // Game centric
    Game::Direction dir;
    bool won = false;
    bool valid_move = false;


    Player = new Object(player, player_width);

    InitPuzzle(on_puzzle);

    uint8_t goal_c = 0;

    do {
        kb_Scan();
        // Fetches key press information
        arrow_keys = kb_Data[7];
        special_keys_1 = kb_Data[1];
        special_keys_2 = kb_Data[2];

        // If the user entered a direction...
        if (arrow_keys & (kb_Up | kb_Down | kb_Left | kb_Right))
        {
            // Find which direction they shall move in
            dir = Game::Direction::NONE;
            if (arrow_keys & kb_Down) {
                dir = Game::Direction::SOUTH;
            } else if (arrow_keys & kb_Up) {
                dir = Game::Direction::NORTH;
            } else if (arrow_keys & kb_Left) {
                dir = Game::Direction::WEST;
            } else if (arrow_keys & kb_Right) {
                dir = Game::Direction::EAST;
            }
            // Move the player, always consider it a valid move at first
            Player->Move(dir);
            valid_move = true;

            // If the player hits a wall, its an invalid move. Reset it's position
            if (Player->OverlapsWall(cur_tilemap)) {
                Player->Move(Game::mirror_dir(dir));
                valid_move = false;
            }
            // Now Check boxes
            for (int i = 0; i < BoxNum(on_puzzle); i++)
            {
                if (!Boxes[i]) continue; // Skips if Boxes[i] does not exist (failsafe)
                if (Boxes[i]->Overlaps(*Player)) Boxes[i]->Move(dir); // If the box overlaps the player, move it with the player
                // If the box overlaps an object or wall after moving with the player, its an invalid move and the box should be reset
                // along with the player
                if (Boxes[i]->OverlapsAny() || Boxes[i]->OverlapsWall(cur_tilemap)) { //
                    valid_move = false;
                    Boxes[i]->Move(Game::mirror_dir(dir));
                    Player->Move(Game::mirror_dir(dir));
                    break;
                }
            }
            // Only if the move still is valid, add the step done to all objects
            if (valid_move) {
                for (int i = 0; i < Object::num_objs; i++)
                {
                    Object::objs[i]->AddStep();
                }
            };
            // Zeroes out all moves, leaving a clean slate for undo appending
            for (int i = 0; i < Object::num_objs; i++)
            {
                Object::objs[i]->InvalidMove();
            }
        }

        // If the 2nd (undo) button is pressed
        if (special_keys_1 & kb_2nd)
        {
            // All objects undo their last step
            for (int i = 0; i < Object::num_objs; i++)
            {
                Object::objs[i]->UndoStep();
            }
        }
        // If Alpha (reset) button is pressed
        if (special_keys_2 & kb_Alpha)
        {
            // All objects return to their prev position and delete their undo history
            for (int i = 0; i < Object::num_objs; i++)
            {
                Object::objs[i]->Reset();
            }
        }

        // WIN CON CHECKING
        // Count the number of boxes overlapping goal tiles
        goal_c = 0;
        for (int i = 0; i < BoxNum(on_puzzle); i++)
        {
            if (Boxes[i]->OnTile(cur_tilemap) == WIN_TILE) goal_c++;
        }

        // If the number of boxes on win_tiles is equal to the number of boxes in the level
        if (goal_c == BoxNum(on_puzzle)) {
            // If there are more puzzles
            if (on_puzzle < NUM_PUZZLES)
            {
                // Delete All boxes
                for (int i = 0; i < BoxNum(on_puzzle); i++)
                {
                    delete Boxes[i];
                    Boxes[i] = nullptr;
                }
                // Removes current Boxes array in prep for reinitialization
                delete[] Boxes;
                Boxes = nullptr;

                // Move to the next puzzle
                on_puzzle++;
                InitPuzzle(on_puzzle);
            }
            else {
                // Otherwise, the game has been finished "won"
                won = true;
            }

        };

        // DRAWING
        gfx_FillScreen(2);
        gfx_Tilemap_NoClip(cur_tilemap, 0, 0);
        Object::Draw();
        gfx_SwapDraw();
        // WAITING
        while (!(os_GetCSC() || special_keys_1 & kb_Mode || won));

    } while (!(special_keys_1 & kb_Mode || won));

    // Ends graphical process
    gfx_End();
    // Deletes all objects from memory
    Object::End();

    return 0;
}
