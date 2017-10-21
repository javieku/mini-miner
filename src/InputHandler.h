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
    King::Engine& m_engine;

    bool m_drag_started;
	Coordinates m_start;
	Coordinates m_end;

    CommandFactory m_factory;
};
}