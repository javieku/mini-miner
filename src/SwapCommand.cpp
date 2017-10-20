#include "SwapCommand.h"

#include "MoveCommand.h"

#include <iostream>

namespace Game
{
namespace
{
const int32_t DELTA = 5;
}

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

    state.print( );

    const Gem& one_gem = state.board( ).gem( m_one_coordinate.x, m_one_coordinate.y );
    const Gem& other_gem = state.board( ).gem( m_other_coordinate.x, m_other_coordinate.y );

    std::cout << "std::abs( m_previous_gem_one.x - one_gem.x ) "
              << std::abs( m_previous_one_gem.x - one_gem.x ) << std::endl;
    std::cout << "std::abs( m_previous_gem_one.y - one_gem.y ) "
              << std::abs( m_previous_one_gem.y - one_gem.y ) << std::endl;
    std::cout << "std::abs( m_previous_gem_other.x - other_gem.x ) "
              << std::abs( m_previous_other_gem.x - other_gem.x ) << std::endl;
    std::cout << "std::abs( m_previous_gem_other.y - other_gem.y  "
              << std::abs( m_previous_other_gem.y - other_gem.y ) << std::endl;

    return ( std::abs( m_previous_one_gem.x - one_gem.x ) <= 1 )
           && ( std::abs( m_previous_one_gem.y - one_gem.y ) <= 1 )
           && ( std::abs( m_previous_other_gem.x - other_gem.x ) <= 1 )
           && ( std::abs( m_previous_other_gem.y - other_gem.y ) <= 1 );
}

void
SwapCommand::move( GameState& state,
                   const GemPosition& one_position,
                   const GemPosition& another_position )
{
    auto& board = state.board_tiles( );

    Gem& one_gem = board[ one_position.col ][ one_position.row ];
    Gem& other_gem = board[ another_position.col ][ another_position.row ];

    if ( one_position.col == another_position.col )
    {
        if ( one_gem.y < m_previous_one_gem.y )
        {
            one_gem.y += DELTA;
        }
        else if ( one_gem.y > m_previous_one_gem.y )
        {
            one_gem.y -= DELTA;
        }

        if ( other_gem.y < m_previous_other_gem.y )
        {
            other_gem.y += DELTA;
        }
        else if ( other_gem.y > m_previous_other_gem.y )
        {
            other_gem.y -= DELTA;
        }
    }
    else if ( one_position.row == another_position.row )
    {
        if ( one_gem.x < m_previous_one_gem.x )
        {
            one_gem.x += DELTA;
        }
        else if ( one_gem.x > m_previous_one_gem.x )
        {
            one_gem.x -= DELTA;
        }

        if ( other_gem.x < m_previous_other_gem.x )
        {
            other_gem.x += DELTA;
        }
        else if ( other_gem.x > m_previous_other_gem.x )
        {
            other_gem.x -= DELTA;
        }
    }
}

void
SwapCommand::apply( GameState& state )
{
    if ( !is_valid( state ) )
    {
        return;
    }

    auto& board = state.board_tiles( );
    if ( first_time )
    {
        m_previous_one_gem = state.board( ).copy_gem( m_one_coordinate.x, m_one_coordinate.y );
        m_previous_other_gem
            = state.board( ).copy_gem( m_other_coordinate.x, m_other_coordinate.y );

        m_one_position = state.board( ).position_of_gem( m_one_coordinate.x, m_one_coordinate.y );
        m_another_position
            = state.board( ).position_of_gem( m_other_coordinate.x, m_other_coordinate.y );

        std::cout << "SwapCommand" << std::endl;
        state.print( );

        Gem aux = board[ m_one_position.col ][ m_one_position.row ];
        board[ m_one_position.col ][ m_one_position.row ]
            = board[ m_another_position.col ][ m_another_position.row ];
        board[ m_another_position.col ][ m_another_position.row ] = aux;
        state.print( );
        first_time = false;
    }

    move( state, m_one_position, m_another_position );
}

void
SwapCommand::undo( GameState& state )
{
    Board& board = state.board( );

    first_time = true;
    Coordinates aux = m_one_coordinate;
    m_one_coordinate = m_other_coordinate;
    m_other_coordinate = aux;

    return apply( state );
}
}