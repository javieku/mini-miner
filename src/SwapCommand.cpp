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
SwapCommand::is_valid( Gameplay& gameplay ) const
{
    const auto& one = gameplay.cell_position( m_one_coordinate.x, m_one_coordinate.y );
    const auto& other = gameplay.cell_position( m_other_coordinate.x, m_other_coordinate.y );

    if ( !one.is_valid( ) || !other.is_valid( ) )
    {
        return false;
    }

    return ( one.col == other.col && std::abs( one.row - other.row ) <= 1 )
           || ( one.row == other.row && std::abs( one.col - other.col ) <= 1 );
}

bool
SwapCommand::is_finished( Gameplay& gameplay ) const
{
    std::cout << "is_finished" << std::endl;
    if ( !is_valid( gameplay ) )
    {
        return true;
    }

    Cell& one_cell = gameplay.cell( m_one_coordinate.x, m_one_coordinate.y );
    Cell& other_cell = gameplay.cell( m_other_coordinate.x, m_other_coordinate.y );

    std::cout << "std::abs( m_previous_cell_one.x - one_cell.x ) "
              << std::abs( m_previous_cell_one.x - one_cell.x ) << std::endl;
    std::cout << "std::abs( m_previous_cell_one.y - one_cell.y ) "
              << std::abs( m_previous_cell_one.y - one_cell.y ) << std::endl;
    std::cout << "std::abs( m_previous_cell_other.x - other_cell.x ) "
              << std::abs( m_previous_cell_other.x - other_cell.x ) << std::endl;
    std::cout << "std::abs( m_previous_cell_other.y - other_cell.y  "
              << std::abs( m_previous_cell_other.y - other_cell.y ) << std::endl;

    return ( std::abs( m_previous_cell_one.x - one_cell.x ) <= 1 )
           && ( std::abs( m_previous_cell_one.y - one_cell.y ) <= 1 )
           && ( std::abs( m_previous_cell_other.x - other_cell.x ) <= 1 )
           && ( std::abs( m_previous_cell_other.y - other_cell.y ) <= 1 );
}

bool
SwapCommand::apply( Gameplay& gameplay )
{
    if ( !is_valid( gameplay ) )
    {
        return false;
    }

    Board& board = gameplay.board( );
    if ( first_time )
    {
        m_previous_cell_one = gameplay.copy_cell( m_one_coordinate.x, m_one_coordinate.y );
        m_previous_cell_other = gameplay.copy_cell( m_other_coordinate.x, m_other_coordinate.y );

        m_one_position = gameplay.cell_position( m_one_coordinate.x, m_one_coordinate.y );
        m_another_position = gameplay.cell_position( m_other_coordinate.x, m_other_coordinate.y );

        Cell aux = board[ m_one_position.row ][ m_one_position.col ];
        board[ m_one_position.row ][ m_one_position.col ]
            = board[ m_another_position.row ][ m_another_position.col ];
        board[ m_another_position.row ][ m_another_position.col ] = aux;

        first_time = false;
    }

    Cell& one_cell = board[ m_one_position.row ][ m_one_position.col ];
    Cell& other_cell = board[ m_another_position.row ][ m_another_position.col ];

    if ( m_one_position.col == m_another_position.col )
    {
        if ( one_cell.y < m_previous_cell_one.y )
        {
            one_cell.y += DELTA;
        }
        else if ( one_cell.y > m_previous_cell_one.y )
        {
            one_cell.y -= DELTA;
        }

        if ( other_cell.y < m_previous_cell_other.y )
        {
            other_cell.y += DELTA;
        }
        else if ( other_cell.y > m_previous_cell_other.y )
        {
            other_cell.y -= DELTA;
        }
    }
    else if ( m_one_position.row == m_another_position.row )
    {
        if ( one_cell.x < m_previous_cell_one.x )
        {
            one_cell.x += DELTA;
        }
        else if ( one_cell.x > m_previous_cell_one.x )
        {
            one_cell.x -= DELTA;
        }

        if ( other_cell.x < m_previous_cell_other.x )
        {
            other_cell.x += DELTA;
        }
        else if ( other_cell.x > m_previous_cell_other.x )
        {
            other_cell.x -= DELTA;
        }
    }

    return true;
}

bool
SwapCommand::undo( Gameplay& gameplay )
{
    return true;
}
}