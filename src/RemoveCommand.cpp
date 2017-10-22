#include "RemoveCommand.h"

// Game
#include "Board.h"
#include "GameState.h"
#include "Utils.h"

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

bool
can_remove( const Column& column )
{
    auto first = Utils::adjacent_find_n( column.begin( ), column.end( ), COLLAPSE_THRESHOLD - 1,
                                         is_removable );

    auto rfirst = Utils::adjacent_find_n( column.rbegin( ), column.rend( ), COLLAPSE_THRESHOLD - 1,
                                          is_removable );

    return ( first != column.end( ) ) || rfirst != column.rend( );
}

bool
remove_tiles( Column& column )
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

int32_t
remove_tiles( Tiles& board )
{
    int32_t counter = 0u;
    for ( Column& column : board )
    {
        if ( remove_tiles( column ) )
            ++counter;
    }
    return counter;
}
}

RemoveCommand::RemoveCommand( )
    : m_done( false )
{
}

bool
RemoveCommand::is_valid( const GameState& state ) const
{
    const auto& board = state.board_tiles( );
    bool valid = false;

    // Strategy for rows
    // Transposition of the board
    Tiles transposed_tiles;
    Utils::transposition( board, transposed_tiles );

    // Handle rows as column
    for ( const Column& column : transposed_tiles )
    {
        valid = valid || can_remove( column );
    }

    // Strategy for colums
    for ( const Column& column : board )
    {
        valid = valid || can_remove( column );
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
    int32_t removed_tile_count = strategy_for_row( state.board( ) );

    removed_tile_count += strategy_for_colum( state.board( ) );

    m_done = ( removed_tile_count > 0 );

    state.score( ).increase( removed_tile_count );
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

int32_t
RemoveCommand::strategy_for_row( Board& board )
{
    Tiles& tiles = board.tiles( );
    // Since the board is represented as std::vector of std::vector
    // To apply easily standard algorithm adjacent first it is required
    // to transpose the board
    // 1 - Board tiles transposition
    // 2 - Apply column strategy to rows
    // 3 - Apply result to the original board

    std::vector< Column > transposed_tiles;
    Utils::transposition( tiles, transposed_tiles );

    int32_t removed_tile_count = remove_tiles( transposed_tiles );

    for ( size_t col = 0; col < tiles.size( ); ++col )
    {
        for ( size_t row = 0; row < tiles[ col ].size( ); ++row )
        {
            tiles[ col ][ row ] = transposed_tiles[ row ][ col ];
        }
    }

    return removed_tile_count;
}

int32_t
RemoveCommand::strategy_for_colum( Board& board )
{
    // Simply apply the adjacent_n algorithm to every column

    return remove_tiles( board.tiles( ) );
}
}