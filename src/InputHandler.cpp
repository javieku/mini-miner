#include "InputHandler.h"

#include "SwapCommand.h"

#include <king/Engine.h>

#include <memory>

namespace Game
{
InputHandler::InputHandler( King::Engine& engine )
    : m_engine( engine )
    , m_drag_started( false )
{
    start_x = -1;
    start_y = -1;
}

InputHandler::~InputHandler( )
{
}

CommandInterfaceSharedPtr
InputHandler::handle_events( )
{
    CommandInterfaceSharedPtr command;
    if ( !m_drag_started && m_engine.GetMouseButtonDown( ) )
    {
        m_drag_started = true;
        start_x = m_engine.GetMouseX( );
        start_y = m_engine.GetMouseY( );
    }
    if ( m_drag_started && !m_engine.GetMouseButtonDown( ) )
    {
        m_drag_started = false;
        end_x = m_engine.GetMouseX( );
        end_y = m_engine.GetMouseY( );

        command = std::make_shared< SwapCommand >( Coordinates( {start_x, start_y} ),
                                                   Coordinates( {end_x, end_y} ) );
    }
    return command;
}
}