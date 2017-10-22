#pragma once

// Game
#include "CommandInterface.h"
#include "CreateAndMoveCommandCommand.h"
#include "RemoveCommand.h"

namespace Game
{
class CollapseCommand : public CommandInterface
{
public:
    CollapseCommand( );
    ~CollapseCommand( ) = default;

    bool is_valid( const GameState& state ) const override;

    bool is_finished( const GameState& state ) const override;

    void apply( GameState& state ) override;
    void undo( GameState& state ) override;

private:
    CreateAndMoveCommandSharedPtr generate_comand;
    RemoveCommandSharedPtr remove_comand;
};
using CollapseCommandSharedPtr = std::shared_ptr< CollapseCommand >;
}