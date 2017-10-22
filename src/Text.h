#pragma once

// Game
#include "Entity.h"

// Standard
#include <string>

namespace Game
{
// TODO Part of this could be engine functionality (visible, rotation factor)
class Text : public Entity
{
public:
    Text( const Coordinates& c, const std::string t )
        : Entity( c )
        , text( t )
        , visible( false )
        , rotation_factor( 0.0 )
    {
    }

public:
    bool visible;
    float rotation_factor;
    std::string text;
};
}