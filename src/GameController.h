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
    void end_game( GameState& state );

private:
    InputHandler& m_input_handler;

    Game::CommandInterfaceSharedPtr m_current_action;
    Game::CommandInterfaceSharedPtr m_last_action;
    std::deque< Game::CommandInterfaceSharedPtr > m_actions;

	CommandFactory m_factory;
};
}