#include "InputHandler.h"

// Game
#include "CollapseCommand.h"
#include "GenerateGemsCommand.h"
#include "RemoveGemsCommand.h"
#include "SwapCommand.h"

// Engine
#include <king/Engine.h>

// Standard
#include <memory>

namespace Game
{
InputHandler::InputHandler( King::Engine& engine )
    : m_engine( engine )
    , m_drag_started( false )
    , m_start_x( -1 )
    , m_start_y( -1 )
    , m_end_x( -1 )
    , m_end_y( -1 )
{
}

InputHandler::~InputHandler( )
{
}

std::deque< CommandInterfaceSharedPtr >
InputHandler::handle_event( )
{
    std::deque< CommandInterfaceSharedPtr > actions;
    if ( !m_drag_started && m_engine.GetMouseButtonDown( ) )
    {
        m_drag_started = true;
        m_start_x = m_engine.GetMouseX( );
        m_start_y = m_engine.GetMouseY( );
    }

    if ( m_drag_started && !m_engine.GetMouseButtonDown( ) )
    {
        m_drag_started = false;
        m_end_x = m_engine.GetMouseX( );
        m_end_y = m_engine.GetMouseY( );

        actions.push_back( std::make_shared< SwapCommand >( Coordinates( {m_start_x, m_start_y} ),
                                                            Coordinates( {m_end_x, m_end_y} ) ) );
        actions.push_back( std::make_shared< RemoveGemsCommand >( ) );
        actions.push_back( std::make_shared< CollapseCommand >( ) );
    }

    return actions;
}
}