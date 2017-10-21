#pragma once

#include "CommandInterface.h"
#include "GameState.h"
#include "MoveCommand.h"

namespace Game
{
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
    Coordinates m_one_coordinate;
    Coordinates m_other_coordinate;
    bool first_time;

    MoveCommandSharedPtr m_move1;
    MoveCommandSharedPtr m_move2;
};
using SwapCommandSharedPtr = std::shared_ptr< SwapCommand >;
}