#include "GenerateGemsCommand.h"

#include "Gameplay.h"

#include <algorithm>
#include <memory>

namespace Game
{
bool
GenerateGemsCommand::is_valid( Gameplay& gameplay ) const
{
    return true;
};

bool
GenerateGemsCommand::is_finished( Gameplay& gameplay ) const
{
    Board& board = gameplay.board( );
    bool is_finished = false;
    for ( auto row = 0; row < board.size( ); ++row )
    {
        for ( auto col = 0; col < board[ row ].size( ); ++col )
        {
            if ( board[ row ][ col ].texture == King::Engine::TEXTURE_BROKEN )
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
        gameplay.print( );
        std::vector< King::Engine::Texture > supported_cell_types
            = {King::Engine::TEXTURE_BLUE, King::Engine::TEXTURE_YELLOW, King::Engine::TEXTURE_RED,
               King::Engine::TEXTURE_GREEN, King::Engine::TEXTURE_PURPLE};

        for ( auto col = 0; col < board.size( ); ++col )
        {
            CellPosition offset;
            bool found = false;

            std::stable_partition(
                board[ col ].begin( ), board[ col ].end( ),
                []( const Cell& cell ) { return cell.texture == King::Engine::TEXTURE_BROKEN; } );

            for ( auto row = 0; row < board.size( ); ++row )
            {
                if ( board[ row ][ col ].texture == King::Engine::TEXTURE_BROKEN )
                {
                    offset.col = col;
                    offset.row = row;
                    found = true;
                    break;
                }
            }
            if ( found )
            {
                int row = offset.row;
                while ( row > 0 && board[ row ][ col ].texture == King::Engine::TEXTURE_BROKEN )
                {
                    board[ row ][ col ].texture
                        = supported_cell_types[ std::rand( ) % supported_cell_types.size( ) ];
                }
            }
        }
        first_time = false;
        gameplay.print( );
    }

    /*for ( auto row = 0; row < board.size( ); ++row )
    {
        for ( auto col = 0; col < board[ row ].size( ); ++col )
        {
            if ( board[ row ][ col ].texture == King::Engine::TEXTURE_BROKEN )
            {
                MoveCommandSharedPtr command;
                if ( row > 0 && board[ row - 1 ][ col ].texture != King::Engine::TEXTURE_BROKEN )
                {
                    board[ row ][ col ].texture = board[ row - 1 ][ col ].texture;
                    board[ row - 1 ][ col ].texture = King::Engine::TEXTURE_BROKEN;
                    command = std::make_shared< MoveCommand >( CellPosition( {row - 1, col} ),
                                                               CellPosition( {row, col} ) );

                    m_falling_gems.push_back( command );
                }
                else
                {
                    board[ row ][ col ].texture
                        = supported_cell_types[ std::rand( ) % supported_cell_types.size( ) ];
                }
            }
        }
    }*/

    for ( auto& move_command : m_falling_gems )
    {
        move_command->apply( gameplay );
    }

    return true;
}

bool
GenerateGemsCommand::undo( Gameplay& gameplay )
{
    return true;
}
}