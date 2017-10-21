#pragma once

#include "Board.h"
#include "CommandInterface.h"
#include "Coordinates.h"
#include "GameState.h"

namespace Game
{
class MoveCommand : public CommandInterface
{
public:
    MoveCommand( const Gem& gem, const Coordinates& to );
    ~MoveCommand( ) = default;

    bool is_valid( const GameState& state ) const override;
    bool is_finished( const GameState& state ) const override;
    void apply( GameState& state ) override;
    void undo( GameState& state ) override;

private:
    Gem m_gem;
    Coordinates m_to_coordinates;

    // Undo
    Gem m_previous_gem;
    bool m_store_for_undo;
};

using MoveCommandSharedPtr = std::shared_ptr< MoveCommand >;
}