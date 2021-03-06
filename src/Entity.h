#pragma once

// Game
#include "Coordinates.h"

// Engine
#include <king/Engine.h>

namespace Game
{
/**
 * Abstraction that represents any element in the game.
 *
 * It could be also part of the Engine logic.
 **/
struct Entity
{
    float x;
    float y;
    King::Engine::Texture texture;
    bool visible;

    Entity( const Coordinates& c )
        : Entity( c, King::Engine::TEXTURE_MAX )
    {
    }

    Entity( Coordinates c, King::Engine::Texture texture )
        : x( c.x )
        , y( c.y )
        , texture( texture )
        , visible( true )
    {
    }
};
}