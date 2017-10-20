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
class GameplayView
{
public:
    GameplayView( ) = delete;
    explicit GameplayView( King::Engine& engine );
    ~GameplayView( );

    void render( const GameState& model );

private:
    King::Engine& m_engine;
};
}