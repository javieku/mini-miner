#include "Board.h"

// Standard
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <set>

namespace Game
{
namespace
{
const int32_t BOARD_WIDTH = 400;
const int32_t BOARD_HEIGHT = 400;

}  // anonymous namespace

Board::Board( )
{
    x = 300;
    y = 80;
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

const Cell&
Board::cell( int32_t row, int32_t col ) const
{
    return m_tiles[ col ][ row ];
};

const Cell&
Board::cell( float x, float y ) const
{
    const auto& pos = cell_position( x, y );

    return m_tiles[ pos.col ][ pos.row ];
}

Cell
Board::copy_cell( float x, float y )
{
    const auto& pos = cell_position( x, y );

    return m_tiles[ pos.col ][ pos.row ];
}

const CellPosition&
Board::cell_position( float x, float y ) const
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
    std::set< King::Engine::Texture > black_listed_cell_types;
    if ( row > 0 )
    {
        black_listed_cell_types.insert( m_tiles[ col ][ row - 1 ].texture );
    }

    if ( row + 1 < NROW )
    {
        black_listed_cell_types.insert( m_tiles[ col ][ row + 1 ].texture );
    }

    if ( col > 0 )
    {
        black_listed_cell_types.insert( m_tiles[ col - 1 ][ row ].texture );
    }

    if ( col + 1 < NCOL )
    {
        black_listed_cell_types.insert( m_tiles[ col + 1 ][ row ].texture );
    }

    std::set< King::Engine::Texture > supported_cell_types
        = {King::Engine::TEXTURE_BLUE, King::Engine::TEXTURE_YELLOW, King::Engine::TEXTURE_RED,
           King::Engine::TEXTURE_GREEN, King::Engine::TEXTURE_PURPLE};

    std::vector< King::Engine::Texture > diff;
    std::set_difference( supported_cell_types.begin( ), supported_cell_types.end( ),
                         black_listed_cell_types.begin( ), black_listed_cell_types.end( ),
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
        m_tiles[ col ].resize( NCOL );

        for ( int32_t row = 0; row < NROW; ++row )
        {
            Cell& cell = m_tiles[ col ][ row ];
            cell.texture = King::Engine::TEXTURE_MAX;

            cell.x = this->x + base_col * col + ( base_col / 4 );
            cell.y = this->y + base_row * row + ( base_row / 4 );
        }
    }

    for ( int32_t col = 0; col < NCOL; ++col )
    {
        for ( int32_t row = 0; row < NROW; ++row )
        {
            Cell& cell = m_tiles[ col ][ row ];
            cell.texture = generate_texture_type( col, row );
        }
    }
}
}