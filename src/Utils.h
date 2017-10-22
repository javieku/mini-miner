#pragma once

// Game
#include "Board.h"
#include "Coordinates.h"
#include "Tile.h"

namespace Game
{
class Coordinates;
class TilePosition;

class Utils
{
public:
    static Coordinates to_tile_coordinates( const Coordinates& original_coordinate,
                                            const Coordinates& board_offset,
                                            const Dimension& tile );

    static TilePosition position_of_tile( const Coordinates& coordinate,
                                          const Coordinates& board_offset,
                                          const Dimension& dimension );

    static void transposition( const Tiles& tiles, Tiles& transposed_tiles );

    // Implementation taken from the standard. This is generalization of std::adjacent_find
    // to check n consecutive elements instead of 2
    template < class ForwardIt, class Size, class BinaryPredicate >
    static ForwardIt
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
};
}