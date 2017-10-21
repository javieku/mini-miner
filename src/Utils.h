#pragma once
#include "Coordinates.h"
#include "Gem.h"
namespace Game
{
class Coordinates;
class GemPosition;

class Utils
{
public:
    static Coordinates
    to_cell_coordinates( const Coordinates& coordinate_to_adjust,
                         const Coordinates& board_offset,
                         const Dimension& tile )
    {
        GemPosition pos = Utils::to_position_of_gem( coordinate_to_adjust, board_offset, tile );

        Coordinates c;
        c.x = board_offset.x + tile.height * pos.col + ( tile.height / 4 );
        c.y = board_offset.y + tile.width * pos.row + ( tile.width / 4 );

        return c;
    }

    static GemPosition to_position_of_gem( const Coordinates& coordinate,
                                           const Coordinates& board_offset,
                                           const Dimension& dimension );
};
}