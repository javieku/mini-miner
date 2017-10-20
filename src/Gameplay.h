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

    static Cell
    create_random( float x, float y )
    {
        std::vector< King::Engine::Texture > supported_cell_types
            = {King::Engine::TEXTURE_BLUE, King::Engine::TEXTURE_YELLOW, King::Engine::TEXTURE_RED,
               King::Engine::TEXTURE_GREEN, King::Engine::TEXTURE_PURPLE};

        Cell new_cell;
        new_cell.texture = supported_cell_types[ std::rand( ) % supported_cell_types.size( ) ];
        new_cell.y = x;
        new_cell.x = y;
        return new_cell;
    }
};

using Colum = std::vector< Cell >;
using Board = std::vector< Colum >;

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
    const Cell& cell( float x, float y ) const;
    Cell copy_cell( float x, float y );
    const CellPosition& cell_position( float x, float y ) const;

    bool is_finished( ) const;

    void increase_score( );

    // Debug
    void print( ) const;

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