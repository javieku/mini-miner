#include "RemoveGemsCommand.h"

#include "GameState.h"

#include <iostream>

namespace Game
{
RemoveGemsCommand::RemoveGemsCommand( )
    : m_done( false )
{
}

bool
RemoveGemsCommand::is_valid( const GameState& state ) const
{
    const auto& board = state.board_tiles( );
    bool can_remove = false;
    for ( size_t col = 0; col < board.size( ); ++col )
    {
        for ( size_t row = 0; row < board[ col ].size( ); ++row )
        {
            if ( row > 1 )
            {
                can_remove |= board[ col ][ row - 1 ].texture == board[ col ][ row - 2 ].texture
                              && board[ col ][ row - 1 ].texture == board[ col ][ row ].texture;
            }

            if ( row + 2 < NROW )
            {
                can_remove |= board[ col ][ row + 1 ].texture == board[ col ][ row + 2 ].texture
                              && board[ col ][ row + 1 ].texture == board[ col ][ row ].texture;
            }

            if ( col > 1 )
            {
                can_remove |= board[ col - 1 ][ row ].texture == board[ col - 2 ][ row ].texture
                              && board[ col - 1 ][ row ].texture == board[ col ][ row ].texture;
            }

            if ( col + 2 < NCOL )
            {
                can_remove |= board[ col + 1 ][ row ].texture == board[ col + 2 ][ row ].texture
                              && board[ col + 1 ][ row ].texture == board[ col ][ row ].texture;
            }
        }
    }
    return can_remove;
};

void
RemoveGemsCommand::apply( GameState& state )
{
    if ( !is_valid( state ) )
    {
        m_done = true;
        return;
    }

    auto& board = state.board_tiles( );
    std::cout << "RemoveCommand" << std::endl;
    state.print( );

    bool has_removed_gem = false;
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
                    state.increase_score( );
                    has_removed_gem = true;
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
                    state.increase_score( );
                    has_removed_gem = true;
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
                    state.increase_score( );
                    has_removed_gem = true;
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
                    state.increase_score( );
                    has_removed_gem = true;
                }
            }
        }
    }
    m_done = has_removed_gem;
    state.print( );
}

bool
RemoveGemsCommand::is_finished( const GameState& state ) const
{
    return m_done;
};

void
RemoveGemsCommand::undo( GameState& state )
{
}

template < class ForwardIt, class Size, class BinaryPredicate >
ForwardIt
adjacent_find_n( ForwardIt first, ForwardIt last, Size n, BinaryPredicate p )
{
    if ( first == last )
    {
        return last;
    }
    ForwardIt next = first;
    ++next;

    Size counter = 0;
    for ( ; next != last; ++next, ++first )
    {
        if ( p( *first, *next ) )
        {
            ++counter;
        }
        if ( counter >= n )
        {
            return first;
        }
    }
    return last;
}
}