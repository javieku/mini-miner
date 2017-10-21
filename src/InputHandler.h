#pragma once

// Game
#include "CommandFactory.h"
#include "CommandInterface.h"
#include "Coordinates.h"

// Standard
#include <deque>
#include <memory>

namespace King
{
class Engine;
}

namespace Game
{
class InputHandler
{
public:
    InputHandler( King::Engine& engine );
    ~InputHandler( ) = default;

    std::deque< CommandInterfaceSharedPtr > handle_event( );

private:
    EventSharedPtr handle_click( const Coordinates& first_click, const Coordinates& second_click );

private:
    King::Engine& m_engine;

    // Input processing
    bool m_drag_started;
    Coordinates m_start_drag;

	// Click related members
    bool m_is_first_click;
    Coordinates m_first_click_position;

	// Create game actions
    CommandFactory m_factory;
};
}