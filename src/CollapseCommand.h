#pragma once

// Game
#include "CommandInterface.h"
#include "CreateAndMoveCommand.h"
#include "RemoveCommand.h"

namespace Game
{
/**
 *  Combines RemoveCommand and CreateAndMoveCommandCommand to implement
 *  the logic of creating and removing tiles after an user action that
 *  collapsed some  of the items in the board.
 *
 * It is finished once removal can't not remove more tiles in the board.
 *
 * It is valid when RemoveCommand and CreateAndMoveCommand are valid.
 *
 **/
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