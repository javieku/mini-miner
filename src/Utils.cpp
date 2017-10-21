#include "Utils.h"

// Game
#include "Coordinates.h"
#include "Gem.h"

namespace Game
{
GemPosition
Utils::to_position_of_gem( const Coordinates& coordinate,
                           const Coordinates& board_offset,
                           const Dimension& dimension )
{
    int col = ( coordinate.x - board_offset.x ) / dimension.width;
    int row = ( coordinate.y - board_offset.y ) / dimension.height;

    return {row, col};
}
}