#include "Gem.h"

// Engine
#include <king/Engine.h>

// Standard
#include <vector>

namespace Game
{
Gem
Gem::create_random( float x, float y )
{
    std::vector< King::Engine::Texture > supported_gem_types
        = {King::Engine::TEXTURE_BLUE, King::Engine::TEXTURE_YELLOW, King::Engine::TEXTURE_RED,
           King::Engine::TEXTURE_GREEN, King::Engine::TEXTURE_PURPLE};

    Gem new_gem;
    new_gem.texture = supported_gem_types[ std::rand( ) % supported_gem_types.size( ) ];
    new_gem.y = x;
    new_gem.x = y;
    return new_gem;
}
}