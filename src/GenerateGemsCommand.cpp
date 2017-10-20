#include "GenerateGemsCommand.h"

// Game
#include "GameState.h"

// Standard
#include <algorithm>
#include <iostream>
#include <memory>

namespace Game
{
bool
GenerateGemsCommand::is_valid( const GameState& state ) const
{
    // Always executable
    return true;
};

bool
GenerateGemsCommand::is_finished( const GameState& state ) const
{
    const auto& board = state.board_tiles( );
    bool is_finished = true;
    for ( size_t col = 0; col < board.size( ); ++col )
    {
        for ( size_t row = 0; row < board[ col ].size( ); ++row )
        {
            if ( board[ col ][ row ].texture == King::Engine::TEXTURE_BROKEN )
            {
                return false;
            }
        }
    }

    for ( auto& move_command : m_falling_gems )
    {
        is_finished = is_finished && move_command->is_finished( state );
    }

    return is_finished;
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
            // Find last broken cell in colum
            if ( has_broken_cell( board[ col ] ) )
            {
                // If found create move commands
                Colum column( board[ col ].size( ) );
                std::copy( board[ col ].begin( ), board[ col ].end( ), column.begin( ) );

                auto bound = std::stable_partition(
                    column.begin( ), column.end( ), []( const Cell& cell ) {
                        return cell.texture == King::Engine::TEXTURE_BROKEN;
                    } );

                state.print( );

                for ( size_t row = 0; row < column.size( ); ++row )
                {
                    Cell cell = ( column[ row ].texture == King::Engine::TEXTURE_BROKEN )
                                    ? Cell::create_random( 40.0f * row, column[ row ].x )
                                    : column[ row ];

                    const Cell& cell_to_be_replaced = board[ col ][ row ];
                    m_falling_gems.push_back( std::make_shared< MoveCommand >(
                        cell, Coordinates( {cell_to_be_replaced.x, cell_to_be_replaced.y} ) ) );
                }
            }
        }
        first_time = false;
        state.print( );
    }

    for ( auto& move_command : m_falling_gems )
    {
        move_command->apply( state );
    }
}

void
GenerateGemsCommand::undo( GameState& state )
{
    // TODO
}

bool
GenerateGemsCommand::has_broken_cell( const Colum& colum )
{
    auto it = std::find_if( colum.rbegin( ), colum.rend( ), []( const Cell& cell ) {
        return cell.texture == King::Engine::TEXTURE_BROKEN;
    } );

    return it != colum.rend( );
}
}