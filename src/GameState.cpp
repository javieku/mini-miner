#include "GameState.h"

// Standard
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>

namespace Game
{
GameState::GameState( )
    : m_background( {0.0f, 0.0f}, King::Engine::TEXTURE_BACKGROUND )
{
}

GameState::~GameState( )
{
}

const Entity&
GameState::background( ) const
{
    return m_background;
}

const Score&
GameState::score( ) const
{
    return m_score;
}

Score&
GameState::score( )
{
    return m_score;
}

const Timer&
GameState::timer( ) const
{
    return m_timer;
}

const Board&
GameState::board( ) const
{
    return m_board;
}

Board&
GameState::board( )
{
    return m_board;
}

Tiles&
GameState::board_tiles( )
{
    return m_board.tiles( );
}

const Tiles&
GameState::board_tiles( ) const
{
    return m_board.tiles( );
}
void
GameState::print( ) const
{
    m_board.print( );
}

bool
GameState::is_finished( ) const
{
    return m_timer.countdown( ) == 0;
}
}