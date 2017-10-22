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
using Column = std::vector< Tile >;
using Tiles = std::vector< Column >;

class Board : public Entity
{
public:
    Board( const Coordinates& c, const Dimension& dimensions, int32_t ncol, int32_t nrow );
    ~Board( ) = default;

    const Tile& tile( const TilePosition& pos ) const;
    const Tile& tile( const Coordinates& c ) const;
    Tile copy_tile( const Coordinates& c );
    TilePosition position_of_tile( const Coordinates& c ) const;

    const Tiles& tiles( ) const;
    Tiles& tiles( );

    Dimension tile_dimension( ) const;
	
	// Debugging
    void print( ) const;

private:
    void init_board( const Dimension& dimension, int32_t ncol, int32_t nrow );
    King::Engine::Texture generate_texture_type( int32_t row, int32_t col );

private:
    Tiles m_tiles;
    Dimension m_dimension;
};
}