#ifndef TYPES_HPP
#define TYPES_HPP

namespace Game {
    enum class Direction {
        NONE, // 0
        NORTH, // 1
        EAST, // 2
        SOUTH, // 3
        WEST // 4

    };

    inline Direction mirror_dir(Direction dir)
    {
        switch(dir)
        {
            case Direction::NORTH:
                return Direction::SOUTH;
            case Direction::EAST:
                return Direction::WEST;
            case Direction::SOUTH:
                return Direction::NORTH;
            case Direction::WEST:
                return Direction::EAST;
            default:
                return Direction::NONE;
        }
    }
}

#endif
