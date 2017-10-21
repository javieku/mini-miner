#include "Tile.h"

// Engine
#include <king/Engine.h>

// Standard
#include <vector>

namespace Game
{
Tile
Tile::create_random( float x, float y )
{
    std::vector< King::Engine::Texture > supported_tile_types
        = {King::Engine::TEXTURE_BLUE, King::Engine::TEXTURE_YELLOW, King::Engine::TEXTURE_RED,
           King::Engine::TEXTURE_GREEN, King::Engine::TEXTURE_PURPLE};

    Tile tile;
    tile.texture = supported_tile_types[ std::rand( ) % supported_tile_types.size( ) ];
    tile.y = x;
    tile.x = y;
    return tile;
}
}