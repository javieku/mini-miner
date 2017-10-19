#pragma once

#include "Gameplay.h"

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

    void render( const Gameplay& model );

private:
    King::Engine& m_engine;
};
}