#pragma once

#include "CommandInterface.h"

namespace Game
{
class RemoveGemsCommand : public CommandInterface
{
public:
    RemoveGemsCommand( );
    ~RemoveGemsCommand( ) = default;

    bool is_valid( const GameState& state ) const override;
    bool is_finished( const GameState& state ) const override;
    void apply( GameState& state ) override;
    void undo( GameState& state ) override;

private:
    bool m_done;
};

using RemoveGemsCommandSharedPtr = std::shared_ptr< RemoveGemsCommand >;
}
