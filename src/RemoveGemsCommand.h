#pragma once

#include "CommandInterface.h"

namespace Game
{
class RemoveGemsCommand : public CommandInterface
{
public:
    RemoveGemsCommand( );
    ~RemoveGemsCommand( ) = default;

    bool is_valid( const GameState& gameplay ) const override;
    bool is_finished( const GameState& gameplay ) const override;
    bool apply( GameState& gameplay ) override;
    bool undo( GameState& gameplay ) override;

private:
    bool m_done;
};

using RemoveGemsCommandSharedPtr = std::shared_ptr< RemoveGemsCommand >;
}
