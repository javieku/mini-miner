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
RemoveGemsCommand::is_valid( const Gameplay& gameplay ) const
{
    const Board& board = gameplay.board( );
    std::cout << "RemoveCommand" << std::endl;
    gameplay.print( );
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
    gameplay.print( );
    return removable;
};

bool
RemoveGemsCommand::apply( Gameplay& gameplay )
{
    Board& board = gameplay.board( );

    for ( size_t col = 0; col < board.size( ); ++col )
    {
        for ( size_t row = 0; row < board[ col ].size( ); ++row )
        {
            bool removable = false;

            if ( row > 1 )
            {
                removable = board[ col ][ row - 1 ].texture == board[ col ][ row - 2 ].texture
                            && board[ col ][ row - 1 ].texture == board[ col ][ row ].texture;
                if ( removable )
                {
                    board[ col ][ row - 1 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row - 2 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    m_done = true;
                }
            }

            if ( row + 2 < NROW )
            {
                removable = board[ col ][ row + 1 ].texture == board[ col ][ row + 2 ].texture
                            && board[ col ][ row + 1 ].texture == board[ col ][ row ].texture;
                if ( removable )
                {
                    board[ col ][ row + 1 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row + 2 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    m_done = true;
                }
            }

            if ( col > 1 )
            {
                removable = board[ col - 1 ][ row ].texture == board[ col - 2 ][ row ].texture
                            && board[ col - 1 ][ row ].texture == board[ col ][ row ].texture;
                if ( removable )
                {
                    board[ col - 1 ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col - 2 ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    m_done = true;
                }
            }

            if ( col + 2 < NCOL )
            {
                removable = board[ col + 1 ][ row ].texture == board[ col + 2 ][ row ].texture
                            && board[ col + 1 ][ row ].texture == board[ col ][ row ].texture;
                if ( removable )
                {
                    board[ col + 1 ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col + 2 ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ col ][ row ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    m_done = true;
                }
            }
        }
    };

    return true;
}

bool
RemoveGemsCommand::is_finished( const Gameplay& gameplay ) const
{
    return m_done;
};

bool
RemoveGemsCommand::undo( Gameplay& gameplay )
{
    return false;
}
}