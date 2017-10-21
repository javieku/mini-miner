#include "InputHandler.h"

// Game
#include "Event.h"

// Engine
#include <king/Engine.h>

// Standard
#include <memory>

namespace Game
{
InputHandler::InputHandler( King::Engine& engine )
    : m_engine( engine )
    , m_drag_started( false )
    , m_start( {-1, -1} )
    , m_end( {-1, -1} )
{
}

std::deque< CommandInterfaceSharedPtr >
InputHandler::handle_event( )
{
    std::deque< CommandInterfaceSharedPtr > actions;
    if ( !m_drag_started && m_engine.GetMouseButtonDown( ) )
    {
        m_drag_started = true;
        m_start.x = m_engine.GetMouseX( );
        m_start.y = m_engine.GetMouseY( );
    }

    if ( m_drag_started && !m_engine.GetMouseButtonDown( ) )
    {
        m_drag_started = false;
        m_end.x = m_engine.GetMouseX( );
        m_end.y = m_engine.GetMouseY( );

        actions = m_factory.create_command_list( std::make_shared< DragEvent >( m_start, m_end ) );
    }

    return actions;
}
}