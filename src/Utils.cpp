#include "Utils.h"

// Game
#include "Board.h"
#include "Coordinates.h"
#include "Tile.h"

namespace Game
{
Coordinates
Utils::to_tile_coordinates( const Coordinates& coordinate_to_adjust,
                            const Coordinates& board_offset,
                            const Dimension& tile )
{
    TilePosition pos = Utils::position_of_tile( coordinate_to_adjust, board_offset, tile );

    Coordinates c;
    c.x = board_offset.x + tile.height * pos.col + ( tile.height / 4u );
    c.y = board_offset.y + tile.width * pos.row + ( tile.width / 4u );

    return c;
}

TilePosition
Utils::position_of_tile( const Coordinates& coordinate,
                         const Coordinates& board_offset,
                         const Dimension& tile_dim )
{
    int32_t col = ( coordinate.x - board_offset.x ) / tile_dim.width;
    int32_t row = ( coordinate.y - board_offset.y ) / tile_dim.height;

    return {row, col};
}

void
Utils::transposition( const Tiles& tiles, Tiles& transposed_tiles )
{
    for ( size_t col = 0u; col < tiles.size( ); ++col )
    {
        Column items_row;
        for ( size_t row = 0; row < tiles[ col ].size( ); ++row )
        {
            items_row.push_back( tiles[ row ][ col ] );
        }
        transposed_tiles.push_back( items_row );
    }
}
}