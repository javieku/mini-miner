#define GLM_FORCE_RADIANS

// Game
#include "CommandInterface.h"
#include "Gameplay.h"
#include "GameplayController.h"
#include "GameplayView.h"
#include "InputHandler.h"

// Engine
#include <king/Engine.h>
#include <king/Updater.h>

// Standard
#include <ctime>

//**********************************************************************

class ExampleGame : public King::Updater
{
public:
    ExampleGame( )
        : mEngine( "./assets" )
        , mRotation( 0.0f )
        , mYellowDiamondX( 100.0f )
        , mYellowDiamondY( 100.0f )
    {
    }

    void
    Start( )
    {
        mEngine.Start( *this );
    }

    void
    Update( )
    {
        mEngine.Render( King::Engine::TEXTURE_BACKGROUND, 0.0f, 0.0f );
        mEngine.Render( King::Engine::TEXTURE_RED, 100.0f, 450.0f );
        mEngine.Render( King::Engine::TEXTURE_BLUE, 650.0f, 450.0f );

        mEngine.Write( "Green", 650.0f, 140.0f );
        mEngine.Write( "Red", 100.0f, 490.0f );
        mEngine.Write( "Blue", 650.0f, 490.0f );

        const char text[] = "This rotates at 5/PI Hz";
        mRotation += mEngine.GetLastFrameSeconds( );
        mEngine.Write( text, mEngine.GetWidth( ) / 2.0f, mEngine.GetHeight( ) / 2.0f,
                       mRotation * 2.5f );

        if ( mEngine.GetMouseButtonDown( ) )
        {
            mYellowDiamondX = mEngine.GetMouseX( );
            mYellowDiamondY = mEngine.GetMouseY( );
        }
        mEngine.Render( King::Engine::TEXTURE_YELLOW, mYellowDiamondX, mYellowDiamondY );
        mEngine.Write( "Click to", mYellowDiamondX, mYellowDiamondY + 40.0f );
        mEngine.Write( "move me!", mYellowDiamondX, mYellowDiamondY + 70.0f );
    }

private:
    King::Engine mEngine;
    float mRotation;
    float mYellowDiamondX;
    float mYellowDiamondY;
};

//**********************************************************************
class MiniCrush : public King::Updater
{
public:
    MiniCrush( )
        : m_engine( "./assets" )
        , m_view( m_engine )
        , m_gameplay( )
        , m_input( m_engine )
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
        m_view.render( m_gameplay );

        m_controller.update( m_gameplay );

        if ( m_gameplay.is_finished( ) )
        {
            m_engine.Quit( );
        }
    }

private:
    King::Engine m_engine;

    Game::GameplayController m_controller;
    Game::Gameplay m_gameplay;
    Game::GameplayView m_view;
    Game::InputHandler m_input;
};

//**********************************************************************

int
main( int argc, char* argv[] )
{
    std::srand( std::time( 0 ) );

    MiniCrush game;
    game.Start( );

    // ExampleGame g;
    // g.Start( );

    return 0;
}
