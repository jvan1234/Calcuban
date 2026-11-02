#include "Object.hpp"
#include "game/Game.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <graphx.h>
#include <string.h>

uint8_t Object::max_num_objs = 16;
Object** Object::objs = new Object*[max_num_objs];
uint8_t Object::num_objs = 0;

Object::Object(gfx_sprite_t* img, uint8_t img_width)
{
    // Sets the init pos to 0,0
    this->tile_x = 0;
    this->tile_y = 0;
    // Set image data
    this->img = img;
    this->img_width = img_width;
    // Allocates memory in the objs array for the new object
    if (num_objs < max_num_objs)
    {
        objs[num_objs] = this;
        num_objs++;
    }


    // Initializes the undo list
    this->prev_steps = new Game::Direction[MAX_STEPS];
    this->num_prev_steps = 0;

    this->last_dir = Game::Direction::NONE;
}

Object::~Object()
{
    for (int i = 0; i < num_objs; i++)
    {
        if (objs[i] == this) {
            // Start index: i
            // End index: num_objs
            int remainder = num_objs - i - 1;
            if (remainder > 0) // Object is not at the end of the list
            {
                memmove(&objs[i], &objs[i+1], sizeof(Object*) * remainder);
            }
            num_objs--;
            objs[num_objs] = nullptr;
            break;
        }
    }
    delete[] prev_steps;
    prev_steps = nullptr;

}

void Object::End() {
    delete[] objs;
}

void Object::Draw() {
    for (int i = 0; i < num_objs; i++)
    {
        gfx_TransparentSprite_NoClip(objs[i]->img, (int)(objs[i]->tile_x * objs[i]->img_width), objs[i]->tile_y * objs[i]->img_width);
    }
}

void Object::Move(Game::Direction dir)
{
    switch (dir) {
        case Game::Direction::NORTH:
            tile_y -= 1;
            break;
        case Game::Direction::EAST:
            tile_x += 1;
            break;
        case Game::Direction::SOUTH:
            tile_y += 1;
            break;
        case Game::Direction::WEST:
            tile_x -= 1;
            break;
        case Game::Direction::NONE:
            break;
    }
    last_dir = dir;
}

bool Object::OverlapsAny() const {
    for (int i = 0; i < num_objs; i++)
    {
        if (objs[i] != this)
        {
            // We know its a different object
            if (objs[i]->tile_x == tile_x && objs[i]->tile_y == tile_y) return true;
        }
    }
    return false;
}

bool Object::Overlaps(const Object &other) const
{
    return other.tile_x == tile_x && other.tile_y == tile_y;
}

bool Object::OverlapsWall(const gfx_tilemap_t *tilemap) const
{
    return gfx_GetTileMapped(tilemap, tile_x, tile_y) == WALL_INDEX;
}

void Object::SetSpawn(uint8_t x, uint8_t y)
{
    spawn_x = x;
    spawn_y = y;
    tile_x = spawn_x;
    tile_y = spawn_y;
}

uint8_t Object::OnTile(const gfx_tilemap_t* tilemap) const
{
    return gfx_GetTileMapped(tilemap, tile_x, tile_y);
}

void Object::AddStep() {
    if (num_prev_steps >= MAX_STEPS - 1) {
        for (int i = 1; i < MAX_STEPS; i++)
        {
            prev_steps[i - 1] = prev_steps[i];
        }
        num_prev_steps = MAX_STEPS - 2;
    }; // TODO: Shift list down
    prev_steps[num_prev_steps] = last_dir;
    num_prev_steps++;
    // Reset the last dir to NONE
    last_dir = Game::Direction::NONE;
}

void Object::UndoStep()
{
    if (num_prev_steps > 0)
    {
        num_prev_steps--;
        Move(Game::mirror_dir(prev_steps[num_prev_steps]));
        prev_steps[num_prev_steps] = Game::Direction::NONE;
    }
}

void Object::Reset()
{
    num_prev_steps = 0;
    tile_x = spawn_x;
    tile_y = spawn_y;
    last_dir = Game::Direction::NONE;
}

void Object::InvalidMove() {
    last_dir = Game::Direction::NONE;
}
