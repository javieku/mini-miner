#include "MoveCommand.h"

// Standard
#include <iostream>

namespace Game
{
namespace
{
const int32_t DELTA = 1;
}

MoveCommand::MoveCommand( const Cell& cell, const Coordinates& to )
    : m_cell( cell )
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
    CellPosition position = state.board( ).cell_position( m_to_coordinates.x, m_to_coordinates.y );
    const Cell& cell = board[ position.col ][ position.row ];

    std::cout << "std::abs( m_previous_cell.x - cell.x ) " << std::abs( m_previous_cell.x - cell.x )
              << std::endl;
    std::cout << "std::abs( m_previous_cell.y - cell.y ) " << std::abs( m_previous_cell.y - cell.y )
              << std::endl;

    return ( std::abs( m_previous_cell.x - cell.x ) <= 1 )
           && ( std::abs( m_previous_cell.y - cell.y ) <= 1 );
};

void
MoveCommand::apply( GameState& state )
{
    auto& board = state.board_tiles( );

    if ( m_store_for_undo )
    {
        m_previous_cell = state.board( ).copy_cell( m_to_coordinates.x, m_to_coordinates.y );
        m_store_for_undo = false;

        std::cout << "MoveCommand" << std::endl;
        CellPosition position
            = state.board( ).cell_position( m_to_coordinates.x, m_to_coordinates.y );
        state.print( );
        board[ position.col ][ position.row ] = m_cell;
        state.print( );
    }

    CellPosition position = state.board( ).cell_position( m_to_coordinates.x, m_to_coordinates.y );
    Cell& cell = board[ position.col ][ position.row ];

    if ( cell.y < m_previous_cell.y )
    {
        cell.y += ( m_previous_cell.y - cell.y ) > DELTA ? DELTA : ( m_previous_cell.y - cell.y );
    }
    else if ( cell.y > m_previous_cell.y )
    {
        cell.y -= ( cell.y - m_previous_cell.y ) > DELTA ? DELTA : ( cell.y - m_previous_cell.y );
    }

    if ( cell.x < m_previous_cell.x )
    {
        cell.x += ( m_previous_cell.x - cell.x ) > DELTA ? DELTA : ( m_previous_cell.x - cell.x );
    }
    else if ( cell.x > m_previous_cell.x )
    {
        cell.x -= ( cell.x - m_previous_cell.x ) > DELTA ? DELTA : ( cell.x - m_previous_cell.x );
    }
};

void
MoveCommand::undo( GameState& state )
{
}
}