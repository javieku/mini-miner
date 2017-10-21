#pragma once

#include "CommandInterface.h"

namespace Game
{
class RemoveCommand : public CommandInterface
{
public:
    RemoveCommand( );
    ~RemoveCommand( ) = default;

    bool is_valid( const GameState& state ) const override;
    bool is_finished( const GameState& state ) const override;
    void apply( GameState& state ) override;
    void undo( GameState& state ) override;

private:
    bool m_done;
};

using RemoveCommandSharedPtr = std::shared_ptr< RemoveCommand >;
}
