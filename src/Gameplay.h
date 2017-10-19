#pragma once

#include "Hud.h"

// Standard
#include <string>
#include <vector>

// Engine
#include <king/Engine.h>

namespace Game
{
enum class CellType
{
    RED,
    GREEN,
    YELLOW,
    BlUE
};

const unsigned int NROW = 8;
const unsigned int NCOL = 8;

struct CellPosition
{
    int row;
    int col;

    inline bool
    is_valid( ) const
    {
        return row >= 0 && col >= 0;
    }
};

struct Coordinates
{
    float x;
    float y;
};

struct Entity
{
    float x;
    float y;
    King::Engine::Texture texture;
};

struct Background : public Entity
{
};

struct Cell : public Entity
{
    CellType type;
};

using Row = std::vector< Cell >;
using Board = std::vector< Row >;

class Gameplay
{
public:
    Gameplay( );
    ~Gameplay( );

    const Entity& background( ) const;

    const Score& score( ) const;

    const Timer& timer( ) const;

    const Board& board( ) const;
    Board& board( );

    const Cell& cell( int32_t row, int32_t col ) const;
    Cell& cell( float x, float y );
    Cell copy_cell( float x, float y );
    const CellPosition& cell_position( float x, float y ) const;

    bool is_finished( ) const;

    void print( );

    void increase_score( );

private:
    void init_board( float width, float height );
    King::Engine::Texture generate_texture_type( int row, int col );

private:
    Board m_board;
    float x_board;
    float y_board;
    Score m_score;
    Timer m_timer;
};
}