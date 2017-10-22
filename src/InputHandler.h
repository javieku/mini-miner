#pragma once

// Game
#include "Event.h"

// Standard
#include <deque>
#include <memory>

namespace King
{
class Engine;
}

namespace Game
{
/**
 * Observes changes in the mouse position from the engine and
 * creates different EventSharedPtr.
 *
 * These events will be used afterwards to create different
 * sequences of commands to make operations on the GameState.
 *
 * Engine implementation could be improved by using a 1-1 observer pattern
 * to receive events generated in the engine.
 **/
class InputHandler
{
public:
    InputHandler( King::Engine& engine );
    ~InputHandler( ) = default;

    EventSharedPtr handle_event( );

private:
    EventSharedPtr handle_click( const Coordinates& first_click, const Coordinates& second_click );

private:
    King::Engine& m_engine;

    // Input processing
    bool m_drag_started;
    Coordinates m_start_drag;

    // Click related fields
    bool m_is_first_click;
    Coordinates m_first_click_position;
};
}