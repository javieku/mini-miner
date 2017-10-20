#pragma once

// Game
#include "Entity.h"
#include "Gem.h"

// Engine
#include <king/Engine.h>

// Standard
#include <vector>

namespace Game
{
const unsigned int NROW = 8;
const unsigned int NCOL = 8;

using Colum = std::vector< Gem >;
using Tiles = std::vector< Colum >;

class Board : Entity
{
public:
    Board( );
    ~Board( ) = default;

    const Gem& gem( int32_t row, int32_t col ) const;
    const Gem& gem( float x, float y ) const;
    Gem copy_gem( float x, float y );
    const GemPosition& position_of_gem( float x, float y ) const;

    const Tiles& tiles( ) const;
    Tiles& tiles( );

    void print( ) const;

private:
    void init_board( float width, float height );
    King::Engine::Texture generate_texture_type( int row, int col );

private:
    Tiles m_tiles;
};
}