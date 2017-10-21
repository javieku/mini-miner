#pragma once

// Game
#include "Coordinates.h"
#include "Entity.h"
#include "Tile.h"

// Engine
#include <king/Engine.h>

// Standard
#include <vector>

namespace Game
{
const unsigned int NROW = 8;
const unsigned int NCOL = 8;

using Colum = std::vector< Tile >;
using Tiles = std::vector< Colum >;

class Board : public Entity
{
public:
    Board( );
    ~Board( ) = default;

    const Tile& tile( int32_t row, int32_t col ) const;
    const Tile& tile( float x, float y ) const;
    Tile copy_tile( float x, float y );
    const TilePosition& position_of_tile( float x, float y ) const;

    const Tiles& tiles( ) const;
    Tiles& tiles( );

    Dimension tile_dimension( ) const;

    void print( ) const;

private:
    void init_board( float width, float height );
    King::Engine::Texture generate_texture_type( int row, int col );

private:
    Tiles m_tiles;
};
}