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

MoveCommand::MoveCommand( const Tile& tile, const Coordinates& to )
    : m_previous_tile( tile )
    , m_to( to )
    , m_update_board( true )
    , m_pos( {-1, -1} )
{
}

bool
MoveCommand::is_valid( const GameState& state ) const
{
    // Allow move to anywhere in the view
    return true;
};

bool
MoveCommand::is_finished( const GameState& state ) const
{
    if ( !m_pos.is_valid( ) )
    {
        return false;
    }

    const Tile& tile = state.board_tiles( )[ m_pos.col ][ m_pos.row ];

    std::cout << " Distance to destination x: " << std::abs( m_to.x - tile.x )
              << " y: " << std::abs( m_to.y - tile.y ) << std::endl;

    return ( std::abs( m_to.x - tile.x ) <= 0.5 ) && ( std::abs( m_to.y - tile.y ) <= 0.5 );
};

void
MoveCommand::apply( GameState& state )
{
    auto& board = state.board_tiles( );

    if ( m_update_board )
    {
        std::cout << "MoveCommand" << std::endl;
        state.print( );

        m_update_board = false;

        m_pos = state.board( ).position_of_tile( m_to );
        board[ m_pos.col ][ m_pos.row ] = m_previous_tile;

        state.print( );
    }

    Tile& current_tile = board[ m_pos.col ][ m_pos.row ];
    move( current_tile, m_to );
};

void
MoveCommand::undo( GameState& state )
{
    Board& board = state.board( );

    Coordinates tile_coordinate = Utils::to_tile_coordinates(
        m_to, Coordinates( {board.x, board.y} ), board.tile_dimension( ) );

    Coordinates aux;
    aux.x = m_previous_tile.x;
    aux.y = m_previous_tile.y;
    m_previous_tile.x = tile_coordinate.x;
    m_previous_tile.y = tile_coordinate.y;
    m_to.x = aux.x;
    m_to.y = aux.y;

    m_update_board = true;

    apply( state );
}

void
MoveCommand::move( Tile& tile, const Coordinates& to )
{
    if ( tile.y < to.y )
    {
        tile.y += ( to.y - tile.y ) > DELTA ? DELTA : ( to.y - tile.y );
    }
    else if ( tile.y > to.y )
    {
        tile.y -= ( tile.y - to.y ) > DELTA ? DELTA : ( tile.y - to.y );
    }

    if ( tile.x < to.x )
    {
        tile.x += ( to.x - tile.x ) > DELTA ? DELTA : ( to.x - tile.x );
    }
    else if ( tile.x > to.x )
    {
        tile.x -= ( tile.x - to.x ) > DELTA ? DELTA : ( tile.x - to.x );
    }
}
}