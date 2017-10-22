#include "InputHandler.h"

// Game
#include "Event.h"

// Engine
#include <king/Engine.h>

// Standard
#include <memory>

namespace Game
{
namespace
{
const int32_t DELTA = 5u;
bool
is_click( const Coordinates& c1, const Coordinates& c2 )
{
    return std::abs( c1.x - c2.x ) < DELTA && std::abs( c1.y - c2.y ) < DELTA;
}
}

InputHandler::InputHandler( King::Engine& engine )
    : m_engine( engine )
    , m_drag_started( false )
    , m_start_drag( {-1, -1} )
    , m_first_click_position( {-1, -1} )
    , m_is_first_click( true )
{
}

EventSharedPtr
InputHandler::handle_click( const Coordinates& first_click, const Coordinates& second_click )
{
    EventSharedPtr event = std::make_shared< Event >( );
    if ( !m_is_first_click )
    {
        event = std::make_shared< ClickEvent >( first_click, second_click );
    }
    else
    {
        // Needed to create ClickEvent afterwards
        m_first_click_position = second_click;
    }
    m_is_first_click = !m_is_first_click;

    return event;
}

EventSharedPtr
InputHandler::handle_event( )
{
    EventSharedPtr event = std::make_shared< Event >( );
    if ( !m_drag_started && m_engine.GetMouseButtonDown( ) )
    {
        m_drag_started = true;
        m_start_drag.x = m_engine.GetMouseX( );
        m_start_drag.y = m_engine.GetMouseY( );
    }

    if ( m_drag_started && !m_engine.GetMouseButtonDown( ) )
    {
        m_drag_started = false;
        Coordinates end_drag{m_engine.GetMouseX( ), m_engine.GetMouseY( )};

        if ( is_click( m_start_drag, end_drag ) )
        {
            event = handle_click( m_first_click_position, end_drag );
        }
        else
        {
            event = std::make_shared< DragEvent >( m_start_drag, end_drag );
        }
    }

    return event;
}
}