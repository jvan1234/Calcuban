#ifndef GAME_HPP
#define GAME_HPP

namespace Game {
    enum class Direction {
        NONE,
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    inline Game::Direction mirror_dir(Game::Direction dir)
    {
        switch (dir) {
            case Game::Direction::NORTH:
                return Game::Direction::SOUTH;
            case Game::Direction::SOUTH:
                return Game::Direction::NORTH;
            case Game::Direction::WEST:
                return Game::Direction::EAST;
            case Game::Direction::EAST:
                return Game::Direction::WEST;
            default:
                return Game::Direction::NONE;
        }
    }
}

#endif
