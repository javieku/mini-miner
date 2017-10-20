#pragma once

// Game
#include "Entity.h"

namespace Game
{
enum class GemState
{
    RED,
    GREEN,
    YELLOW,
    BlUE,
    BROKEN,
    SELECTED
};

struct GemPosition
{
    int row;
    int col;

    inline bool
    is_valid( ) const
    {
        return row >= 0 && col >= 0;
    }
};

class Gem : public Entity
{
public:
    GemState type;

    static Gem create_random( float x, float y );
};
}