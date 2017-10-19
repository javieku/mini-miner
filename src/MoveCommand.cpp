#include "MoveCommand.h"

#include <iostream>

namespace Game
{
namespace
{
const int32_t DELTA = 5;
}
MoveCommand::MoveCommand( const Cell& cell, const CellPosition& to )
    : m_cell( cell )
    , m_to( to )
    , m_store_for_undo( true )
{
}

bool
MoveCommand::is_valid( Gameplay& gameplay ) const
{
    if ( !m_to.is_valid( ) )
    {
        return false;
    }

    return true;
};

bool
MoveCommand::is_finished( Gameplay& gameplay ) const
{
    if ( !is_valid( gameplay ) )
    {
        return true;
    }
    Board& board = gameplay.board( );
    Cell& cell = board[ m_to.col ][ m_to.row ];
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
    Board& board = gameplay.board( );
    if ( m_store_for_undo )
    {
        m_previous_cell = board[ m_to.col ][ m_to.row ];
        m_store_for_undo = false;
        std::cout << "MoveCommand" << std::endl;
        gameplay.print( );
        board[ m_to.col ][ m_to.row ] = m_cell;
        gameplay.print( );
    }

    Cell& cell = board[ m_to.col ][ m_to.row ];

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
        cell.x += DELTA;
    }
    else if ( cell.x > m_previous_cell.x )
    {
        cell.x -= DELTA;
    }
    return true;
};

bool
MoveCommand::undo( Gameplay& gameplay )
{
    return false;
}
}