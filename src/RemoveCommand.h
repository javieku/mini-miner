#pragma once

// Game
#include "CommandInterface.h"

namespace Game
{
class Board;
class GameState;

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
