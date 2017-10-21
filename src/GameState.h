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
    const Timer& timer( ) const;
    const Board& board( ) const;
    Board& board( );

    // Wrappers (law of Demeter)
    Tiles& board_tiles( );
    const Tiles& board_tiles( ) const;

    // Helpers
    bool is_finished( ) const;
    void increase_score( );

    // Debug
    void print( ) const;

private:
    Board m_board;
    Score m_score;
    Timer m_timer;
};
}