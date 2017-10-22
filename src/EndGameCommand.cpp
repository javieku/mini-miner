#include "EndGameCommand.h"

// Game
#include "GameState.h"

namespace Game
{
namespace
{
const int32_t DELTA = 4u;
const int32_t ROTATION_DELTA = 10u;
}

bool
EndGameCommand::is_valid( const GameState& state ) const
{
    return state.is_finished( );
}

bool
EndGameCommand::is_finished( const GameState& state ) const
{
    return false;
}

void
EndGameCommand::apply( GameState& state )
{
    hide_board( state );
    show_game_over( state );
    move_score( state );
    hide_timer( state );
}

void
EndGameCommand::undo( GameState& state )
{
    // No needed
}

void
EndGameCommand::show_game_over( GameState& state )
{
    Text& msg = state.end_game_msg( );
    msg.visible = true;
    msg.rotation_factor += ROTATION_DELTA;
    if ( msg.x < 400u )
        msg.x += DELTA;
    else
        msg.rotation_factor = 0.0f;
}

void
EndGameCommand::move_score( GameState& state )
{
    if ( state.score( ).x < 400u )
        state.score( ).x += DELTA;
}

void
EndGameCommand::hide_board( GameState& state )
{
    state.board_tiles( ).clear( );
}

void
EndGameCommand::hide_timer( GameState& state )
{
    state.timer( ).visible = false;
    state.timer( ).stop( );
}
}