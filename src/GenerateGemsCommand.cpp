#include "GenerateGemsCommand.h"

#include "Gameplay.h"

#include <algorithm>
#include <iostream>
#include <memory>

namespace Game
{
bool
GenerateGemsCommand::is_valid( const Gameplay& gameplay ) const
{
    return true;
};

bool
GenerateGemsCommand::is_finished( const Gameplay& gameplay ) const
{
    const auto& board = gameplay.board_tiles( );
    bool is_finished = true;
    for ( auto col = 0; col < board.size( ); ++col )
    {
        for ( auto row = 0; row < board[ col ].size( ); ++row )
        {
            if ( board[ col ][ row ].texture == King::Engine::TEXTURE_BROKEN )
            {
                return false;
            }
        }
    }

    for ( auto& move_command : m_falling_gems )
    {
        is_finished = is_finished && move_command->is_finished( gameplay );
    }

    return is_finished;
};

bool
GenerateGemsCommand::apply( Gameplay& gameplay )
{
    auto& board = gameplay.board_tiles( );

    if ( first_time )
    {
        std::cout << "GenerateGemsCommand" << std::endl;
        gameplay.print( );

        for ( auto col = 0; col < board.size( ); ++col )
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

                gameplay.print( );

                for ( auto row = 0; row < column.size( ); ++row )
                {
                    Cell cell = ( column[ row ].texture == King::Engine::TEXTURE_BROKEN )
                                    ? Cell::create_random( 40 * row, column[ row ].x )
                                    : column[ row ];

                    const Cell& cell_to_be_replaced = board[ col ][ row ];
                    m_falling_gems.push_back( std::make_shared< MoveCommand >(
                        cell, Coordinates( {cell_to_be_replaced.x, cell_to_be_replaced.y} ) ) );
                }
            }
        }
        first_time = false;
        gameplay.print( );
    }

    for ( auto& move_command : m_falling_gems )
    {
        move_command->apply( gameplay );
    }

    return true;
}

bool
GenerateGemsCommand::undo( Gameplay& gameplay )
{
    // TODO
    return true;
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