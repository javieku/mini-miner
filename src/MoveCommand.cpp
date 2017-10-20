#include "MoveCommand.h"

// Standard
#include <iostream>

namespace Game
{
namespace
{
const int32_t DELTA = 1;
}

MoveCommand::MoveCommand( const Gem& gem, const Coordinates& to )
    : m_gem( gem )
    , m_to_coordinates( to )
    , m_store_for_undo( true )
{
}

bool
MoveCommand::is_valid( const GameState& state ) const
{
    return true;
};

bool
MoveCommand::is_finished( const GameState& state ) const
{
    if ( !is_valid( state ) )
    {
        return true;
    }

    const auto& board = state.board_tiles( );
    GemPosition position = state.board( ).position_of_gem( m_to_coordinates.x, m_to_coordinates.y );
    const Gem& gem = board[ position.col ][ position.row ];

    std::cout << "std::abs( m_previous_gem.x - gem.x ) " << std::abs( m_previous_gem.x - gem.x )
              << std::endl;
    std::cout << "std::abs( m_previous_gem.y - gem.y ) " << std::abs( m_previous_gem.y - gem.y )
              << std::endl;

    return ( std::abs( m_previous_gem.x - gem.x ) <= 1 )
           && ( std::abs( m_previous_gem.y - gem.y ) <= 1 );
};

void
MoveCommand::apply( GameState& state )
{
    auto& board = state.board_tiles( );

    if ( m_store_for_undo )
    {
        m_previous_gem = state.board( ).copy_gem( m_to_coordinates.x, m_to_coordinates.y );
        m_store_for_undo = false;

        std::cout << "MoveCommand" << std::endl;
        GemPosition position
            = state.board( ).position_of_gem( m_to_coordinates.x, m_to_coordinates.y );
        state.print( );
        board[ position.col ][ position.row ] = m_gem;
        state.print( );
    }

    GemPosition position = state.board( ).position_of_gem( m_to_coordinates.x, m_to_coordinates.y );
    Gem& gem = board[ position.col ][ position.row ];

    if ( gem.y < m_previous_gem.y )
    {
        gem.y += ( m_previous_gem.y - gem.y ) > DELTA ? DELTA : ( m_previous_gem.y - gem.y );
    }
    else if ( gem.y > m_previous_gem.y )
    {
        gem.y -= ( gem.y - m_previous_gem.y ) > DELTA ? DELTA : ( gem.y - m_previous_gem.y );
    }

    if ( gem.x < m_previous_gem.x )
    {
        gem.x += ( m_previous_gem.x - gem.x ) > DELTA ? DELTA : ( m_previous_gem.x - gem.x );
    }
    else if ( gem.x > m_previous_gem.x )
    {
        gem.x -= ( gem.x - m_previous_gem.x ) > DELTA ? DELTA : ( gem.x - m_previous_gem.x );
    }
};

void
MoveCommand::undo( GameState& state )
{
}
}