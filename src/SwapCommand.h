#pragma once

#include "CommandInterface.h"
#include "Gameplay.h"

namespace Game
{
class MoveCommand;

class SwapCommand : public CommandInterface
{
public:
    SwapCommand( const Coordinates& one, const Coordinates& other );
    ~SwapCommand( );

    bool is_valid( const Gameplay& gameplay ) const override;

    bool is_finished( const Gameplay& gameplay ) const override;

    bool apply( Gameplay& gameplay ) override;

    bool undo( Gameplay& gameplay ) override;

private:
    void move( Gameplay& gameplay,
               const CellPosition& one_position,
               const CellPosition& another_position );

private:
    Coordinates m_one_coordinate;
    Coordinates m_other_coordinate;

    Cell m_previous_cell_one;
    Cell m_previous_cell_other;

    CellPosition m_one_position;
    CellPosition m_another_position;

    bool first_time;

    std::unique_ptr< MoveCommand > move1;
    std::unique_ptr< MoveCommand > move2;
};
using SwapCommandSharedPtr = std::shared_ptr< SwapCommand >;
}