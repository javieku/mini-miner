#pragma once

#include "Board.h"
#include "CommandInterface.h"
#include "Coordinates.h"
#include "GameState.h"

namespace Game
{
/**
 * Given the coordinates from an input event and a tile,
 * moves the latter to the former.
 *
 * It is finished when the tiles reaches the given
 * coordinates.
 *
 * It is valid if the given coordinates are valid in 
 * engine the window.
 *
 * Movement can be undone. This is useful to implement
 * SwapCommand.
 *
 **/
class MoveCommand : public CommandInterface
{
public:
    MoveCommand( const Tile& tile, const Coordinates& to );
    ~MoveCommand( ) = default;

    bool is_valid( const GameState& state ) const override;
    bool is_finished( const GameState& state ) const override;
    void apply( GameState& state ) override;
    void undo( GameState& state ) override;

private:
    void move( Tile& tile, const Coordinates& to );

private:
    Coordinates m_to;
    TilePosition m_pos;

    // For Undo
    Tile m_previous_tile;
    bool m_update_board;
};

using MoveCommandSharedPtr = std::shared_ptr< MoveCommand >;
}