#include "GameplayController.h"

namespace Game
{
GameplayController::GameplayController( InputHandler& input_handler )
    : m_input_handler( input_handler )
{
}

GameplayController::~GameplayController( )
{
}

void
GameplayController::update( Gameplay& gameplay )
{
    if ( !m_action || m_action->is_finished( gameplay ) )
    {
        m_action = m_input_handler.handle_events( );
    }
    else
    {
        m_action->apply( gameplay );
    }
}
}