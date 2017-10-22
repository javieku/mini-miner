#include "Board.h"

// Game
#include "Utils.h"

// Standard
#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <string>

namespace Game
{
Board::Board( const Coordinates& c, const Dimension& dimension, int32_t ncol, int32_t nrow )
    : Entity( c )
    , m_dimension( dimension )
{
    init_board( m_dimension, ncol, nrow );
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
    for ( size_t col = 0u; col < m_tiles.size( ); ++col )
    {
        for ( size_t row = 0u; row < m_tiles[ col ].size( ); ++row )
        {
            std::cout << to_string( m_tiles[ row ][ col ].texture ) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------" << std::endl;
}

const Tile&
Board::tile( const TilePosition& pos ) const
{
    return m_tiles[ pos.col ][ pos.row ];
};

const Tile&
Board::tile( const Coordinates& event_coordinates ) const
{
    const auto& pos = position_of_tile( event_coordinates );

    return m_tiles[ pos.col ][ pos.row ];
}

Tile
Board::copy_tile( const Coordinates& event_coordinates )
{
    const auto& pos = position_of_tile( event_coordinates );

    return m_tiles[ pos.col ][ pos.row ];
}

TilePosition
Board::position_of_tile( const Coordinates& event_coordinates ) const
{
    return Utils::position_of_tile( event_coordinates, Coordinates( {this->x, this->y} ),
                                    tile_dimension( ) );
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
Board::generate_texture_type( int32_t col, int32_t row )
{
    std::set< King::Engine::Texture > black_list;
    if ( row > 0u )
    {
        black_list.insert( m_tiles[ col ][ row - 1 ].texture );
    }

    if ( row + 1u < m_tiles[ col ].size( ) )
    {
        black_list.insert( m_tiles[ col ][ row + 1 ].texture );
    }

    if ( col > 0u )
    {
        black_list.insert( m_tiles[ col - 1 ][ row ].texture );
    }

    if ( col + 1u < m_tiles.size( ) )
    {
        black_list.insert( m_tiles[ col + 1 ][ row ].texture );
    }

    std::set< King::Engine::Texture > supported
        = {King::Engine::TEXTURE_BLUE, King::Engine::TEXTURE_YELLOW, King::Engine::TEXTURE_RED,
           King::Engine::TEXTURE_GREEN, King::Engine::TEXTURE_PURPLE};

    std::vector< King::Engine::Texture > diff;
    std::set_difference( supported.begin( ), supported.end( ), black_list.begin( ),
                         black_list.end( ), std::inserter( diff, diff.begin( ) ) );

    return diff[ std::rand( ) % diff.size( ) ];
}

void
Board::init_board( const Dimension& dimension, int32_t ncol, int32_t nrow )
{
    m_tiles.resize( nrow );

    float base_row = dimension.height / nrow;
    float base_col = dimension.width / ncol;

    for ( int32_t col = 0u; col < ncol; ++col )
    {
        m_tiles.reserve( nrow );
        for ( int32_t row = 0u; row < nrow; ++row )
        {
            Coordinates c;
            c.x = this->x + base_col * col + ( base_col / 4 );
            c.y = this->y + base_row * row + ( base_row / 4 );
            m_tiles[ col ].push_back( Tile( {c} ) );
        }
    }

    for ( int32_t col = 0u; col < ncol; ++col )
    {
        for ( int32_t row = 0u; row < nrow; ++row )
        {
            Tile& tile = m_tiles[ col ][ row ];
            tile.texture = generate_texture_type( col, row );
        }
    }
}

Dimension
Board::tile_dimension( ) const
{
    if ( m_tiles.empty( ) )
        return Dimension( {0u, 0u} );

    return Dimension(
        {m_dimension.width / m_tiles[ 0 ].size( ), m_dimension.height / m_tiles.size( )} );
}
}