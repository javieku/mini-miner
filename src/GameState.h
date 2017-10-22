#pragma once

// Game
#include "Board.h"
#include "Entity.h"
#include "Score.h"
#include "Timer.h"

// Standard
#include <string>
#include <vector>

// Engine
#include <king/Engine.h>

namespace Game
{
class GameState
{
public:
    GameState( );
    ~GameState( );

    // Models
    const Entity& background( ) const;
    const Score& score( ) const;
    Score& score( );
    const Timer& timer( ) const;
    const Board& board( ) const;
    Board& board( );

    // Wrappers (law of Demeter)
    Tiles& board_tiles( );
    const Tiles& board_tiles( ) const;

    // Helpers
    bool is_finished( ) const;

    // Debug
    void print( ) const;

private:
    Entity m_background;
    Board m_board;
    Score m_score;
    Timer m_timer;
};
}