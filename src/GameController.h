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