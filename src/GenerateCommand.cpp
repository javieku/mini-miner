#include "GenerateCommand.h"

// Game
#include "GameState.h"

// Standard
#include <algorithm>
#include <iostream>
#include <memory>

namespace Game
{
namespace
{
const auto tile_is_broken
    = []( const Tile& tile ) { return tile.texture == King::Engine::TEXTURE_BROKEN; };

bool
any_of_tiles_is_broken( const Colum& column )
{
    return std::any_of( column.begin( ), column.end( ), tile_is_broken );
}
bool
none_of_tiles_is_broken( const Tiles& board )
{
    for ( const Colum& column : board )
    {
        if ( any_of_tiles_is_broken( column ) )
        {
            return false;
        }
    }

    return true;
}

void
stable_partition( Colum& column )
{
    std::stable_partition( column.begin( ), column.end( ), tile_is_broken );
}

std::vector< MoveCommandSharedPtr >
create_falling_tiles( const Colum& original_column, const Colum& copied_column )
{
    std::vector< MoveCommandSharedPtr > result;

    for ( size_t row = 0u; row < copied_column.size( ); ++row )
    {
        const auto& tile = copied_column[ row ];

        Tile falling_tile
            = ( tile_is_broken( tile ) ) ? Tile::create_random( 40.0f * row, tile.x ) : tile;

        Coordinates to{original_column[ row ].x, original_column[ row ].y};

        result.push_back( std::make_shared< MoveCommand >( falling_tile, to ) );
    }

    return result;
}

}  // anonymous namespace

bool
CreateAndMoveCommand::is_valid( const GameState& state ) const
{
    // Always applicable
    return true;
};

bool
CreateAndMoveCommand::is_finished( const GameState& state ) const
{
    return none_of_tiles_is_broken( state.board_tiles( ) )
           && std::all_of(
                  m_falling_tiles.cbegin( ), m_falling_tiles.cend( ),
                  [&state]( const MoveCommandSharedPtr& c ) { return c->is_finished( state ); } );
};

void
CreateAndMoveCommand::apply( GameState& state )
{
    if ( m_falling_tiles.empty( ) )
    {
        std::cout << "CreateAndMoveCommand" << std::endl;
        state.print( );
        auto& board = state.board_tiles( );
        for ( const auto& column : board )
        {
            if ( any_of_tiles_is_broken( column ) )
            {
                Colum column_copy = column;

                stable_partition( column_copy );

                auto& result = create_falling_tiles( column, column_copy );
                m_falling_tiles.insert( m_falling_tiles.end( ), result.begin( ), result.end( ) );
            }
        }
        state.print( );
    }

    for ( MoveCommandSharedPtr& c : m_falling_tiles )
    {
        c->apply( state );
    }
}

void
CreateAndMoveCommand::undo( GameState& state )
{
    // TODO: implement if needed
}
}