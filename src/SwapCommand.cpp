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
    const auto& one = state.board( ).cell_position( m_one_coordinate.x, m_one_coordinate.y );
    const auto& other = state.board( ).cell_position( m_other_coordinate.x, m_other_coordinate.y );

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

    const Cell& one_cell = state.board( ).cell( m_one_coordinate.x, m_one_coordinate.y );
    const Cell& other_cell = state.board( ).cell( m_other_coordinate.x, m_other_coordinate.y );

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

void
SwapCommand::move( GameState& state,
                   const CellPosition& one_position,
                   const CellPosition& another_position )
{
    auto& board = state.board_tiles( );

    Cell& one_cell = board[ one_position.col ][ one_position.row ];
    Cell& other_cell = board[ another_position.col ][ another_position.row ];

    if ( one_position.col == another_position.col )
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
    else if ( one_position.row == another_position.row )
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
        m_previous_cell_one = state.board( ).copy_cell( m_one_coordinate.x, m_one_coordinate.y );
        m_previous_cell_other
            = state.board( ).copy_cell( m_other_coordinate.x, m_other_coordinate.y );

        m_one_position = state.board( ).cell_position( m_one_coordinate.x, m_one_coordinate.y );
        m_another_position
            = state.board( ).cell_position( m_other_coordinate.x, m_other_coordinate.y );

        std::cout << "SwapCommand" << std::endl;
        state.print( );

        Cell aux = board[ m_one_position.col ][ m_one_position.row ];
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