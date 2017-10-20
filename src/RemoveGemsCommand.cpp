#include "RemoveGemsCommand.h"

#include "Gameplay.h"

#include <iostream>

namespace Game
{
RemoveGemsCommand::RemoveGemsCommand( )
    : m_done( false )
{
}

bool
RemoveGemsCommand::is_valid( const GameState& gameplay ) const
{
    const auto& board = gameplay.board_tiles( );
    bool removable = false;
    for ( size_t col = 0; col < board.size( ); ++col )
    {
        for ( size_t row = 0; row < board[ col ].size( ); ++row )
        {
            if ( row > 1 )
            {
                removable |= board[ col ][ row - 1 ].texture == board[ col ][ row - 2 ].texture
                             && board[ col ][ row - 1 ].texture == board[ col ][ row ].texture;
            }

            if ( row + 2 < NROW )
            {
                removable |= board[ col ][ row + 1 ].texture == board[ col ][ row + 2 ].texture
                             && board[ col ][ row + 1 ].texture == board[ col ][ row ].texture;
            }

            if ( col > 1 )
            {
                removable |= board[ col - 1 ][ row ].texture == board[ col - 2 ][ row ].texture
                             && board[ col - 1 ][ row ].texture == board[ col ][ row ].texture;
            }

            if ( col + 2 < NCOL )
            {
                removable |= board[ col + 1 ][ row ].texture == board[ col + 2 ][ row ].texture
                             && board[ col + 1 ][ row ].texture == board[ col ][ row ].texture;
            }
        }
    }
    return removable;
};

bool
RemoveGemsCommand::apply( GameState& gameplay )
{
    if ( !is_valid( gameplay ) )
    {
        m_done = true;
        return false;
    }

    auto& board = gameplay.board_tiles( );
    std::cout << "RemoveCommand" << std::endl;
    gameplay.print( );

    bool has_removed_cell = false;
    for ( size_t col = 0; col < board.size( ); ++col )
    {
        for ( size_t row = 0; row < board[ col ].size( ); ++row )
        {
            if ( row > 1 )
            {
                bool down = board[ col ][ row - 1 ].texture == board[ col ][ row - 2 ].texture
                            && board[ col ][ row - 1 ].texture == board[ col ][ row ].texture;
                if ( down )
                {
                    board[ col ][ row - 1 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row - 2 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    has_removed_cell = true;
                }
            }

            if ( row + 2 < NROW )
            {
                bool up = board[ col ][ row + 1 ].texture == board[ col ][ row + 2 ].texture
                          && board[ col ][ row + 1 ].texture == board[ col ][ row ].texture;
                if ( up )
                {
                    board[ col ][ row + 1 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row + 2 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    has_removed_cell = true;
                }
            }

            if ( col > 1 )
            {
                bool left = board[ col - 1 ][ row ].texture == board[ col - 2 ][ row ].texture
                            && board[ col - 1 ][ row ].texture == board[ col ][ row ].texture;
                if ( left )
                {
                    board[ col - 1 ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col - 2 ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    has_removed_cell = true;
                }
            }

            if ( col + 2 < NCOL )
            {
                bool right = board[ col + 1 ][ row ].texture == board[ col + 2 ][ row ].texture
                             && board[ col + 1 ][ row ].texture == board[ col ][ row ].texture;
                if ( right )
                {
                    board[ col + 1 ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col + 2 ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    has_removed_cell = true;
                }
            }
        }
    }
    m_done = has_removed_cell;
    gameplay.print( );
    return true;
}

bool
RemoveGemsCommand::is_finished( const GameState& gameplay ) const
{
    return m_done;
};

bool
RemoveGemsCommand::undo( GameState& gameplay )
{
    return false;
}
}