#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "game/Game.hpp"
#include <cstdint>
#include <graphx.h>


class Object {
    protected:
        uint8_t tile_x;
        uint8_t tile_y;
        uint8_t spawn_x;
        uint8_t spawn_y;
        gfx_sprite_t* img;
        uint8_t img_width;
        // Undo
        Game::Direction* prev_steps;
        uint16_t num_prev_steps;
        Game::Direction last_dir;


        static constexpr uint16_t MAX_STEPS = 256;
    public:
        Object(gfx_sprite_t* img, uint8_t img_width);
        ~Object();
        static void End(); // Frees Memory
        static void Draw();
        void SetSpawn(uint8_t x, uint8_t y);
        void Move(Game::Direction dir);
        // Overlap checks
        bool OverlapsAny() const;
        bool Overlaps(const Object& other) const;
        bool OverlapsWall(const gfx_tilemap_t* tilemap) const;
        uint8_t OnTile(const gfx_tilemap_t* tilemap) const;
        // Undo History
        void AddStep();
        void UndoStep();
        void Reset();
        void InvalidMove();
        // Object Handling/Memory
        static Object** objs;
        static uint8_t num_objs;
        static uint8_t max_num_objs;
};

#endif
