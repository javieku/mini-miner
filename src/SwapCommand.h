#pragma once

#include "CommandInterface.h"
#include "MoveCommand.h"

namespace Game
{
class GameState;

/**
 * Given two coordinates from an input event swaps
 * two items on the board.
 *
 * It is finished when both cells are exchanged.
 *
 * It is not valid when the given coordinates selected
 * non-consecutive tiles.
 *
 * The swap movement can be undone in case this operation
 * is considered illegal. This happens when once the tiles
 * are swapped no tile can be collapsed.
 *
 **/
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
    Coordinates m_event_pos;
    Coordinates m_other_event_pos;

    MoveCommandSharedPtr m_move2;
    MoveCommandSharedPtr m_move1;
};
using SwapCommandSharedPtr = std::shared_ptr< SwapCommand >;
}