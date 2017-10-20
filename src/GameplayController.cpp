#include "GameplayController.h"

namespace Game
{
GameController::GameController( InputHandler& input_handler )
    : m_input_handler( input_handler )
{
}

GameController::~GameController( )
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
            m_actions = m_input_handler.handle_event( );
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
}