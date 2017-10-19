#pragma once

#include "CommandInterface.h"
#include "Gameplay.h"

namespace Game
{
class MoveCommand : public CommandInterface
{
public:
    MoveCommand( const CellPosition& from, const CellPosition& to );
    ~MoveCommand( ) = default;

    bool is_valid( Gameplay& gameplay ) const override;
    bool is_finished( Gameplay& gameplay ) const override;
    bool apply( Gameplay& gameplay ) override;
    bool undo( Gameplay& gameplay ) override;

private:
    CellPosition m_from;
    CellPosition m_to;

    // Undo
    Cell m_previous_cell;
    bool m_store_for_undo;
};
using MoveCommandSharedPtr = std::shared_ptr< MoveCommand >;
}