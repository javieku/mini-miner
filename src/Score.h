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
    {
        this->x = 75u;
        this->y = 225u;
    };

public:
    std::string text = "Score: ";
    int score;
};
}