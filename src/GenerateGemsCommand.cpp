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
    const Board& board = gameplay.board( );
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
    Board& board = gameplay.board( );

    if ( first_time )
    {
        std::cout << "GenerateGemsCommand" << std::endl;
        gameplay.print( );

        for ( auto col = 0; col < board.size( ); ++col )
        {
            std::stable_partition(
                board[ col ].begin( ), board[ col ].end( ),
                []( const Cell& cell ) { return cell.texture == King::Engine::TEXTURE_BROKEN; } );

            gameplay.print( );

            for ( auto row = 0; row < board[ col ].size( ); ++row )
            {
                if ( board[ col ][ row ].texture == King::Engine::TEXTURE_BROKEN )
                {
                    std::vector< King::Engine::Texture > supported_cell_types
                        = {King::Engine::TEXTURE_BLUE, King::Engine::TEXTURE_YELLOW,
                           King::Engine::TEXTURE_RED, King::Engine::TEXTURE_GREEN,
                           King::Engine::TEXTURE_PURPLE};

                    Cell new_cell;
                    new_cell.texture
                        = supported_cell_types[ std::rand( ) % supported_cell_types.size( ) ];
                    new_cell.y = 40 * row;
                    new_cell.x = board[ col ][ row ].x;
                    auto command
                        = std::make_shared< MoveCommand >( new_cell, CellPosition( {row, col} ) );

                    m_falling_gems.push_back( command );
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
}