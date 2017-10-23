#pragma once

#include "CommandInterface.h"
#include "MoveCommand.h"

namespace Game
{
/**
 * Given a Board where some tiles have been already
 * removed, it collapses the tiles above the ones removed
 * and creates new ones.
 *
 * It is finished when no tile is in movement anymore and all the
 * tiles in the board have some content.
 *
 * It is valid for every GameState.
 *
 * ----Implementation comments----
 * It uses std::stable_partition to move the broken tiles to the top of
 * the column:
 *
 *  X = Broken
 *
 *     1 2 3 8 3        X 2 3 8 3
 *     X 4 5 9 2        X 4 5 9 2
 *     X 6 7 1 4  ----> X 6 7 1 4
 *     X 2 3 4 1        1 2 3 4 1
 *	   4 1 2 3 5        4 1 2 3 5
 *
 *  Once the board is updated it creates a MoveCommand for every tile that
 *  either is new or has to be moved down.
 *
 **/
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