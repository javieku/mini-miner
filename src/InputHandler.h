#pragma once

#include "CommandInterface.h"

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

    CommandInterfaceSharedPtr handle_events( );

private:
    King::Engine& m_engine;

	bool m_drag_started;
    float start_x;
    float start_y;
    float end_x;
    float end_y;
};
}