#include "MoveCommand.h"

#include <iostream>

namespace Game
{
namespace
{
const int32_t DELTA = 5;
}
MoveCommand::MoveCommand( const CellPosition& from, const CellPosition& to )
    : m_from( from )
    , m_to( to )
    , m_store_for_undo( true )
{
}

bool
MoveCommand::is_valid( Gameplay& gameplay ) const
{
    if ( !m_from.is_valid( ) || !m_to.is_valid( ) )
    {
        return false;
    }

    return ( m_from.col == m_to.col && std::abs( m_from.row - m_to.row ) <= 1 );
};

bool
MoveCommand::is_finished( Gameplay& gameplay ) const
{
    if ( !is_valid( gameplay ) )
    {
        return true;
    }

    Cell& one_cell = gameplay.board( )[ m_from.row ][ m_from.col ];

    std::cout << "std::abs( m_previous_cell_one.x - one_cell.x ) "
              << std::abs( m_previous_cell.x - one_cell.x ) << std::endl;
    std::cout << "std::abs( m_previous_cell_one.y - one_cell.y ) "
              << std::abs( m_previous_cell.y - one_cell.y ) << std::endl;

    return ( std::abs( m_previous_cell.x - one_cell.x ) <= 1 )
           && ( std::abs( m_previous_cell.y - one_cell.y ) <= 1 );
};

bool
MoveCommand::apply( Gameplay& gameplay )
{
    Board& board = gameplay.board( );
    if ( m_store_for_undo )
    {
        m_previous_cell = board[ m_from.row ][ m_from.col ];
        m_store_for_undo = false;

        board[ m_to.row ][ m_to.col ] = board[ m_from.row ][ m_from.col ];
    }

    Cell& from_cell = board[ m_from.row ][ m_from.col ];
    Cell& to_cell = board[ m_from.row ][ m_from.col ];
    if ( m_from.col == m_to.col )
    {
        if ( from_cell.y < to_cell.y )
        {
            from_cell.y += DELTA;
        }
        else if ( from_cell.y > to_cell.y )
        {
            from_cell.y -= DELTA;
        }
    }
    else if ( m_from.row == m_to.row )
    {
        if ( from_cell.x < to_cell.x )
        {
            from_cell.x += DELTA;
        }
        else if ( from_cell.x > to_cell.x )
        {
            from_cell.x -= DELTA;
        }
    }
	return true;
};

bool
MoveCommand::undo( Gameplay& gameplay )
{
    Board& board = gameplay.board( );

    m_store_for_undo = true;
    CellPosition aux = m_from;
    m_from = m_to;
    m_to = aux;

    return apply( gameplay );
}
}