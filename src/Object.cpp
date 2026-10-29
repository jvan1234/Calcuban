#include "Object.hpp"
#include "Vector.hpp"
#include <graphx.h>
#include <cmath>

Vector<Object*> Object::objs(1);

Object::Object(gfx_sprite_t* new_img, short new_img_size)
{
    this->x = 0;
    this->y = 0;

    this->img = new_img;
    this->img_size = new_img_size;

    objs.push_back(this);
}

Object::Object(const Object& other)
{
    this->x = 0;
    this->y = 0;

    this->img = other.img;
    this->img_size = other.img_size;

    objs.push_back(this);
}

void Object::draw()
{
    for (int i = 0; i < objs.length(); i++)
    {
        gfx_TransparentSprite_NoClip(objs.at(i)->img, objs.at(i)->x, objs.at(i)->y);
    }

}

short Object::grid_getX() const
{
    return floor(x / img_size);
}

short Object::getX() const {
    return x;
}

short Object::grid_getY() const
{
    return floor(y / img_size);
}

short Object::getY() const
{
    return y;
}

void Object::move(Game::Direction dir)
{
    switch(dir)
    {
        case Game::Direction::NORTH:
            if (y > 0) y -= img_size;
            break;
        case Game::Direction::EAST:
            if (x < (GFX_LCD_WIDTH - img_size * 2)) x += img_size;
            break;
        case Game::Direction::SOUTH:
            if (y < (GFX_LCD_HEIGHT - img_size)) y += img_size;
            break;
        case Game::Direction::WEST:
            if (x > 0) x -= img_size;
            break;
    }
}

bool Object::touching(Object& other)
{
    return x == other.getX() && y == other.getY();
}

void Object::grid_setX(short n_x)
{
    x = img_size * n_x;
}

void Object::grid_setY(short n_y)
{
    y = img_size * n_y;
}

void Object::grid_setPos(short n_x, short n_y)
{
    x = img_size * n_x;
    y = img_size * n_y;
}
