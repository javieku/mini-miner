#include "BreakGemsCommand.h"

#include "Gameplay.h"

namespace Game
{
BreakGemsCommand::BreakGemsCommand( )
    : m_done( false )
{
}

bool
BreakGemsCommand::is_valid( Gameplay& gameplay ) const
{
    Board& board = gameplay.board( );

    bool removable = false;
    for ( auto row = 0; row < board.size( ); ++row )
    {
        for ( auto col = 0; col < board[ row ].size( ); ++col )
        {
            if ( row > 1 )
            {
                removable |= board[ row - 1 ][ col ].texture == board[ row - 2 ][ col ].texture
                             && board[ row - 1 ][ col ].texture == board[ row ][ col ].texture;
            }

            if ( row + 2 < NROW )
            {
                removable |= board[ row + 1 ][ col ].texture == board[ row + 2 ][ col ].texture
                             && board[ row + 1 ][ col ].texture == board[ row ][ col ].texture;
            }

            if ( col > 0 )
            {
                removable |= board[ row ][ col - 1 ].texture == board[ row ][ col - 2 ].texture
                             && board[ row ][ col - 1 ].texture == board[ row ][ col ].texture;
            }

            if ( col + 2 < NCOL )
            {
                removable |= board[ row ][ col + 1 ].texture == board[ row ][ col + 2 ].texture
                             && board[ row ][ col + 1 ].texture == board[ row ][ col ].texture;
            }
        }
    };
    return removable;
};

bool
BreakGemsCommand::apply( Gameplay& gameplay )
{
    Board& board = gameplay.board( );

    for ( auto row = 0; row < board.size( ); ++row )
    {
        for ( auto col = 0; col < board[ row ].size( ); ++col )
        {
            bool removable = false;

            if ( row > 1 )
            {
                removable = board[ row - 1 ][ col ].texture == board[ row - 2 ][ col ].texture
                            && board[ row - 1 ][ col ].texture == board[ row ][ col ].texture;
                if ( removable )
                {
                    board[ row - 1 ][ col ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ row - 2 ][ col ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ row ][ col ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    m_done = true;
                }
            }

            if ( row + 2 < NROW )
            {
                removable = board[ row + 1 ][ col ].texture == board[ row + 2 ][ col ].texture
                            && board[ row + 1 ][ col ].texture == board[ row ][ col ].texture;
                if ( removable )
                {
                    board[ row + 1 ][ col ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ row + 2 ][ col ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ row ][ col ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    m_done = true;
                }
            }

            if ( col > 0 )
            {
                removable = board[ row ][ col - 1 ].texture == board[ row ][ col - 2 ].texture
                            && board[ row ][ col - 1 ].texture == board[ row ][ col ].texture;
                if ( removable )
                {
                    board[ row ][ col - 1 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ row ][ col - 2 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ row ][ col ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    m_done = true;
                }
            }

            if ( col + 2 < NCOL )
            {
                removable = board[ row ][ col + 1 ].texture == board[ row ][ col + 2 ].texture
                            && board[ row ][ col + 1 ].texture == board[ row ][ col ].texture;
                if ( removable )
                {
                    board[ row ][ col + 1 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ row ][ col + 2 ].texture = King::Engine::TEXTURE_BROKEN;
                    board[ row ][ col ].texture = King::Engine::TEXTURE_BROKEN;
                    gameplay.increase_score( );
                    m_done = true;
                }
            }
        }
    };

    return true;
}

bool
BreakGemsCommand::is_finished( Gameplay& gameplay ) const
{
    return m_done;
};

bool
BreakGemsCommand::undo( Gameplay& gameplay )
{
    return false;
}
}