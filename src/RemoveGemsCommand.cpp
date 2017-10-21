#include "RemoveGemsCommand.h"

#include "GameState.h"

#include <iostream>

namespace Game
{
namespace
{
// At least 3 items have to be the same in a row/colum
const int32_t COLLAPSE_THRESHOLD = 3;
}

RemoveGemsCommand::RemoveGemsCommand( )
    : m_done( false )
{
}

// Generalization of adjacent_find to check n consecutive elements
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
    ForwardIt first_range;
    for ( ; next != last; ++next, ++first )
    {
        if ( p( *first, *next ) )
        {
            if ( counter == 0 )
            {
                first_range = first;
            }
            ++counter;
        }
        else
        {
            counter = 0;
        }
        if ( counter >= n )
        {
            return first_range;
        }
    }
    return last;
}

bool
can_remove( const Colum& column )
{
    auto first = adjacent_find_n(
        column.begin( ), column.end( ), COLLAPSE_THRESHOLD - 1,
        []( const Gem& gem1, const Gem& gem2 ) { return gem1.texture == gem2.texture; } );

    auto rfirst = adjacent_find_n(
        column.rbegin( ), column.rend( ), COLLAPSE_THRESHOLD - 1,
        []( const Gem& gem1, const Gem& gem2 ) { return gem1.texture == gem2.texture; } );

    return ( first != column.end( ) ) || rfirst != column.rend( );
}

bool
remove_gems( Colum& column )
{
    auto first = adjacent_find_n( column.begin( ), column.end( ), COLLAPSE_THRESHOLD - 1,
                                  []( const Gem& gem1, const Gem& gem2 ) {
                                      if ( gem1.texture == King::Engine::TEXTURE_BROKEN
                                           || gem2.texture == King::Engine::TEXTURE_BROKEN )
                                      {
                                          return false;
                                      }

                                      return gem1.texture == gem2.texture;
                                  } );

    if ( first != column.end( ) )
    {
        auto& it = first;
        const auto texture = first->texture;
        while ( it->texture == texture && it != column.end( ) )
        {
            it->texture = King::Engine::TEXTURE_BROKEN;
            ++it;
        }
    }

    auto rfirst = adjacent_find_n(
        column.rbegin( ), column.rend( ), COLLAPSE_THRESHOLD - 1,
        []( const Gem& gem1, const Gem& gem2 ) { return gem1.texture == gem2.texture; } );

    if ( rfirst != column.rend( ) )
    {
        auto& it = rfirst;
        const auto texture = rfirst->texture;
        while ( it->texture == texture && it != column.rend( ) )
        {
            it->texture = King::Engine::TEXTURE_BROKEN;
            ++it;
        }
    }

    return first != column.end( );
}

std::string
to_strings( const King::Engine::Texture& texture )
{
    switch ( texture )

    {
    case King::Engine::TEXTURE_BLUE:
        return "B";
    case King::Engine::TEXTURE_GREEN:
        return "G";
    case King::Engine::TEXTURE_PURPLE:
        return "P";
    case King::Engine::TEXTURE_RED:
        return "R";
    case King::Engine::TEXTURE_YELLOW:
        return "Y";
    case King::Engine::TEXTURE_BROKEN:
        return "X";
    case King::Engine::TEXTURE_MAX:
        return "?";
    }
}

bool
RemoveGemsCommand::is_valid( const GameState& state ) const
{
    const auto& board = state.board_tiles( );
    bool valid = false;

    state.print( );

    // Strategy for row
    // Transposition of the board
    std::vector< Colum > rows;
    for ( size_t col = 0; col < board.size( ); ++col )
    {
        Colum items_row;
        for ( size_t row = 0; row < board[ col ].size( ); ++row )
        {
            items_row.push_back( board[ row ][ col ] );
        }
        rows.push_back( items_row );
    }

    // Handle rows as column
    for ( size_t row = 0; row < rows.size( ); ++row )
    {
        valid = valid || can_remove( rows[ row ] );
    }

    // Strategy for colums
    for ( size_t col = 0; col < board.size( ); ++col )
    {
        valid = valid || can_remove( board[ col ] );
    }
    return valid;
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
    // Strategy for rows
    // transposition the board so that we can handle rows as columns

    std::cout << "Strategy for rows" << std::endl;
    std::vector< Colum > rows;
    for ( size_t col = 0; col < board.size( ); ++col )
    {
        Colum items_row;
        for ( size_t row = 0; row < board[ col ].size( ); ++row )
        {
            items_row.push_back( board[ row ][ col ] );
        }
        rows.push_back( items_row );
    }

    std::cout << "Transposition of board" << std ::endl;

    for ( size_t col = 0; col < rows.size( ); ++col )
    {
        for ( size_t row = 0; row < rows[ col ].size( ); ++row )
        {
            std::cout << to_strings( rows[ row ][ col ].texture ) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------" << std::endl;

    // Apply colum strategy to rows
    for ( size_t row = 0; row < rows.size( ); ++row )
    {
        bool success = remove_gems( rows[ row ] );
        if ( success )
            state.increase_score( );
        has_removed_gem = has_removed_gem || success;
    }

    // Apply result to the original board
    for ( size_t col = 0; col < board.size( ); ++col )
    {
        for ( size_t row = 0; row < board[ col ].size( ); ++row )
        {
            board[ col ][ row ] = rows[ row ][ col ];
        }
    }
    state.print( );

    std::cout << "Strategy for columns" << std::endl;

    // Strategy for colums
    for ( size_t col = 0; col < board.size( ); ++col )
    {
        bool success = remove_gems( board[ col ] );
        if ( success )
            state.increase_score( );
        has_removed_gem = has_removed_gem || success;
    }
    state.print( );

    m_done = has_removed_gem;

    std::cout << "Done? " << m_done << std::endl;
}

bool
RemoveGemsCommand::is_finished( const GameState& state ) const
{
    return m_done;
};

void
RemoveGemsCommand::undo( GameState& state )
{
    // TODO: Implement when needed
}
}