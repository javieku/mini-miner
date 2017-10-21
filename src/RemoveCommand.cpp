#include "RemoveCommand.h"

#include "GameState.h"
#include "Utils.h"

#include <iostream>

namespace Game
{
namespace
{
// At least 3 items have to be the same in a row/colum
const int32_t COLLAPSE_THRESHOLD = 3;

auto is_removable = []( const Tile& one_tile, const Tile& other_tile ) {
    if ( one_tile.texture == King::Engine::TEXTURE_BROKEN
         || other_tile.texture == King::Engine::TEXTURE_BROKEN )
    {
        return false;
    }

    return one_tile.texture == other_tile.texture;
};
}

RemoveCommand::RemoveCommand( )
    : m_done( false )
{
}

bool
can_remove( const Colum& column )
{
    auto first = Utils::adjacent_find_n( column.begin( ), column.end( ), COLLAPSE_THRESHOLD - 1,
                                         is_removable );

    auto rfirst = Utils::adjacent_find_n( column.rbegin( ), column.rend( ), COLLAPSE_THRESHOLD - 1,
                                          is_removable );

    return ( first != column.end( ) ) || rfirst != column.rend( );
}

bool
remove_tiles( Colum& column )
{
    auto first = Utils::adjacent_find_n( column.begin( ), column.end( ), COLLAPSE_THRESHOLD - 1,
                                         is_removable );

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

    auto rfirst = Utils::adjacent_find_n( column.rbegin( ), column.rend( ), COLLAPSE_THRESHOLD - 1,
                                          is_removable );

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

    return first != column.end( ) || rfirst != column.rend( );
}

bool
RemoveCommand::is_valid( const GameState& state ) const
{
    const auto& board = state.board_tiles( );
    bool valid = false;

    state.print( );

    // Strategy for row
    // Transposition of the board
    Tiles transposed_tiles;
    Utils::transposition( board, transposed_tiles );

    // Handle rows as column
    for ( size_t row = 0; row < transposed_tiles.size( ); ++row )
    {
        valid = valid || can_remove( transposed_tiles[ row ] );
    }

    // Strategy for colums
    for ( size_t col = 0; col < board.size( ); ++col )
    {
        valid = valid || can_remove( board[ col ] );
    }
    return valid;
};

void
RemoveCommand::apply( GameState& state )
{
    if ( !is_valid( state ) )
    {
        m_done = true;
        return;
    }

    auto& board = state.board_tiles( );
    std::cout << "RemoveCommand" << std::endl;
    state.print( );

    bool has_removed_tile = false;
    // Strategy for rows
    // 1 - Board tiles transposition
    // 2 - Apply colum strategy to rows
    // 3 - Apply result to the original board
    std::cout << "Strategy for rows" << std::endl;

    std::vector< Colum > transposed_tiles;
    Utils::transposition( board, transposed_tiles );

    for ( size_t row = 0; row < transposed_tiles.size( ); ++row )
    {
        bool success = remove_tiles( transposed_tiles[ row ] );
        if ( success )
            state.increase_score( );
        has_removed_tile = has_removed_tile || success;
    }

    for ( size_t col = 0; col < board.size( ); ++col )
    {
        for ( size_t row = 0; row < board[ col ].size( ); ++row )
        {
            board[ col ][ row ] = transposed_tiles[ row ][ col ];
        }
    }
    state.print( );

    std::cout << "Strategy for columns" << std::endl;

    // Strategy for colums
    for ( size_t col = 0; col < board.size( ); ++col )
    {
        bool success = remove_tiles( board[ col ] );
        if ( success )
            state.increase_score( );
        has_removed_tile = has_removed_tile || success;
    }
    state.print( );

    m_done = has_removed_tile;

    std::cout << "Done? " << m_done << " has_removed_tile? " << has_removed_tile << std::endl;
}

bool
RemoveCommand::is_finished( const GameState& state ) const
{
    return m_done;
};

void
RemoveCommand::undo( GameState& state )
{
    // TODO: Implement when needed
}
}