#include "Gameplay.h"

#include <algorithm>
#include <cstdlib>  // std::rand
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>

namespace Game
{
namespace
{
const int32_t BOARD_WIDTH = 400;
const int32_t BOARD_HEIGHT = 400;

}  // anonymous namespace

Gameplay::Gameplay( )
{
    init_board( BOARD_WIDTH, BOARD_HEIGHT );
}

King::Engine::Texture
Gameplay::generate_texture_type( int row, int col )
{
    std::set< King::Engine::Texture > black_listed_cell_types;
    if ( row > 0 )
    {
        black_listed_cell_types.insert( m_board[ row - 1 ][ col ].texture );
    }

    if ( row + 1 < NROW )
    {
        black_listed_cell_types.insert( m_board[ row + 1 ][ col ].texture );
    }

    if ( col > 0 )
    {
        black_listed_cell_types.insert( m_board[ row ][ col - 1 ].texture );
    }

    if ( col + 1 < NCOL )
    {
        black_listed_cell_types.insert( m_board[ row ][ col + 1 ].texture );
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
Gameplay::init_board( float width, float height )
{
    m_board.resize( NROW );

    x_board = 300;
    y_board = 80;

    float base_row = height / NROW;
    float base_col = width / NCOL;

    for ( int32_t row = 0; row < NROW; ++row )
    {
        m_board[ row ].resize( NCOL );

        for ( int32_t col = 0; col < NCOL; ++col )
        {
            Cell& cell = m_board[ row ][ col ];
            cell.texture = King::Engine::TEXTURE_MAX;

            cell.x = x_board + base_col * col + ( base_col / 4 );
            cell.y = y_board + base_row * row + ( base_row / 4 );
        }
    }

    for ( int32_t row = 0; row < NROW; ++row )
    {
        for ( int32_t col = 0; col < NCOL; ++col )
        {
            Cell& cell = m_board[ row ][ col ];
            cell.texture = generate_texture_type( row, col );
        }
    }
}

Gameplay::~Gameplay( )
{
}

const Entity&
Gameplay::background( ) const
{
    return {0.0f, 0.0f, King::Engine::TEXTURE_BACKGROUND};
}

const Score&
Gameplay::score( ) const
{
    return m_score;
}

const Timer&
Gameplay::timer( ) const
{
    return m_timer;
}

const Cell&
Gameplay::cell( int32_t row, int32_t col ) const
{
    return m_board[ row ][ col ];
};

Cell&
Gameplay::cell( float x, float y )
{
    const auto& pos = cell_position( x, y );

    return m_board[ pos.row ][ pos.col ];
}

Cell
Gameplay::copy_cell( float x, float y )
{
    const auto& pos = cell_position( x, y );

    return m_board[ pos.row ][ pos.col ];
}

const CellPosition&
Gameplay::cell_position( float x, float y ) const
{
    float tile_width = BOARD_WIDTH / NCOL;
    int col = ( x - x_board ) / tile_width;

    float tile_height = BOARD_HEIGHT / NROW;
    int row = ( y - y_board ) / tile_height;

    return {row, col};
}

const Board&
Gameplay::board( ) const
{
    return m_board;
}

Board&
Gameplay::board( )
{
    return m_board;
}

std::string
to_string( const Cell& cell )
{
    std::ostringstream oss;

    oss << "cell{ "
        << "texture=" << cell.texture << ", "
        << "x=" << cell.x << ", "
        << "y=" << cell.y << " }";

    oss.str( );
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
Gameplay::print( )
{
    for ( int row = 0; row < m_board.size( ); ++row )
    {
        for ( int col = 0; col < m_board[ row ].size( ); ++col )
        {
            std::cout << to_string( m_board[ row ][ col ].texture ) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------" << std::endl;
}

bool
Gameplay::is_finished( ) const
{
    return m_timer.elapsed( ) == 60;
}

void
Gameplay::increase_score( )
{
    m_score.score += 50;
}
}