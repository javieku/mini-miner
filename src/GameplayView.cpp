#include "GameView.h"

// Game
#include "GameState.h"

// Engine
#include <king/Engine.h>

namespace Game
{
GameView::GameView( King::Engine& engine )
    : m_engine( engine )
{
}

GameView::~GameView( )
{
}

void
GameView::render( const Board& board )
{
    for ( const Column& col : board.tiles( ) )
    {
        for ( const Tile& tile : col )
        {
            m_engine.Render( tile.texture, tile.x, tile.y );
        }
    }
}
void
GameView::render( const Timer& timer )
{
    if ( !timer.visible )
        return;

    std::string title = timer.text + std::to_string( timer.countdown( ) );
    m_engine.Write( title.c_str( ), timer.x, timer.y );
}

void
GameView::render( const Text& text )
{
    if ( !text.visible )
        return;
    m_engine.Write( text.text.c_str( ), text.x, text.y, text.rotation_factor * 2.5f );
}

void
GameView::render( const Score& score )
{
    if ( !score.visible )
        return;

    std::string title = score.text + std::to_string( score.score );
    m_engine.Write( title.c_str( ), score.x, score.y );
}

void
GameView::render( const GameState& state )
{
    m_engine.Render( state.background( ).texture, 0, 0 );
    render( state.board( ) );
    render( state.timer( ) );
    render( state.score( ) );
    render( state.score( ) );
}
}