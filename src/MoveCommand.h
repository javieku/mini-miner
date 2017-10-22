#pragma once

#include "Board.h"
#include "CommandInterface.h"
#include "Coordinates.h"
#include "GameState.h"

namespace Game
{
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

    // Undo
    Tile m_previous_tile;
    bool m_update_board;
};

using MoveCommandSharedPtr = std::shared_ptr< MoveCommand >;
}