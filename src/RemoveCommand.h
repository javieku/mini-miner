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
 * It is not valid when no tile is removed. This is convenient to check
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
 *		- Board transposition is applied.  		
 *        1 2 3       1 4 7
 *        4 5 6  ---> 2 5 8
 *        7 8 9       3 6 9
 *      - Then the same strategy as for colums.
 *      - Finally the changes are applied on the board
 *      
 *   Because it is good for readability to use std::adjacent_first and to use 
 *   the same strategy for both dimensions is simpler to understand I have implemented
 *   step 2 using this transposition despite generating an extra copy of the board. 
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
