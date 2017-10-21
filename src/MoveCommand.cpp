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
    : m_tile( tile )
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
    const auto& board = state.board_tiles( );
    TilePosition position
        = state.board( ).position_of_tile( m_to_coordinates.x, m_to_coordinates.y );
    const Tile& tile = board[ position.col ][ position.row ];

    std::cout << " Distance to x:" << std::abs( m_previous_tile.x - tile.x )
              << "y : " << std::abs( m_previous_tile.y - tile.y ) << std::endl;

    return ( std::abs( m_previous_tile.x - tile.x ) <= 0.5 )
           && ( std::abs( m_previous_tile.y - tile.y ) <= 0.5 );
};

void
MoveCommand::apply( GameState& state )
{
    auto& board = state.board_tiles( );

    if ( m_store_for_undo )
    {
        std::cout << "Applying MoveCommand" << std::endl;
        state.print( );

        m_previous_tile = state.board( ).copy_tile( m_to_coordinates.x, m_to_coordinates.y );
        m_store_for_undo = false;

        TilePosition pos
            = state.board( ).position_of_tile( m_to_coordinates.x, m_to_coordinates.y );
        board[ pos.col ][ pos.row ] = m_tile;

        state.print( );
    }

    TilePosition position
        = state.board( ).position_of_tile( m_to_coordinates.x, m_to_coordinates.y );
    Tile& tile = board[ position.col ][ position.row ];

    if ( tile.y < m_previous_tile.y )
    {
        tile.y += ( m_previous_tile.y - tile.y ) > DELTA ? DELTA : ( m_previous_tile.y - tile.y );
    }
    else if ( tile.y > m_previous_tile.y )
    {
        tile.y -= ( tile.y - m_previous_tile.y ) > DELTA ? DELTA : ( tile.y - m_previous_tile.y );
    }

    if ( tile.x < m_previous_tile.x )
    {
        tile.x += ( m_previous_tile.x - tile.x ) > DELTA ? DELTA : ( m_previous_tile.x - tile.x );
    }
    else if ( tile.x > m_previous_tile.x )
    {
        tile.x -= ( tile.x - m_previous_tile.x ) > DELTA ? DELTA : ( tile.x - m_previous_tile.x );
    }
};

void
MoveCommand::undo( GameState& state )
{
    Board& board = state.board( );
    Coordinates aux;

    Coordinates tile_coordinate = Utils::to_tile_coordinates(
        m_to_coordinates, Coordinates( {board.x, board.y} ), state.board( ).tile_dimension( ) );

    aux.x = m_tile.x;
    aux.y = m_tile.y;
    m_tile.x = tile_coordinate.x;
    m_tile.y = tile_coordinate.y;
    m_to_coordinates.x = aux.x;
    m_to_coordinates.y = aux.y;
    m_store_for_undo = true;
    apply( state );
}
}