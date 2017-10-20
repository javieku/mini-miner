#pragma once

// Game
#include "GameState.h"

// Engine
#include <king/Engine.h>

namespace King
{
class Engine;
}

namespace Game
{
class GameView
{
public:
    GameView( ) = delete;
    explicit GameView( King::Engine& engine );
    ~GameView( );

    void render( const GameState& model );

private:
    King::Engine& m_engine;
};
}