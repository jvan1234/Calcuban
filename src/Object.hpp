#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <graphx.h>
#include "Types.hpp"
#include "Vector.hpp"
class Object {
    public:
        Object(gfx_sprite_t* new_img, short new_img_size);
        Object(const Object& other);
        static void draw();
        short getX() const;
        short getY() const;
        short grid_getX() const;
        short grid_getY() const;
        void grid_setX(short n_x);
        void grid_setY(short n_y);
        void grid_setPos(short n_x, short n_y);
        void move(Game::Direction dir);
        void add_step(Game::Direction dir);
        void undo_step();
        int num_steps() const;
        bool touching(Object& other);
        static Vector<Object*> objs;
    protected:
        short x;
        short y;
        short img_size;
        gfx_sprite_t* img;
        Vector<Game::Direction> prev_steps;
};
#endif
