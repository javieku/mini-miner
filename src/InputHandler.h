#pragma once

// Game
#include "CommandInterface.h"

// Standard
#include <deque>

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
    ~InputHandler( );

    std::deque< CommandInterfaceSharedPtr > handle_event( );

private:
    King::Engine& m_engine;

    bool m_drag_started;
    float m_start_x;
    float m_start_y;
    float m_end_x;
    float m_end_y;
};
}