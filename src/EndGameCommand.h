#pragma once

// Game
#include "CommandInterface.h"

namespace Game
{
class EndGameCommand : public CommandInterface
{
public:
    EndGameCommand( ) = default;

    ~EndGameCommand( ) = default;

    bool is_valid( const GameState& state ) const override;

    bool is_finished( const GameState& state ) const override;

    void apply( GameState& state ) override;
    void undo( GameState& state ) override;

private:
    void show_game_over( GameState& state );
    void move_score( GameState& state );
    void hide_board( GameState& state );
    void hide_timer( GameState& state );
};

using EndGameCommandSharedPtr = std::shared_ptr< EndGameCommand >;
}