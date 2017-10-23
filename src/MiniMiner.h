#pragma once

// Game
#include "GameController.h"
#include "GameState.h"
#include "GameView.h"
#include "InputHandler.h"

// Engine
#include <king/Engine.h>
#include <king/Updater.h>

namespace Game
{
class MiniMiner : public King::Updater
{
public:
    MiniMiner( )
        : m_engine( "./assets" )
        , m_input( m_engine )
        , m_view( m_engine )
        , m_game_state( )
        , m_controller( m_input )
    {
    }

    void
    Start( )
    {
        m_engine.Start( *this );
    }

    void
    Update( )
    {
        m_view.render( m_game_state );

        m_controller.update( m_game_state );
    }

private:
    King::Engine m_engine;
    InputHandler m_input;

    GameController m_controller;
    GameState m_game_state;
    GameView m_view;
};
}
