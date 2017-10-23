#pragma once

// Game
#include "CommandInterface.h"

namespace Game
{
class Board;
class GameState;

/**
 * Marks as broken 3 or more consecutive tiles with the same color.
 *
 * It is finished when the algorithm is applied once.
 *
 * It is not valid when no tile is removed. This command is convenient to check
 * if a SwapCommand has been successful or not.
 *
 * ----Implementation comments----
 * It applies a two steps strategy:
 *
 * 1 - For columns, it applies a std::adjacent_first checking
 *     both dimensions. From the beginning to the end and the other way around. 
 *     This is taking advantage that the board has size 8. If it were bigger 
 *     A different approach had to be implemented.
 *	   
 * 2 - For rows:
 *		- Transposition of the board.  		
 *        1 2 3       1 4 7
 *        4 5 6  ---> 2 5 8
 *        7 8 9       3 6 9
 *      - Then the same strategy as for colums.
 *      - Finally the changes are applied to the board
 *      
 *   This distinction has been implemented despite generating an extra copy of the board because 
 *   std::adjacent_first helps with readability. It is also possible to handcraft loops and make the step 
 *   2 "in place".
 *
 **/
class RemoveCommand : public CommandInterface
{
public:
    RemoveCommand( );
    ~RemoveCommand( ) = default;

    bool is_valid( const GameState& state ) const override;
    bool is_finished( const GameState& state ) const override;
    void apply( GameState& state ) override;
    void undo( GameState& state ) override;

private:
    int32_t strategy_for_row( Board& board );
    int32_t strategy_for_colum( Board& board );

private:
    bool m_done;
};

using RemoveCommandSharedPtr = std::shared_ptr< RemoveCommand >;
}
