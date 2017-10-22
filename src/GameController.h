#pragma once

// Game
#include "CommandFactory.h"
#include "CommandInterface.h"
#include "GameState.h"

// Standard
#include <deque>

namespace Game
{
class InputHandler;
/**
 * Executes sequencually every command in a list created by CommandFactory.
 *
 * This command list depends on how the event(ClickEvent, DragEvent,
 * GameOverEvent...) is expected to interact with the model.
 **/
class GameController
{
public:
    GameController( InputHandler& input_handler );
    ~GameController( ) = default;

    void update( GameState& state );

    bool is_finished( const GameState& state ) const;

private:
    CommandInterfaceSharedPtr next_command( GameState& state );

private:
    InputHandler& m_input_handler;

    Game::CommandInterfaceSharedPtr m_current_command;
    Game::CommandInterfaceSharedPtr m_last_command;
    std::deque< Game::CommandInterfaceSharedPtr > m_actions;

    CommandFactory m_factory;
};
}