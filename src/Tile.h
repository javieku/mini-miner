#pragma once

// Game
#include "Entity.h"

namespace Game
{
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
/**
 * Simple model to represent one of the items in the board.
 **/
class Tile : public Entity
{
public:
    Tile( const Coordinates& c );
    Tile( const Coordinates& c, King::Engine::Texture texture );

    static Tile create_random( float x, float y );
};
}