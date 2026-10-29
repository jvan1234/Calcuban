// Calculator includes
#include <tice.h>
#include <stdio.h>
#include <graphx.h>
#include <keypadc.h>
// Premade assets
#include "gfx/gfx.h"
// Classes
#include "Object.hpp"
#include "Vector.hpp"
// Enums
#include "Types.hpp"

// Tilemap
extern unsigned char tilemap_map[];

#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define TILEMAP_WIDTH 6
#define TILEMAP_HEIGHT 7
#define TILEMAP_DRAW_WIDTH  6
#define TILEMAP_DRAW_HEIGHT 7

#define Y_OFFSET            0
#define X_OFFSET            0



int main(void)
{
    // KEY PRESSED REGISTER
    kb_key_t key;
    kb_key_t key_2nd;
    kb_key_t key_alpha;
    // MORE SHIT
    int b_c = 0;
    // START GRAPHICS INIT


    // -- Sets up tilemap
    gfx_tilemap_t tilemap;
    tilemap.map = tilemap_map;
    tilemap.tiles = tileset_tiles;
    tilemap.type_width = gfx_tile_16_pixel;
    tilemap.type_height = gfx_tile_16_pixel;
    tilemap.tile_height = TILE_HEIGHT;
    tilemap.tile_width  = TILE_WIDTH;
    tilemap.draw_height = TILEMAP_DRAW_HEIGHT;
    tilemap.draw_width  = TILEMAP_DRAW_WIDTH;
    tilemap.height      = TILEMAP_HEIGHT;
    tilemap.width       = TILEMAP_WIDTH;
    tilemap.y_loc       = Y_OFFSET;
    tilemap.x_loc       = X_OFFSET;

    gfx_Begin();

    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    gfx_SetTransparentColor(0);
    gfx_SetDrawBuffer();
    // END GRAPHICS INIT

    Object Player(player, player_width);
    Player.grid_setPos(2,3);
    // Boxes Init:
    Vector<Object*> boxes(2);
    Vector<bool> box_moved(2);
    boxes.push_back(new Object(box, box_width));
    boxes.push_back(new Object(box, box_width));
    boxes.at(0)->grid_setPos(1,3);
    box_moved.push_back(false);
    boxes.at(1)->grid_setPos(3,4);
    box_moved.push_back(false);
    // Silly lil boolean, as a treat
    bool won = false;
    bool failed_step = false;
    // Vector for undoing

    gfx_Tilemap_NoClip(&tilemap, 0, 0);
    Player.draw();
    gfx_SwapDraw();

    do {

        kb_Scan();

        key = kb_Data[7];
        key_2nd = kb_Data[1];
        key_alpha = kb_Data[2];

        if (key & (kb_Down | kb_Right | kb_Left | kb_Up))
        {
            Game::Direction dir;
            failed_step = false;
            switch (key)
            {
                case kb_Down:
                    dir = Game::Direction::SOUTH;
                    break;
                case kb_Right:
                    dir = Game::Direction::EAST;
                    break;
                case kb_Left:
                    dir = Game::Direction::WEST;
                    break;
                case kb_Up:
                    dir = Game::Direction::NORTH;
                    break;

            }
            Player.move(dir);
            for (int i = 0; i < boxes.length(); i++)
            {
                if (Player.touching(*boxes.at(i)))
                {
                    boxes.at(i)->move(dir);
                    box_moved.set(i, true);
                }
                // Check overlapping boxes
                for (int j = 0; j < boxes.length(); j++)
                {
                    if (j == i) continue;
                    if (boxes.at(i)->touching(*boxes.at(j)) || gfx_GetTileMapped(&tilemap, boxes.at(i)->grid_getX(), boxes.at(i)->grid_getY()) == 1)
                    {
                        boxes.at(i)->move(Game::mirror_dir(dir));
                        box_moved.set(i, false);
                        break;
                    }
                }
                if (Player.touching(*boxes.at(i))){
                    Player.move(Game::mirror_dir(dir));
                    failed_step = true;
                    break;
                }
            }
            if (gfx_GetTileMapped(&tilemap, Player.grid_getX(), Player.grid_getY()) == 1) {
                failed_step = true;
                Player.move(Game::mirror_dir(dir));
            }
            b_c = 0;
            for (int i = 0; i < boxes.length(); i++)
            {
                if (gfx_GetTileMapped(&tilemap, boxes.at(i)->grid_getX(), boxes.at(i)->grid_getY()) == 2)
                {
                    b_c++;
                }
            }

            if (!failed_step) {
                Player.add_step(dir);
                for (int i = 0; i < boxes.length(); i++)
                {
                    if (box_moved.at(i))
                    {
                        boxes.at(i)->add_step(dir);
                        box_moved.set(i, false);
                    } else {
                        boxes.at(i)->add_step(Game::Direction::NONE);
                    }
                }
            }

            b_c = 0;
            for (int i = 0; i < boxes.length(); i++)
            {
                if (gfx_GetTileMapped(&tilemap, boxes.at(i)->grid_getX(), boxes.at(i)->grid_getY()) == 2)
                {
                    b_c++;
                }
            }

            gfx_Tilemap_NoClip(&tilemap, 0, 0);
            Player.draw();
            gfx_SwapDraw();

            // Until a directional key is released...
            while (key & (kb_Down | kb_Right | kb_Left | kb_Up))
            {
                kb_Scan();
                key = kb_Data[7];  // Draws to the screen
            }
            if (b_c == boxes.length())
            {
                won = true;
            }
        } else if (key_2nd & kb_2nd && Player.num_steps() > 0) {
            Player.undo_step();
            for (int i = 0; i < boxes.length(); i++)
            {
                boxes.at(i)->undo_step();
            }
            gfx_Tilemap_NoClip(&tilemap, 0, 0);
            Player.draw();
            gfx_SwapDraw();
            while (key_2nd & kb_2nd)
            {
                kb_Scan();
                key_2nd = kb_Data[1];
            }
        } else if (key_alpha & kb_Alpha)
        {
            // Reset Code
            while(Player.num_steps() > 0) {
                Player.undo_step();
            }
            for (int i = 0; i < boxes.length(); i++) {
                while (boxes.at(i)->num_steps() > 0)
                {
                    boxes.at(i)->undo_step();
                }
            }
            gfx_Tilemap_NoClip(&tilemap, 0, 0);
            Player.draw();
            gfx_SwapDraw();
            while (key_alpha & kb_Alpha) {
                kb_Scan();
                key_alpha = kb_Data[2];
            }
        }
        /**

        */



    } while (kb_Data[1] != kb_Mode && !won);

    gfx_End();

    return 0;
}
