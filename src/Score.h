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
    Score( )
        : Entity( {75u, 225u} )
    {
        this->text = "Score: ";
        this->score = 0u;
    };

    inline void
    Score::increase( const int32_t factor = 1 )
    {
        score += factor * 50;
    }

public:
    std::string text = "Score: ";
    int score;
};
}