#include "SwapCommand.h"

// Game
#include "MoveCommand.h"
#include "Tile.h"

// Standard
#include <iostream>
#include <memory>

namespace Game
{
SwapCommand::SwapCommand( const Coordinates& one, const Coordinates& other )
    : m_one_coordinate( one )
    , m_other_coordinate( other )
{
}

SwapCommand::~SwapCommand( )
{
}

bool
SwapCommand::is_valid( const GameState& state ) const
{
    const auto& board = state.board( );

    const TilePosition& one = board.position_of_tile( m_one_coordinate );
    const TilePosition& other = board.position_of_tile( m_other_coordinate );

    if ( !one.is_valid( ) || !other.is_valid( ) )
    {
        return false;
    }

    return ( one.col == other.col && std::abs( one.row - other.row ) <= 1 )
           || ( one.row == other.row && std::abs( one.col - other.col ) <= 1 );
}

bool
SwapCommand::is_finished( const GameState& state ) const
{
    if ( !is_valid( state ) )
    {
        return true;
    }
    if ( !m_move1 || !m_move2 )
    {
        return false;
    }

    return m_move1->is_finished( state ) && m_move2->is_finished( state );
}

void
SwapCommand::apply( GameState& state )
{
    if ( !is_valid( state ) )
    {
        return;
    }

    if ( !m_move1 || !m_move2 )
    {
        Tile other_tile = state.board( ).copy_tile( m_one_coordinate );
        Tile tile = state.board( ).copy_tile( m_other_coordinate );

        m_move1 = std::make_shared< MoveCommand >( other_tile, Coordinates( {tile.x, tile.y} ) );
        m_move2
            = std::make_shared< MoveCommand >( tile, Coordinates( {other_tile.x, other_tile.y} ) );
    }
    else
    {
        m_move1->apply( state );
        m_move2->apply( state );
    }
}

void
SwapCommand::undo( GameState& state )
{
    if ( !m_move1 || !m_move2 || !is_valid( state ) )
        return;
    m_move1->undo( state );
    m_move2->undo( state );
}
}