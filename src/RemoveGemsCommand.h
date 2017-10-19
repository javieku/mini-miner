#pragma once

#include "CommandInterface.h"

namespace Game
{
class RemoveGemsCommand : public CommandInterface
{
public:
    RemoveGemsCommand( );
    ~RemoveGemsCommand( ) = default;

    bool is_valid( Gameplay& gameplay ) const override;
    bool is_finished( Gameplay& gameplay ) const override;
    bool apply( Gameplay& gameplay ) override;
    bool undo( Gameplay& gameplay ) override;

private:
    bool m_done;
};

using RemoveGemsCommandSharedPtr = std::shared_ptr< RemoveGemsCommand >;
}
