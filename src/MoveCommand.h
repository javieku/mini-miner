#pragma once

#include "CommandInterface.h"
#include "Gameplay.h"

namespace Game
{
class MoveCommand : public CommandInterface
{
public:
    enum Direction
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    MoveCommand( const CellPosition& position, const Coordinates& to )
    {
    }

    bool is_valid( Gameplay& gameplay ) const {};

    bool is_finished( Gameplay& gameplay ) const {};

    bool
    apply( Gameplay& gameplay ) const
    {

    };

private:
    Direction direction;
    CellPosition position;
    float tox, toy;
};
}