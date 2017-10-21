#include "MoveCommand.h"

// Game
#include "Utils.h"

// Standard
#include <iostream>

namespace Game
{
namespace
{
const int32_t DELTA = 4;
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

    std::cout << " Distance to x:" << std::abs( m_previous_gem.x - gem.x )
              << "y : " << std::abs( m_previous_gem.y - gem.y ) << std::endl;

    return ( std::abs( m_previous_gem.x - gem.x ) <= 0.5 )
           && ( std::abs( m_previous_gem.y - gem.y ) <= 0.5 );
};

void
MoveCommand::apply( GameState& state )
{
    auto& board = state.board_tiles( );

    if ( m_store_for_undo )
    {
        std::cout << "Applying MoveCommand" << std::endl;
        state.print( );

        m_previous_gem = state.board( ).copy_gem( m_to_coordinates.x, m_to_coordinates.y );
        m_store_for_undo = false;

        GemPosition pos = state.board( ).position_of_gem( m_to_coordinates.x, m_to_coordinates.y );
        board[ pos.col ][ pos.row ] = m_gem;

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
    Board& board = state.board( );
    Coordinates aux;

    Coordinates cell_coordinate = Utils::to_tile_coordinates(
        m_to_coordinates, Coordinates( {board.x, board.y} ), state.board( ).tile_dimension( ) );

    aux.x = m_gem.x;
    aux.y = m_gem.y;
    m_gem.x = cell_coordinate.x;
    m_gem.y = cell_coordinate.y;
    m_to_coordinates.x = aux.x;
    m_to_coordinates.y = aux.y;
    m_store_for_undo = true;
    apply( state );
}
}