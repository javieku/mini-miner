#include "GameController.h"

// Game
#include "InputHandler.h"

namespace Game
{
GameController::GameController( InputHandler& input_handler )
    : m_input_handler( input_handler )
{
}

void
GameController::update( GameState& state )
{
    if ( !m_current_action )
    {
        if ( !m_actions.empty( ) )
        {
            m_current_action = m_actions.front( );
            m_actions.pop_front( );
            if ( !m_current_action->is_valid( state ) && m_last_action )
            {
                m_last_action->undo( state );
                m_current_action = m_last_action;
                m_actions.clear( );
            }
        }
        else
        {
            m_last_action = nullptr;
            EventSharedPtr event = m_input_handler.handle_event( );
            m_actions = m_factory.create_command_list( event );
        }
    }
    else
    {
        if ( !m_current_action->is_finished( state ) )
        {
            m_current_action->apply( state );
        }
        else
        {
            m_last_action = m_current_action;
            m_current_action = nullptr;
        }
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