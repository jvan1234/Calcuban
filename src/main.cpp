#include <cstdint>
#include <graphx.h>
#include <keypadc.h>
#include <debug.h>
#include <tice.h>
#include "game/Game.hpp"
#include "gfx/box.h"
#include "gfx/global_palette.h"
#include "gfx/player.h"
#include "object/Object.hpp"
#include "gfx/gfx.h"
#include "game/Puzzles.hpp"

uint8_t on_puzzle = 1;
Object** Boxes;
Object* Player = nullptr;
gfx_tilemap_t* cur_tilemap;


void InitPuzzle(uint8_t puzzle_on)
{
    dbg_sprintf(dbgout, "Entered InitPuzzle...");
    Boxes = new Object*[BoxNum(puzzle_on)];
    cur_tilemap = Puzzle(puzzle_on);
    for (int i = 0; i < BoxNum(puzzle_on); i++)
    {
        Boxes[i] = new Object(box, box_width);
        Boxes[i]->SetSpawn(BoxesPosX(puzzle_on)[i], BoxesPosY(puzzle_on)[i]);
    }
    if (Player != nullptr)
    {
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
        arrow_keys = kb_Data[7];
        special_keys_1 = kb_Data[1];
        special_keys_2 = kb_Data[2];
        if (arrow_keys & (kb_Up | kb_Down | kb_Left | kb_Right))
        {
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

            Player->Move(dir);
            valid_move = true;
            if (Player->OverlapsWall(cur_tilemap)) {
                Player->Move(Game::mirror_dir(dir));
                valid_move = false;
            }
            // Now Check boxes
            for (int i = 0; i < BoxNum(on_puzzle); i++)
            {
                if (!Boxes[i]) continue; // Skips if Boxes[i] does not exist
                if (Boxes[i]->Overlaps(*Player)) Boxes[i]->Move(dir);
                // Now check if its still overlapping anything
                if (Boxes[i]->OverlapsAny()) {
                    valid_move = false;
                    Boxes[i]->Move(Game::mirror_dir(dir));
                    Player->Move(Game::mirror_dir(dir));
                    break;
                }
                if (Boxes[i]->OverlapsWall(cur_tilemap))
                {
                    valid_move = false;
                    Boxes[i]->Move(Game::mirror_dir(dir));
                    Player->Move(Game::mirror_dir(dir));
                    break;
                }
            }
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


        if (special_keys_1 & kb_2nd)
        {
            for (int i = 0; i < Object::num_objs; i++)
            {
                Object::objs[i]->UndoStep();
            }
        }
        if (special_keys_2 & kb_Alpha)
        {
            for (int i = 0; i < Object::num_objs; i++)
            {
                Object::objs[i]->Reset();
            }
        }

        goal_c = 0;
        for (int i = 0; i < BoxNum(on_puzzle); i++)
        {
            if (Boxes[i]->OnTile(cur_tilemap) == 2) goal_c++;
        }
        if (goal_c == BoxNum(on_puzzle)) {
            if (on_puzzle < NUM_PUZZLES)
            {
                for (int i = 0; i < BoxNum(on_puzzle); i++)
                {
                    delete Boxes[i];
                    Boxes[i] = nullptr;
                }
                delete[] Boxes;
                Boxes = nullptr;


                on_puzzle++;
                InitPuzzle(on_puzzle);
                Player->Reset();
            }
            else {
                won = true;
            }

        };
        gfx_FillScreen(2);
        gfx_Tilemap_NoClip(cur_tilemap, 0, 0);
        Object::Draw();
        gfx_SwapDraw();
        while (!(os_GetCSC() || special_keys_1 & kb_Mode || won));

    } while (!(special_keys_1 & kb_Mode || won));

    gfx_End();

    Object::End();

    return 0;
}
