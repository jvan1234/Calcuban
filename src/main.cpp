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

Game::Direction mirror_dir(Game::Direction dir)
{
    switch(dir)
    {
        case Game::Direction::NORTH:
            return Game::Direction::SOUTH;
        case Game::Direction::EAST:
            return Game::Direction::WEST;
        case Game::Direction::SOUTH:
            return Game::Direction::NORTH;
        case Game::Direction::WEST:
            return Game::Direction::EAST;
    }
    return Game::Direction::WEST; // Assumed failsafe
}

int main(void)
{
    // KEY PRESSED REGISTER
    kb_key_t key;
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
    boxes.push_back(new Object(box, box_width));
    boxes.push_back(new Object(box, box_width));
    boxes.at(0)->grid_setPos(1,3);
    boxes.at(1)->grid_setPos(3,4);
    // Silly lil boolean, as a treat
    bool won = false;


    gfx_Tilemap_NoClip(&tilemap, 0, 0);
    Player.draw();
    gfx_SwapDraw();

    do {

        kb_Scan();

        key = kb_Data[7];

        if (key & (kb_Down | kb_Right | kb_Left | kb_Up))
        {
            Game::Direction dir;
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
                if (Player.touching(*boxes.at(i))) boxes.at(i)->move(dir);
                // Check overlapping boxes
                for (int j = 0; j < boxes.length(); j++)
                {
                    if (j == i) continue;
                    if (boxes.at(i)->touching(*boxes.at(j)) || gfx_GetTileMapped(&tilemap, boxes.at(i)->grid_getX(), boxes.at(i)->grid_getY()) == 1)
                    {
                        boxes.at(i)->move(mirror_dir(dir));
                        break;
                    }
                }
                if (Player.touching(*boxes.at(i))){
                    Player.move(mirror_dir(dir));
                    break;
                }
            }
            if (gfx_GetTileMapped(&tilemap, Player.grid_getX(), Player.grid_getY()) == 1) Player.move(mirror_dir(dir));
            b_c = 0;
            for (int i = 0; i < boxes.length(); i++)
            {
                if (gfx_GetTileMapped(&tilemap, boxes.at(i)->grid_getX(), boxes.at(i)->grid_getY()) == 2)
                {
                    b_c++;
                }
            }

            // Draws to the screen
            gfx_Tilemap_NoClip(&tilemap, 0, 0);
            Player.draw();
            gfx_SwapDraw();


            // Until a directional key is released...
            while (key & (kb_Down | kb_Right | kb_Left | kb_Up))
            {
                kb_Scan();
                key = kb_Data[7];
            }
            if (b_c == boxes.length())
            {
                won = true;
            }
        }
        /**

        */



    } while (kb_Data[1] != kb_Mode && !won);

    gfx_End();

    return 0;
}
