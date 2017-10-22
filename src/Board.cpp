#include "Board.h"

// Standard
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>

namespace Game
{
namespace
{
const float BOARD_WIDTH = 400.0f;
const float BOARD_HEIGHT = 400.0f;

}  // anonymous namespace

Board::Board( )
    : Entity( {300u, 80u} )
{
    // TODO GameState should give these
    init_board( BOARD_WIDTH, BOARD_HEIGHT );
}

std::string
to_string( const King::Engine::Texture& texture )
{
    switch ( texture )

    {
    case King::Engine::TEXTURE_BLUE:
        return "B";
    case King::Engine::TEXTURE_GREEN:
        return "G";
    case King::Engine::TEXTURE_PURPLE:
        return "P";
    case King::Engine::TEXTURE_RED:
        return "R";
    case King::Engine::TEXTURE_YELLOW:
        return "Y";
    case King::Engine::TEXTURE_BROKEN:
        return "X";
    case King::Engine::TEXTURE_MAX:
        return "?";
    }
}

void
Board::print( ) const
{
    for ( size_t col = 0; col < m_tiles.size( ); ++col )
    {
        for ( size_t row = 0; row < m_tiles[ col ].size( ); ++row )
        {
            std::cout << to_string( m_tiles[ row ][ col ].texture ) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------" << std::endl;
}

const Tile&
Board::tile( int32_t row, int32_t col ) const
{
    return m_tiles[ col ][ row ];
};

const Tile&
Board::tile( float x, float y ) const
{
    const auto& pos = position_of_tile( x, y );

    return m_tiles[ pos.col ][ pos.row ];
}

Tile
Board::copy_tile( float x, float y )
{
    const auto& pos = position_of_tile( x, y );

    return m_tiles[ pos.col ][ pos.row ];
}

const TilePosition&
Board::position_of_tile( float x, float y ) const
{
    float tile_width = BOARD_WIDTH / NCOL;
    int col = ( x - this->x ) / tile_width;

    float tile_height = BOARD_HEIGHT / NROW;
    int row = ( y - this->y ) / tile_height;

    return {row, col};
}

const Tiles&
Board::tiles( ) const
{
    return m_tiles;
}

Tiles&
Board::tiles( )
{
    return m_tiles;
}

King::Engine::Texture
Board::generate_texture_type( int col, int row )
{
    std::set< King::Engine::Texture > black_listed_tile_types;
    if ( row > 0 )
    {
        black_listed_tile_types.insert( m_tiles[ col ][ row - 1 ].texture );
    }

    if ( row + 1 < NROW )
    {
        black_listed_tile_types.insert( m_tiles[ col ][ row + 1 ].texture );
    }

    if ( col > 0 )
    {
        black_listed_tile_types.insert( m_tiles[ col - 1 ][ row ].texture );
    }

    if ( col + 1 < NCOL )
    {
        black_listed_tile_types.insert( m_tiles[ col + 1 ][ row ].texture );
    }

    std::set< King::Engine::Texture > supported_tile_types
        = {King::Engine::TEXTURE_BLUE, King::Engine::TEXTURE_YELLOW, King::Engine::TEXTURE_RED,
           King::Engine::TEXTURE_GREEN, King::Engine::TEXTURE_PURPLE};

    std::vector< King::Engine::Texture > diff;
    std::set_difference( supported_tile_types.begin( ), supported_tile_types.end( ),
                         black_listed_tile_types.begin( ), black_listed_tile_types.end( ),
                         std::inserter( diff, diff.begin( ) ) );

    return diff[ std::rand( ) % diff.size( ) ];
}

void
Board::init_board( float width, float height )
{
    m_tiles.resize( NROW );

    float base_row = height / NROW;
    float base_col = width / NCOL;

    for ( int32_t col = 0; col < NCOL; ++col )
    {
        for ( int32_t row = 0; row < NROW; ++row )
        {
            Coordinates c;
            c.x = this->x + base_col * col + ( base_col / 4 );
            c.y = this->y + base_row * row + ( base_row / 4 );
            m_tiles[ col ].push_back( Tile( {c} ) );
        }
    }

    for ( int32_t col = 0; col < NCOL; ++col )
    {
        for ( int32_t row = 0; row < NROW; ++row )
        {
            Tile& tile = m_tiles[ col ][ row ];
            tile.texture = generate_texture_type( col, row );
        }
    }
}

Dimension
Board::tile_dimension( ) const
{
    return Dimension( {BOARD_WIDTH / NROW, BOARD_HEIGHT / NCOL} );
}
}