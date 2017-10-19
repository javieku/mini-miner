#include "GameplayView.h"

#include <king/Engine.h>

namespace Game
{
GameplayView::GameplayView( King::Engine& engine )
    : m_engine( engine )
{
}

GameplayView::~GameplayView( )
{
}

void
GameplayView::render( const Gameplay& gameplay )
{
    m_engine.Render( gameplay.background( ).texture, 0, 0 );

    for ( const Colum& col : gameplay.board( ) )
    {
        for ( const Cell& cell : col )
        {
            m_engine.Render( cell.texture, cell.x, cell.y );
        }
    }

    std::string title = gameplay.score( ).text + std::to_string( gameplay.score( ).score );
    m_engine.Write( title.c_str( ), gameplay.score( ).x, gameplay.score( ).y );

    title = gameplay.timer( ).text + std::to_string( gameplay.timer( ).elapsed( ) );
    m_engine.Write( title.c_str( ), gameplay.timer( ).x, gameplay.timer( ).y );
}
}