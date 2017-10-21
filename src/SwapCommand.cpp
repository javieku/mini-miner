#include "SwapCommand.h"

// Game
#include "MoveCommand.h"

// Standard
#include <iostream>
#include <memory>

namespace Game
{
SwapCommand::SwapCommand( const Coordinates& one, const Coordinates& other )
    : m_one_coordinate( one )
    , m_other_coordinate( other )
    , first_time( true )
{
}

SwapCommand::~SwapCommand( )
{
}

bool
SwapCommand::is_valid( const GameState& state ) const
{
    const auto& one = state.board( ).position_of_gem( m_one_coordinate.x, m_one_coordinate.y );
    const auto& other
        = state.board( ).position_of_gem( m_other_coordinate.x, m_other_coordinate.y );

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

    if ( first_time )
    {
        Gem gem1 = state.board( ).copy_gem( m_one_coordinate.x, m_one_coordinate.y );
        Gem gem2 = state.board( ).copy_gem( m_other_coordinate.x, m_other_coordinate.y );

        m_move1 = std::make_shared< MoveCommand >( gem1, Coordinates( {gem2.x, gem2.y} ) );
        m_move2 = std::make_shared< MoveCommand >( gem2, Coordinates( {gem1.x, gem1.y} ) );
        first_time = false;
    }

    m_move1->apply( state );
    m_move2->apply( state );
}

void
SwapCommand::undo( GameState& state )
{
    if ( !m_move1 || !m_move2 )
        return;
    m_move1->undo( state );
    m_move2->undo( state );
}
}