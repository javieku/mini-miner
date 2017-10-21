#pragma once

// Game
#include "Entity.h"

namespace Game
{
enum class TileState
{
    RED,
    GREEN,
    YELLOW,
    BLUE,
    BROKEN,
    SELECTED
};

struct TilePosition
{
    int row;
    int col;

    inline bool
    is_valid( ) const
    {
        return row >= 0 && col >= 0;
    }
};

class Tile : public Entity
{
public:
    TileState type;

    static Tile create_random( float x, float y );
};
}