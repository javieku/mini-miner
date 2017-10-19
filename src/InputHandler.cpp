#include "InputHandler.h"

#include "GenerateGemsCommand.h"
#include "RemoveGemsCommand.h"
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

std::deque< CommandInterfaceSharedPtr >
InputHandler::handle_event( )
{
    std::deque< CommandInterfaceSharedPtr > actions;
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

        actions.push_back( std::make_shared< SwapCommand >( Coordinates( {start_x, start_y} ),
                                                            Coordinates( {end_x, end_y} ) ) );
        actions.push_back( std::make_shared< RemoveGemsCommand >( ) );
        actions.push_back( std::make_shared< GenerateGemsCommand >( ) );
    }
    return actions;
}
}