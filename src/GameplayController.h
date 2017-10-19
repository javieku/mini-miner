#pragma once

#include "Gameplay.h"
#include "InputHandler.h"

namespace Game
{
class GameplayController
{
public:
    GameplayController( InputHandler& input_handler );
    ~GameplayController( );

    void update( Gameplay& gameplay );

private:
    InputHandler& m_input_handler;
    Game::CommandInterfaceSharedPtr m_action;
};
}