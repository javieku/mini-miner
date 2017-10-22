#pragma once

// Game
#include "Text.h"

// Standard
#include <string>

namespace Game
{
class Score : public Text
{
public:
    Score( const Coordinates c, const std::string& t )
        : Text( c, t )
        , score( 0u )
    {
    }

    inline void
    Score::increase( const int32_t factor = 1 )
    {
        score += factor * 50;
    }

public:
    int score;
};
}