#include "Tile.h"

// Engine
#include <king/Engine.h>

// Standard
#include <vector>

namespace Game
{
Tile::Tile( const Coordinates& c )
    : Entity( c )
{
}

Tile::Tile( const Coordinates& c, King::Engine::Texture texture )
    : Entity( c, texture )
{
}

Tile
Tile::create_random( float x, float y )
{
    std::vector< King::Engine::Texture > supported_tile_types
        = {King::Engine::TEXTURE_BLUE, King::Engine::TEXTURE_YELLOW, King::Engine::TEXTURE_RED,
           King::Engine::TEXTURE_GREEN, King::Engine::TEXTURE_PURPLE};

    auto texture = supported_tile_types[ std::rand( ) % supported_tile_types.size( ) ];

    return Tile( {x, y}, texture );
}
}