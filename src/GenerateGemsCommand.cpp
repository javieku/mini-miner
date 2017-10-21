#include "GenerateGemsCommand.h"

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
bool
none_of_tiles_is_broken( const Tiles& board )
{
    auto filter = []( const Gem& gem ) { return gem.texture == King::Engine::TEXTURE_BROKEN; };

    for ( const Colum& colum : board )
    {
        if ( std::any_of( colum.begin( ), colum.end( ), filter ) )
        {
            return false;
        }
    }

    return true;
}
bool
any_of_tiles_is_broken( const Colum& column )
{
    auto filter = []( const Gem& gem ) { return gem.texture == King::Engine::TEXTURE_BROKEN; };

	return std::any_of(column.begin(), column.end(), filter);
}
}  // anonymous namespace

bool
GenerateGemsCommand::is_valid( const GameState& state ) const
{
    // Always applicable
    return true;
};

bool
GenerateGemsCommand::is_finished( const GameState& state ) const
{
    return none_of_tiles_is_broken( state.board_tiles( ) )
           && std::all_of(
                  m_tile_falling.cbegin( ), m_tile_falling.cend( ),
                  [&state]( const MoveCommandSharedPtr& c ) { return c->is_finished( state ); } );
};

void
GenerateGemsCommand::apply( GameState& state )
{
    auto& board = state.board_tiles( );

    if ( first_time )
    {
        std::cout << "GenerateGemsCommand" << std::endl;
        state.print( );

        for ( size_t col = 0; col < board.size( ); ++col )
        {
            if ( any_of_tiles_is_broken( board[ col ] ) )
            {
                // If found create move commands
                Colum column( board[ col ].size( ) );
                std::copy( board[ col ].begin( ), board[ col ].end( ), column.begin( ) );

                auto bound = std::stable_partition(
                    column.begin( ), column.end( ),
                    []( const Gem& gem ) { return gem.texture == King::Engine::TEXTURE_BROKEN; } );

                state.print( );

                for ( size_t row = 0; row < column.size( ); ++row )
                {
                    Gem gem = ( column[ row ].texture == King::Engine::TEXTURE_BROKEN )
                                  ? Gem::create_random( 40.0f * row, column[ row ].x )
                                  : column[ row ];

                    const Gem& gem_to_be_replaced = board[ col ][ row ];
                    m_tile_falling.push_back( std::make_shared< MoveCommand >(
                        gem, Coordinates( {gem_to_be_replaced.x, gem_to_be_replaced.y} ) ) );
                }
            }
        }
        first_time = false;
        state.print( );
    }

    for ( MoveCommandSharedPtr& c : m_tile_falling )
    {
        c->apply( state );
    }
}

void
GenerateGemsCommand::undo( GameState& state )
{
    // TODO
}
}