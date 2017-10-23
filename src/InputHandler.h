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
 * Observes changes in the engine mouse position and
 * creates different Event.
 *
 * These events will be used afterwards to create different
 * sequences of commands to apply algorithms to the GameState.
 *
 * Engine implementation could be improved by using a 1-1 observer pattern
 * to receive events generated in the engine. In that way, the game 
 * would have to pull the mouse position on every loop iteration.
 * 
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