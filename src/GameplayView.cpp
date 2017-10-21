#include "GameView.h"

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
GameView::render( const GameState& state )
{
    m_engine.Render( state.background( ).texture, 0, 0 );

    for ( const Colum& col : state.board( ).tiles( ) )
    {
        for ( const Tile& tile : col )
        {
            m_engine.Render( tile.texture, tile.x, tile.y );
        }
    }

    std::string title = state.score( ).text + std::to_string( state.score( ).score );
    m_engine.Write( title.c_str( ), state.score( ).x, state.score( ).y );

    title = state.timer( ).text + std::to_string( state.timer( ).countdown( ) );
    m_engine.Write( title.c_str( ), state.timer( ).x, state.timer( ).y );
}
}