#pragma once

#include "CommandInterface.h"
#include "MoveCommand.h"

namespace Game
{
class CreateAndMoveCommand : public CommandInterface
{
public:
    CreateAndMoveCommand( ) = default;
    ~CreateAndMoveCommand( ) = default;

    bool is_valid( const GameState& state ) const override;
    bool is_finished( const GameState& state ) const override;
    void apply( GameState& state ) override;
    void undo( GameState& state ) override;

private:
    std::vector< MoveCommandSharedPtr > m_falling_tiles;
};

using CreateAndMoveCommandSharedPtr = std::shared_ptr< CreateAndMoveCommand >;
}