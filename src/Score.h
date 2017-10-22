#pragma once

// Game
#include "Entity.h"

// Standard
#include <string>

namespace Game
{
class Score : public Entity
{
public:
    Score( const Coordinates c, const std::string& t )
        : Entity( c )
        , text( t )
        , score( 0u ){};

    inline void
    Score::increase( const int32_t factor = 1 )
    {
        score += factor * 50;
    }

public:
    std::string text;
    int score;
};
}