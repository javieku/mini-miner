#pragma once

#include "CommandInterface.h"
#include "GameState.h"

namespace Game
{
class MoveCommand;

class SwapCommand : public CommandInterface
{
public:
    SwapCommand( const Coordinates& one, const Coordinates& other );
    ~SwapCommand( );

    bool is_valid( const GameState& state ) const override;

    bool is_finished( const GameState& state ) const override;

    void apply( GameState& state ) override;

    void undo( GameState& state ) override;

private:
    void move( GameState& state,
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