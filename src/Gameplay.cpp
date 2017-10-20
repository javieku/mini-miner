#include "Gameplay.h"

// Standard
#include <algorithm>
#include <cstdlib>  // std::rand
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>

namespace Game
{
Gameplay::Gameplay( )
{
}

Gameplay::~Gameplay( )
{
}

const Entity&
Gameplay::background( ) const
{
    return {0.0f, 0.0f, King::Engine::TEXTURE_BACKGROUND};
}

const Score&
Gameplay::score( ) const
{
    return m_score;
}

const Timer&
Gameplay::timer( ) const
{
    return m_timer;
}

const Board&
Gameplay::board( ) const
{
    return m_board;
}

Board&
Gameplay::board( )
{
    return m_board;
}

Tiles&
Gameplay::board_tiles( )
{
    return m_board.tiles( );
}

const Tiles&
Gameplay::board_tiles( ) const
{
    return m_board.tiles( );
}
void
Gameplay::print( ) const
{
    m_board.print( );
}

bool
Gameplay::is_finished( ) const
{
    return m_timer.countdown( ) == 0;
}

void
Gameplay::increase_score( )
{
    m_score.score += 50;
}
}