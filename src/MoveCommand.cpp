#include "MoveCommand.h"

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
MoveCommand::is_valid( const Gameplay& gameplay ) const
{
    return true;
};

bool
MoveCommand::is_finished( const Gameplay& gameplay ) const
{
    if ( !is_valid( gameplay ) )
    {
        return true;
    }

    const auto& board = gameplay.board_tiles( );
    CellPosition position
        = gameplay.board( ).cell_position( m_to_coordinates.x, m_to_coordinates.y );
    const Cell& cell = board[ position.col ][ position.row ];

    std::cout << "std::abs( m_previous_cell.x - cell.x ) " << std::abs( m_previous_cell.x - cell.x )
              << std::endl;
    std::cout << "std::abs( m_previous_cell.y - cell.y ) " << std::abs( m_previous_cell.y - cell.y )
              << std::endl;

    return ( std::abs( m_previous_cell.x - cell.x ) <= 1 )
           && ( std::abs( m_previous_cell.y - cell.y ) <= 1 );
};

bool
MoveCommand::apply( Gameplay& gameplay )
{
    auto& board = gameplay.board_tiles( );

    if ( m_store_for_undo )
    {
        m_previous_cell = gameplay.board( ).copy_cell( m_to_coordinates.x, m_to_coordinates.y );
        m_store_for_undo = false;

        std::cout << "MoveCommand" << std::endl;
        CellPosition position
            = gameplay.board( ).cell_position( m_to_coordinates.x, m_to_coordinates.y );
        gameplay.print( );
        board[ position.col ][ position.row ] = m_cell;
        gameplay.print( );
    }

    CellPosition position
        = gameplay.board( ).cell_position( m_to_coordinates.x, m_to_coordinates.y );
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

    return true;
};

bool
MoveCommand::undo( Gameplay& gameplay )
{
    return false;
}
}