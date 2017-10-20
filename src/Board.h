#pragma once

// Game
#include "Entity.h"

// Engine
#include <king/Engine.h>

// Standard
#include <vector>

namespace Game
{
const unsigned int NROW = 8;
const unsigned int NCOL = 8;

enum class CellState
{
    RED,
    GREEN,
    YELLOW,
    BlUE,
    BROKEN,
    SELECTED
};

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

struct Cell : public Entity
{
    CellState type;

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
using Tiles = std::vector< Colum >;

class Board : Entity
{
public:
    Board( );
    ~Board( ) = default;

    const Cell& cell( int32_t row, int32_t col ) const;
    const Cell& cell( float x, float y ) const;
    Cell copy_cell( float x, float y );
    const CellPosition& cell_position( float x, float y ) const;

    const Tiles& tiles( ) const;
    Tiles& tiles( );

    void print( ) const;

private:
    void init_board( float width, float height );
    King::Engine::Texture generate_texture_type( int row, int col );

private:
    Tiles m_tiles;
};
}