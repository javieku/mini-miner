#include "GameController.h"

// Game
#include "InputHandler.h"

namespace Game
{
GameController::GameController( InputHandler& input_handler )
    : m_input_handler( input_handler )
{
}

CommandInterfaceSharedPtr
GameController::next_command( GameState& state )
{
    if ( m_actions.empty( ) )
    {
        EventSharedPtr event = m_input_handler.handle_event( );
        m_actions = m_factory.create_command_list( event );
        m_last_command = nullptr;
    }

    if ( m_actions.empty( ) )
        return nullptr;

    auto next_action = m_actions.front( );
    m_actions.pop_front( );

    if ( !next_action->is_valid( state ) && m_last_command )
    {
        m_last_command->undo( state );
        next_action = m_last_command;
        m_actions.clear( );
    }

    return next_action;
}

void
GameController::update( GameState& state )
{
    if ( m_current_command )
    {
        if ( m_current_command->is_finished( state ) )
        {
            m_last_command = m_current_command;
            m_current_command = next_command( state );
        }
        else
        {
            m_current_command->apply( state );
        }
    }
    else
    {
        m_current_command = next_command( state );
    }
}

bool
GameController::is_finished( const GameState& state ) const
{
    return state.is_finished( );
}

void
GameController::end_game( GameState& state )
{
}
}